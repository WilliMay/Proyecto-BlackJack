#include "Carta.h"
using namespace std;

/**
 * Constructor que inicializa una carta con su valor y palo
 */
Carta::Carta(const string& valor, const string& palo) : valor(valor), palo(palo) {}

/**
 * Calcula el valor numérico de la carta según las reglas de Blackjack
 * - As vale 11 (el ajuste a 1 se maneja en la clase Mano)
 * - Figuras (J, Q, K) valen 10
 * - Cartas numéricas valen su número
 */
int Carta::obtenerValorNumerico() const {
    if (valor == "A") {
        return 11;  // Por defecto, el As vale 11
    } else if (valor == "J" || valor == "Q" || valor == "K") {
        return 10;  // Todas las figuras valen 10
    } else {
        return stoi(valor);  // Cartas numéricas valen su número
    }
}

/**
 * Getter para el valor de la carta
 */
string Carta::obtenerValor() const {
    return valor;
}

/**
 * Getter para el palo de la carta
 */
string Carta::obtenerPalo() const {
    return palo;
}

/**
 * Verifica si la carta es un As
 */
bool Carta::esAs() const {
    return valor == "A";
}

/**
 * Convierte la carta a una representación legible
 */
string Carta::toString() const {
    return valor + " de " + palo;
}