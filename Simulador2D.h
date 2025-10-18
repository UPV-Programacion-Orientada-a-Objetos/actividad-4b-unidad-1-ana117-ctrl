#ifndef SIMULADOR2D_H
#define SIMULADOR2D_H

#include <iostream> 
#include <iomanip>  

// Definición de la clase genérica 
template <typename T>
class Simulador2D {
private:
    //Atributos Requeridos
    T **_grid;
    int _filas;
    int _columnas;

    T *_fuentes;
    int _numFuentes;
    int _capacidadFuentes;

    float _constantes[3];

    void _liberarMemoria() {
        // Solo liberar si los punteros no son nulos
        if (_grid != nullptr) {
            for (int i = 0; i < _filas; ++i) {
                delete[] _grid[i]; //Liberar cada fila
            }
            delete[] _grid; //Liberar el arreglo de punteros
            _grid = nullptr;
        }
        
        if (_fuentes != nullptr) {
            delete[] _fuentes;
            _fuentes = nullptr;
        }
        
        // Reiniciar contadores
        _filas = 0;
        _columnas = 0;
        _numFuentes = 0;
        _capacidadFuentes = 0;
    }

public:
    //constructor principal
    Simulador2D(int f, int c) : 
        _grid(nullptr), _filas(f), _columnas(c), // Inicializar puntero a null
        _fuentes(nullptr), _numFuentes(0), _capacidadFuentes(4) // Capacidad inicial
    {
        std::cout << "Constructor: Creando Grid (" << typeid(T).name() << ") de " << f << "x" << c << "...\n";

        // Asignar Grid
        _grid = new T*[_filas]; 
        for (int i = 0; i < _filas; ++i) {
            _grid[i] = new T[_columnas]; 
            for (int j = 0; j < _columnas; ++j) {
                _grid[i][j] = T(); 
            }
        }

        // Asignar Fuentes
        _fuentes = new T[_capacidadFuentes];

        // Inicializar constantes
        for (int i = 0; i < 3; ++i) {
            _constantes[i] = 0.0f;
        }
    }

    //Regla de los cinco
    ~Simulador2D() {
        std::cout << "\n Destructor: Liberando memoria...\n";
        _liberarMemoria(); // Usar la función de ayuda
    }

