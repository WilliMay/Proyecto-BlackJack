#include "Jugador.h"
#include <sstream>
using namespace std;

/**
 * Constructor que inicializa un jugador con nombre y dinero inicial
 */
Jugador::Jugador(const string& nombre, double dineroInicial) 
    : nombre(nombre), dinero(dineroInicial), apuestaActual(0.0) {}

/**
 * Recibe una carta y la agrega a la mano
 */
void Jugador::recibirCarta(shared_ptr<Carta> carta) {
    mano.agregarCarta(carta);
}

/**
 * Realiza una apuesta si es válida
 */
bool Jugador::apostar(double cantidad) {
    if (cantidad > 0 && cantidad <= dinero) {
        dinero -= cantidad;
        apuestaActual = cantidad;
        return true;
    }
    return false;
}

/**
 * Gana dinero de una apuesta
 */
void Jugador::ganar(double cantidad) {
    dinero += cantidad;
}

/**
 * Implementación base para decidir si quiere otra carta
 * Esta implementación siempre retorna false y debe ser sobrescrita
 */
bool Jugador::quiereOtraCarta() const {
    return false;  // Implementación por defecto
}

/**
 * Reinicia la mano para una nueva ronda
 */
void Jugador::reiniciarMano() {
    mano.limpiar();
    apuestaActual = 0.0;
}

/**
 * Getter para el nombre del jugador
 */
string Jugador::obtenerNombre() const {
    return nombre;
}

/**
 * Getter para la mano del jugador (versión mutable)
 */
Mano& Jugador::obtenerMano() {
    return mano;
}

/**
 * Getter para la mano del jugador (versión constante)
 */
const Mano& Jugador::obtenerMano() const {
    return mano;
}

/**
 * Getter para el dinero del jugador
 */
double Jugador::obtenerDinero() const {
    return dinero;
}

/**
 * Getter para la apuesta actual
 */
double Jugador::obtenerApuestaActual() const {
    return apuestaActual;
}

/**
 * Verifica si el jugador puede realizar una apuesta
 */
bool Jugador::puedeApostar(double cantidad) const {
    return cantidad > 0 && cantidad <= dinero;
}

/**
 * Obtiene información completa del jugador
 */
string Jugador::obtenerInfo() const {
    stringstream ss;
    ss << "Jugador: " << nombre << " | Dinero: $" << dinero;
    if (apuestaActual > 0) {
        ss << " | Apuesta actual: $" << apuestaActual;
    }
    return ss.str();
}