#include "Crupier.h"
#include <iostream>
#include <thread>
#include <chrono>
using namespace std;

/**
 * Constructor que inicializa el crupier con un mazo nuevo
 */
Crupier::Crupier() : Jugador("Crupier", 0), mazo(make_unique<Mazo>()) {}

/**
 * Implementación polimórfica de la regla del crupier
 * El crupier debe pedir carta si tiene menos de 17
 */
bool Crupier::quiereOtraCarta() const {
    return mano.calcularValor() < 17;
}

/**
 * Reparte una carta del mazo
 */
shared_ptr<Carta> Crupier::repartirCarta() {
    if (mazo->estaVacio()) {
        cout << "¡El mazo está vacío! Reiniciando..." << endl;
        mazo->reiniciar();
    }
    return mazo->repartirCarta();
}

/**
 * Reparte las cartas iniciales a un jugador (2 cartas)
 */
void Crupier::repartirCartasIniciales(Jugador* jugador) {
    if (jugador == nullptr) return;

    // Repartir 2 cartas iniciales
    for (int i = 0; i < 2; i++) {
        auto carta = repartirCarta();
        if (carta != nullptr) {
            jugador->recibirCarta(carta);
        }
    }
}

/**
 * Juega el turno del crupier automáticamente
 */
void Crupier::jugarTurno() {
    cout << "\nTurno del crupier:" << endl;
    cout << "El crupier revela su mano:" << endl;
    mostrarManoCompleta();

    // Pausa para dramatismo
    this_thread::sleep_for(chrono::milliseconds(1000));

    // Pedir cartas mientras sea necesario
    while (quiereOtraCarta() && !mano.sePaso()) {
        cout << "\nEl crupier pide una carta..." << endl;
        auto carta = repartirCarta();
        if (carta != nullptr) {
            recibirCarta(carta);
            cout << "El crupier recibe: " << carta->toString() << endl;
            cout << "Mano del crupier: " << mano.toString() << endl;

            // Pausa para dramatismo
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    }

    // Resultado final
    if (mano.sePaso()) {
        cout << "\n¡El crupier se pasó de 21!" << endl;
    } else {
        cout << "\nEl crupier se planta con " << mano.calcularValor() << endl;
    }
}

/**
 * Muestra la mano del crupier parcialmente (carta oculta)
 */
void Crupier::mostrarManoParcial() const {
    cout << "Crupier - " << mano.toStringParcial() << endl;
}

/**
 * Muestra la mano completa del crupier
 */
void Crupier::mostrarManoCompleta() const {
    cout << "Crupier - " << mano.toString() << endl;
}

/**
 * Determina el ganador comparando con un jugador
 * Retorna: 1 = jugador gana, 0 = empate, -1 = crupier gana
 */
int Crupier::determinarGanador(const Jugador* jugador) const {
    if (jugador == nullptr) return -1;

    const Mano& manoJugador = jugador->obtenerMano();
    int valorJugador = manoJugador.calcularValor();
    int valorCrupier = mano.calcularValor();

    // Si el jugador se pasó, pierde
    if (manoJugador.sePaso()) {
        return -1;
    }

    // Si el crupier se pasó y el jugador no, el jugador gana
    if (mano.sePaso()) {
        return 1;
    }

    // Si ambos tienen Blackjack, es empate
    if (manoJugador.esBlackjack() && mano.esBlackjack()) {
        return 0;
    }

    // Si solo el jugador tiene Blackjack, gana
    if (manoJugador.esBlackjack()) {
        return 1;
    }

    // Si solo el crupier tiene Blackjack, gana
    if (mano.esBlackjack()) {
        return -1;
    }

    // Comparar valores
    if (valorJugador > valorCrupier) {
        return 1;  // Jugador gana
    } else if (valorJugador < valorCrupier) {
        return -1; // Crupier gana
    } else {
        return 0;  // Empate
    }
}

/**
 * Reinicia el mazo completo
 */
void Crupier::reiniciarMazo() {
    mazo->reiniciar();
}

/**
 * Obtiene el número de cartas restantes en el mazo
 */
int Crupier::obtenerCartasRestantes() const {
    return mazo->cartasRestantes();
}

/**
 * Reinicia la mano del crupier
 */
void Crupier::reiniciarMano() {
    mano.limpiar();
}