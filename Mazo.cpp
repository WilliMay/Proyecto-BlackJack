#include "Mazo.h"
#include <algorithm>
#include <random>
#include <chrono>
using namespace std;

/**
 * Constructor que inicializa y baraja el mazo
 */
Mazo::Mazo() : indiceCarta(0) {
    inicializarMazo();
    barajar();
}

/**
 * Inicializa el mazo con las 52 cartas estándar
 * 4 palos × 13 valores = 52 cartas
 */
void Mazo::inicializarMazo() {
    vector<string> palos = {"Corazones", "Diamantes", "Tréboles", "Picas"};
    vector<string> valores = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};

    cartas.clear();

    // Crear todas las combinaciones de cartas
    for (const string& palo : palos) {
        for (const string& valor : valores) {
            cartas.push_back(make_shared<Carta>(valor, palo));
        }
    }

    indiceCarta = 0;
}

/**
 * Baraja las cartas usando un generador aleatorio
 */
void Mazo::barajar() {
    // Usar tiempo actual como semilla para mayor aleatoriedad
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    shuffle(cartas.begin(), cartas.end(), default_random_engine(seed));
    indiceCarta = 0;
}

/**
 * Reparte la siguiente carta disponible
 */
shared_ptr<Carta> Mazo::repartirCarta() {
    if (estaVacio()) {
        return nullptr;  // No hay cartas disponibles
    }

    return cartas[indiceCarta++];
}

/**
 * Calcula cuántas cartas quedan por repartir
 */
int Mazo::cartasRestantes() const {
    return cartas.size() - indiceCarta;
}

/**
 * Verifica si se han repartido todas las cartas
 */
bool Mazo::estaVacio() const {
    return indiceCarta >= cartas.size();
}

/**
 * Reinicia el mazo completo y lo baraja
 */
void Mazo::reiniciar() {
    inicializarMazo();
    barajar();
}