#include <iostream>
#include "Simulador2D.h" 

//Funciones de Ayuda para Probar Copia y Movimiento 
template <typename T>
void probarPasoPorValor(Simulador2D<T> simCopiado) {
    std::cout << "\n--- [Dentro de probarPasoPorValor] ---\n";
    std::cout << "Grid de la COPIA:\n";
    simCopiado.visualizarGrid();
}

Simulador2D<float> crearSimuladorTemp(int f, int c) {
     std::cout << "\n--- [Dentro de crearSimuladorTemp] ---\n";
    Simulador2D<float> temp(f, c);
    temp.setValor(1, 1, 99.9f);
     std::cout << "--- [Saliendo de crearSimuladorTemp (se moverá 'temp')] ---\n";
    return temp; // Esto invoca el Constructor de Movimiento 
}


int main() {
    std::cout << "--- Simulador Genérico de Fluidos ---\n\n";
    //prueba 1: Simulador con tipo FLOAT (Original)
    std::cout << ">> Inicializando Sistema (Tipo FLOAT) <<\n";
    Simulador2D<float> simFloat(5, 5); 
    simFloat.agregarFuente(100.0f);
    simFloat.agregarFuente(50.0f); 
    simFloat.setValor(2, 2, 100.0f);
    simFloat.setValor(4, 0, 50.0f); 
    
    std::cout << "\n--- Grid Inicial (Paso 0) ---\n";
    simFloat.visualizarGrid();
    simFloat.simularPaso();
    std::cout << "\n--- Grid Después del Paso 1 ---\n";
    simFloat.visualizarGrid();
    simFloat.redimensionarGrid(6, 6);


    std::cout << "\n" << std::string(50, '=') << "\n\n";
    std::cout << ">> DEMOSTRACIÓN: REGLA DE LOS 5 <<\n";

    //Prueba Constructor de Copia 
    std::cout << "\n>> 1. Probando Constructor de Copia (paso por valor) <<\n";
    probarPasoPorValor(simFloat);
    std::cout << "\nGrid Original (simFloat) después de la copia (debe estar intacto):\n";
    simFloat.visualizarGrid(); // El original debe seguir intacto

    //Prueba Operador de Asignación de Copia 
    std::cout << "\n>> 2. Probando Operador de Asignación (Copia) <<\n";
    Simulador2D<float> simCopiaAsignada(2, 2); // Un sim pequeño
    std::cout << "--- Antes de asignar:\n";
    simCopiaAsignada.visualizarGrid();
    simCopiaAsignada = simFloat; // Se invoca operator=(copia)
    std::cout << "--- Después de asignar (debe ser igual al original):\n";
    simCopiaAsignada.visualizarGrid();

    //Prueba Constructor de Movimiento 
    std::cout << "\n>> 3. Probando Constructor de Movimiento (desde función) <<\n";
    // El objeto retornado por crearSimuladorTemp es un r-value,
    // se usa el Constructor de Movimiento para crear simMovida.
    Simulador2D<float> simMovida = crearSimuladorTemp(3, 3);
    std::cout << "\n--- Grid de simMovida (después de mover) ---\n";
    simMovida.visualizarGrid();
    
    //Prueba Operador de Asignación de Movimiento
    std::cout << "\n>> 4. Probando Operador de Asignación (Movimiento) <<\n";
    // simFloat (6x6) recibe los datos de un temporal (2x2)
    simFloat = crearSimuladorTemp(2, 2); // Se invoca operator=(movimiento)
    std::cout << "\n--- Grid de simFloat (después de recibir el movimiento) ---\n";
    simFloat.visualizarGrid(); // Ahora debe ser 2x2


    std::cout << "\n" << std::string(50, '=') << "\n\n";
    //Prueba 2: Simulador con tipo int (original)
    std::cout << ">> Inicializando Sistema (Tipo INT) <<\n";
    Simulador2D<int> simInt(4, 4); 
    simInt.agregarFuente(99); 
    simInt.setValor(1, 1, 99);
    simInt.setValor(3, 3, 40);

    std::cout << "\n--- Grid Inicial (Paso 0) ---\n";
    simInt.visualizarGrid();
    simInt.simularPaso(); 
    std::cout << "\n--- Grid Después del Paso 1 ---\n";
    simInt.visualizarGrid();
    
    // Fin, los destructores de todos los objetos se llamarán al final de main()
    return 0;
}