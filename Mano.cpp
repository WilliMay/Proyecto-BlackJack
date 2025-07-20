#include "Mano.h"
#include <sstream>
using namespace std;

/**
 * Constructor que inicializa una mano vacía
 */
Mano::Mano() {}

/**
 * Agrega una carta a la mano
 */
void Mano::agregarCarta(shared_ptr<Carta> carta) {
    if (carta != nullptr) {
        cartas.push_back(carta);
    }
}

/**
 * Calcula el valor total de la mano considerando los Ases
 * Los Ases pueden valer 1 u 11 dependiendo de qué sea mejor
 */
int Mano::calcularValor() const {
    int valor = 0;
    int ases = 0;

    // Sumar valores base y contar Ases
    for (const auto& carta : cartas) {
        if (carta->esAs()) {
            ases++;
            valor += 11;  // Inicialmente contar As como 11
        } else {
            valor += carta->obtenerValorNumerico();
        }
    }

    // Ajustar Ases de 11 a 1 si es necesario
    while (valor > 21 && ases > 0) {
        valor -= 10;  // Cambiar un As de 11 a 1
        ases--;
    }

    return valor;
}

/**
 * Obtiene el número de cartas en la mano
 */
int Mano::obtenerNumeroCartas() const {
    return cartas.size();
}

/**
 * Verifica si la mano es Blackjack (21 con exactamente 2 cartas)
 */
bool Mano::esBlackjack() const {
    return obtenerNumeroCartas() == 2 && calcularValor() == 21;
}

/**
 * Verifica si la mano se pasó de 21
 */
bool Mano::sePaso() const {
    return calcularValor() > 21;
}

/**
 * Limpia todas las cartas de la mano
 */
void Mano::limpiar() {
    cartas.clear();
}

/**
 * Obtiene todas las cartas de la mano
 */
vector<shared_ptr<Carta>> Mano::obtenerCartas() const {
    return cartas;
}

/**
 * Convierte la mano completa a string
 */
string Mano::toString() const {
    if (cartas.empty()) {
        return "Mano vacía";
    }

    stringstream ss;
    ss << "Cartas: ";
    for (size_t i = 0; i < cartas.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << cartas[i]->toString();
    }
    ss << " (Valor: " << calcularValor() << ")";
    return ss.str();
}

/**
 * Muestra la mano parcialmente (solo primera carta)
 * Usado para mostrar la mano del crupier durante el juego
 */
string Mano::toStringParcial() const {
    if (cartas.empty()) {
        return "Mano vacía";
    }

    stringstream ss;
    ss << "Cartas: " << cartas[0]->toString();
    if (cartas.size() > 1) {
        ss << ", [Carta oculta]";
    }
    return ss.str();
}