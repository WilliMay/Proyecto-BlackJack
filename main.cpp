
#include <iostream>
#include <string>
#include "ControladorJuego.h"
using namespace std;

// Declaración de la función de pruebas (definida en PruebasUnitarias.cpp)
void ejecutarPruebasUnitarias();

int main()
{
    int opcion;
    cout << "========================================" << endl;
    cout << "           BLACKJACK GAME" << endl;
    cout << "========================================" << endl;
    cout << "1. Jugar Blackjack" << endl;
    cout << "2. Ejecutar Pruebas Unitarias" << endl;
    cout << "3. Salir" << endl;
    cout << "Selecciona una opción: ";
    cin >> opcion;
    cin.ignore(); // Limpiar buffer

    switch(opcion){
        case 1: {
            cout << "Iniciando juego de Blackjack..." << endl;
            ControladorJuego juego;
            juego.iniciarJuego();
            break;
        }
        case 2: {
            cout << "Ejecutando pruebas unitarias..." << endl;
            system("make clean");
            system("make pruebas");
            system("./pruebas");
            break;
        }
        case 3:
            cout << "¡Hasta luego!" << endl;
            break;
        default:
            cout << "Opción no válida" << endl;
    }
    return 0;
}
