#include "JugadorHumano.h"
#include <iostream>
#include <limits>
using namespace std;

/**
 * Constructor que inicializa un jugador humano
 */
JugadorHumano::JugadorHumano(const string& nombre, double dineroInicial) 
    : Jugador(nombre, dineroInicial) {}

/**
 * Implementación polimórfica para decidir si quiere otra carta
 * Interactúa con el usuario a través de la consola
 */
bool JugadorHumano::quiereOtraCarta() const {
    char respuesta;
    cout << "\n" << nombre << ", tu mano actual:" << endl;
    cout << mano.toString() << endl;

    // Verificar si ya se pasó
    if (mano.sePaso()) {
        cout << "¡Te pasaste de 21!" << endl;
        return false;
    }

    cout << "¿Quieres otra carta? (s/n): ";
    cin >> respuesta;

    // Limpiar buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    return (respuesta == 's' || respuesta == 'S');
}

/**
 * Solicita al jugador que realice una apuesta
 */
double JugadorHumano::solicitarApuesta() const {
    double cantidad;

    cout << "\n" << obtenerInfo() << endl;
    cout << "¿Cuánto quieres apostar? (0 para no apostar): $";

    while (!(cin >> cantidad)) {
        cout << "Por favor ingresa un número válido: $";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    // Limpiar buffer de entrada
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Validar que la cantidad sea válida
    if (cantidad < 0) {
        cout << "La cantidad no puede ser negativa." << endl;
        return 0;
    }

    if (cantidad > dinero) {
        cout << "No tienes suficiente dinero. Máximo: $" << dinero << endl;
        return 0;
    }

    return cantidad;
}

/**
 * Muestra la mano actual del jugador
 */
void JugadorHumano::mostrarMano() const {
    cout << "\n" << nombre << " - " << mano.toString() << endl;
}