    Simulador2D(const Simulador2D<T>& other) {
        std::cout << "Constructor de Copia: Realizando copia profunda...\n";
        
        // Copiar datos simples
        _filas = other._filas;
        _columnas = other._columnas;
        _numFuentes = other._numFuentes;
        _capacidadFuentes = other._capacidadFuentes;
        for(int i=0; i<3; ++i) _constantes[i] = other._constantes[i];

        // Asignar y copiar Grid (Copia profunda)
        _grid = new T*[_filas];
        for (int i = 0; i < _filas; ++i) {
            _grid[i] = new T[_columnas];
            for (int j = 0; j < _columnas; ++j) {
                _grid[i][j] = other._grid[i][j];
            }
        }

        // Asignar y copiar Fuentes (Copia profunda)
        _fuentes = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; ++i) {
            _fuentes[i] = other._fuentes[i];
        }
    }

    Simulador2D<T>& operator=(const Simulador2D<T>& other) {
        std::cout << "Operador de Asignación (Copia): Realizando copia profunda...\n";
        
        // Chequeo de auto-asignación
        if (this == &other) {
            return *this;
        }

        // Liberar memoria existente
        _liberarMemoria();

        // Copiar datos (Idéntico al Constructor de Copia)
        _filas = other._filas;
        _columnas = other._columnas;
        _numFuentes = other._numFuentes;
        _capacidadFuentes = other._capacidadFuentes;
        for(int i=0; i<3; ++i) _constantes[i] = other._constantes[i];

        _grid = new T*[_filas];
        for (int i = 0; i < _filas; ++i) {
            _grid[i] = new T[_columnas];
            for (int j = 0; j < _columnas; ++j) {
                _grid[i][j] = other._grid[i][j];
            }
        }

        _fuentes = new T[_capacidadFuentes];
        for (int i = 0; i < _numFuentes; ++i) {
            _fuentes[i] = other._fuentes[i];
        }
        return *this;
    }

    Simulador2D(Simulador2D<T>&& other) noexcept {
        std::cout << "Constructor de Movimiento: Robando recursos...\n";

        // Robar datos
        _filas = other._filas;
        _columnas = other._columnas;
        _numFuentes = other._numFuentes;
        _capacidadFuentes = other._capacidadFuentes;
        for(int i=0; i<3; ++i) _constantes[i] = other._constantes[i];

        // Robar punteros
        _grid = other._grid;
        _fuentes = other._fuentes;

        // Anular el other para que su destructor no libere la memoria
        other._filas = 0;
        other._columnas = 0;
        other._numFuentes = 0;
        other._capacidadFuentes = 0;
        other._grid = nullptr;
        other._fuentes = nullptr;
    }

    Simulador2D<T>& operator=(Simulador2D<T>&& other) noexcept {
        std::cout << "Operador de Asignación (Movimiento): Robando recursos...\n";

        //Chequeo de auto-asignación
        if (this == &other) {
            return *this;
        }

        // Liberar memoria existente
        _liberarMemoria();

        //Robar datos (Idéntico al Constructor de Movimiento)
        _filas = other._filas;
        _columnas = other._columnas;
        _numFuentes = other._numFuentes;
        _capacidadFuentes = other._capacidadFuentes;
        for(int i=0; i<3; ++i) _constantes[i] = other._constantes[i];
        
        _grid = other._grid;
        _fuentes = other._fuentes;

        //Anular el other
        other._filas = 0;
        other._columnas = 0;
        other._numFuentes = 0;
        other._capacidadFuentes = 0;
        other._grid = nullptr;
        other._fuentes = nullptr;

        return *this;
    }

    // Métodos obligatorios 

    void redimensionarGrid(int nuevaF, int nuevaC) {
        std::cout << "Redimensionando Grid a " << nuevaF << "x" << nuevaC << ". ";

        T **nuevoGrid = new T*[nuevaF];
        for (int i = 0; i < nuevaF; ++i) {
            nuevoGrid[i] = new T[nuevaC];
            for (int j = 0; j < nuevaC; ++j) {
                nuevoGrid[i][j] = T();
            }
        }

        int filasACopiar = (nuevaF < _filas) ? nuevaF : _filas;
        int colsACopiar = (nuevaC < _columnas) ? nuevaC : _columnas;

        // Copiar datos, solo si el grid antiguo no era nulo
        if (_grid != nullptr) {
             for (int i = 0; i < filasACopiar; ++i) {
                for (int j = 0; j < colsACopiar; ++j) {
                    nuevoGrid[i][j] = _grid[i][j];
                }
            }
            
            // Liberar la memoria del grid antiguo 
            for (int i = 0; i < _filas; ++i) {
                delete[] _grid[i];
            }
            delete[] _grid;
        }

        _grid = nuevoGrid;
        _filas = nuevaF;
        _columnas = nuevaC;

        std::cout << "Datos copiados.\n";
    }

    void agregarFuente(T valor) {
        if (_numFuentes >= _capacidadFuentes) {
            int nuevaCapacidad = _capacidadFuentes * 2;
            T *nuevasFuentes = new T[nuevaCapacidad];
            for (int i = 0; i < _numFuentes; ++i) {
                nuevasFuentes[i] = _fuentes[i];
            }
            delete[] _fuentes;
            _fuentes = nuevasFuentes;
            _capacidadFuentes = nuevaCapacidad;
            std::cout << "(Capacidad de fuentes expandida a " << nuevaCapacidad << ") ";
        }
        _fuentes[_numFuentes] = valor;
        _numFuentes++;
        std::cout << "Agregar Fuente (Valor " << valor << "): Éxito.\n";
    }

    void simularPaso() {
        std::cout << "Simulando Propagación...\n";
        T **tempGrid = new T*[_filas];
        for (int i = 0; i < _filas; ++i) {
            tempGrid[i] = new T[_columnas];
        }

        for (int i = 0; i < _filas; ++i) {
            for (int j = 0; j < _columnas; ++j) {
                if (i == 0 || i == _filas - 1 || j == 0 || j == _columnas - 1) {
                    tempGrid[i][j] = _grid[i][j];
                } else {
                    tempGrid[i][j] = (_grid[i - 1][j] + _grid[i + 1][j] + _grid[i][j - 1] + _grid[i][j + 1]) / 4;
                }
            }
        }

        for (int i = 0; i < _filas; ++i) {
            for (int j = 0; j < _columnas; ++j) {
                _grid[i][j] = tempGrid[i][j];
            }
        }

        for (int i = 0; i < _filas; ++i) {
            delete[] tempGrid[i];
        }
        delete[] tempGrid;
    }

    void visualizarGrid() const {
        // Chequeo por si el grid fue movido (ahora es nulo)
        if (_grid == nullptr) {
            std::cout << "[Grid NULO (movido)]\n";
            return;
        }
        
        std::cout << std::fixed << std::setprecision(1);
        for (int i = 0; i < _filas; ++i) {
            std::cout << "| ";
            for (int j = 0; j < _columnas; ++j) {
                std::cout << std::setw(5) << _grid[i][j] << " | ";
            }
            std::cout << std::endl;
        }
    }

    void setValor(int f, int c, T valor) {
        if (f >= 0 && f < _filas && c >= 0 && c < _columnas) {
            _grid[f][c] = valor;
        } else {
            std::cout << "Error: Coordenadas (" << f << "," << c << ") fuera de límites.\n";
        }
    }

    void setConstantes(float c1, float c2, float c3) {
        _constantes[0] = c1;
        _constantes[1] = c2;
        _constantes[2] = c3;
        std::cout << "Constantes físicas establecidas.\n";
    }
};
#endif 