#include "ControladorJuego.h"
#include <iostream>
#include <algorithm>
#include <limits>
using namespace std;

/**
 * Constructor que inicializa el controlador del juego
 */
ControladorJuego::ControladorJuego() 
    : crupier(make_unique<Crupier>()), estadoActual(EstadoJuego::INICIAL), 
      rondaActual(0), juegoTerminado(false) {}

/**
 * Agrega un jugador al juego
 */
void ControladorJuego::agregarJugador(const string& nombre, double dineroInicial) {
    jugadores.push_back(make_unique<JugadorHumano>(nombre, dineroInicial));
}

/**
 * Inicia el juego principal
 */
void ControladorJuego::iniciarJuego() {
    cout << "\n========================================" << endl;
    cout << "       BIENVENIDO AL BLACKJACK" << endl;
    cout << "========================================" << endl;

    // Si no hay jugadores, permitir agregar múltiples
    if (jugadores.empty()) {
        int numJugadores;
        cout << "¿Cuántos jugadores van a jugar? (1-4): ";
        cin >> numJugadores;
        cin.ignore();
        
        // Validar número de jugadores
        if (numJugadores < 1 || numJugadores > 4) {
            numJugadores = 1;
            cout << "Número inválido. Se establecerá 1 jugador." << endl;
        }
        
        // Agregar cada jugador
        for (int i = 1; i <= numJugadores; i++) {
            string nombre;
            cout << "Ingresa el nombre del jugador " << i << ": ";
            getline(cin, nombre);
            if (nombre.empty()) {
                nombre = "Jugador" + to_string(i);
            }
            agregarJugador(nombre);
            cout << "Jugador agregado: " << nombre << " con $1000" << endl;
        }
    }

    estadoActual = EstadoJuego::APOSTANDO;

    // Bucle principal del juego
    while (!juegoTerminado && puedenContinuar()) {
        procesarRonda();

        // Preguntar si quiere continuar
        if (puedenContinuar()) {
            char respuesta;
            cout << "\n¿Quieres jugar otra ronda? (s/n): ";
            cin >> respuesta;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (respuesta != 's' && respuesta != 'S') {
                juegoTerminado = true;
            }
        }
    }

    mostrarEstadisticas();
    cout << "\n¡Gracias por jugar!" << endl;
}

/**
 * Procesa una ronda completa del juego
 */
void ControladorJuego::procesarRonda() {
    rondaActual++;
    cout << "\n========================================" << endl;
    cout << "             RONDA " << rondaActual << endl;
    cout << "========================================" << endl;

    // Limpiar manos de la ronda anterior
    limpiarManos();

    // Secuencia de estados del juego
    estadoActual = EstadoJuego::APOSTANDO;
    manejarEstadoApostando();

    estadoActual = EstadoJuego::REPARTIENDO;
    manejarEstadoRepartiendo();

    estadoActual = EstadoJuego::TURNO_JUGADOR;
    manejarTurnoJugadores();

    estadoActual = EstadoJuego::TURNO_CRUPIER;
    manejarTurnoCrupier();

    estadoActual = EstadoJuego::DETERMINANDO_GANADOR;
    determinarGanadores();

    estadoActual = EstadoJuego::FINALIZADO;
}

/**
 * Maneja el estado de apuestas
 */
void ControladorJuego::manejarEstadoApostando() {
    cout << "\n--- FASE DE APUESTAS ---" << endl;

    for (auto& jugador : jugadores) {
        if (jugador->obtenerDinero() > 0) {
            double apuesta = jugador->solicitarApuesta();
            if (apuesta > 0) {
                jugador->apostar(apuesta);
                cout << jugador->obtenerNombre() << " apuesta $" << apuesta << endl;
            } else {
                cout << jugador->obtenerNombre() << " no apuesta esta ronda." << endl;
            }
        }
    }
}

/**
 * Maneja el estado de reparto de cartas iniciales
 */
void ControladorJuego::manejarEstadoRepartiendo() {
    cout << "\n--- REPARTIENDO CARTAS INICIALES ---" << endl;

    // Repartir cartas iniciales a todos los jugadores
    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0) {
            crupier->repartirCartasIniciales(jugador.get());
        }
    }

    // Repartir cartas iniciales al crupier
    crupier->repartirCartasIniciales(crupier.get());

    // Mostrar cartas iniciales
    cout << "\nCartas iniciales:" << endl;
    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0) {
            jugador->mostrarMano();
        }
    }

    crupier->mostrarManoParcial();

    // Verificar Blackjacks
    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0 && jugador->obtenerMano().esBlackjack()) {
            cout << "\n¡" << jugador->obtenerNombre() << " tiene Blackjack!" << endl;
        }
    }
}

/**
 * Maneja el turno de los jugadores
 */
void ControladorJuego::manejarTurnoJugadores() {
    cout << "\n--- TURNO DE LOS JUGADORES ---" << endl;

    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0 && !jugador->obtenerMano().esBlackjack()) {
            procesarTurnoJugador(jugador.get());
        }
    }
}

/**
 * Procesa el turno de un jugador individual
 */
void ControladorJuego::procesarTurnoJugador(JugadorHumano* jugador) {
    cout << "\nTurno de " << jugador->obtenerNombre() << ":" << endl;

    while (jugador->quiereOtraCarta() && !jugador->obtenerMano().sePaso()) {
        auto carta = crupier->repartirCarta();
        if (carta != nullptr) {
            jugador->recibirCarta(carta);
            cout << "Recibes: " << carta->toString() << endl;
        }
    }

    if (jugador->obtenerMano().sePaso()) {
        cout << "¡" << jugador->obtenerNombre() << " se pasó de 21!" << endl;
    } else {
        cout << jugador->obtenerNombre() << " se planta con " << jugador->obtenerMano().calcularValor() << endl;
    }
}

/**
 * Maneja el turno del crupier
 */
void ControladorJuego::manejarTurnoCrupier() {
    // Solo jugar si hay jugadores que no se hayan pasado
    bool hayJugadoresEnJuego = false;
    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0 && !jugador->obtenerMano().sePaso()) {
            hayJugadoresEnJuego = true;
            break;
        }
    }

    if (hayJugadoresEnJuego) {
        crupier->jugarTurno();
    } else {
        cout << "\nTodos los jugadores se pasaron. El crupier no necesita jugar." << endl;
        crupier->mostrarManoCompleta();
    }
}

/**
 * Determina los ganadores y paga las apuestas
 */
void ControladorJuego::determinarGanadores() {
    cout << "\n--- DETERMINANDO GANADORES ---" << endl;

    for (auto& jugador : jugadores) {
        if (jugador->obtenerApuestaActual() > 0) {
            int resultado = crupier->determinarGanador(jugador.get());
            double apuesta = jugador->obtenerApuestaActual();

            cout << "\n" << jugador->obtenerNombre() << ": ";

            if (resultado == 1) {
                // Jugador gana
                if (jugador->obtenerMano().esBlackjack()) {
                    double pago = calcularPagoBlackjack(apuesta);
                    jugador->ganar(apuesta + pago);
                    cout << "¡BLACKJACK! Ganas $" << pago << " (apuesta devuelta)";
                } else {
                    jugador->ganar(apuesta * 2);
                    cout << "¡GANAS! Recibes $" << apuesta;
                }
            } else if (resultado == 0) {
                // Empate
                jugador->ganar(apuesta);
                cout << "EMPATE. Apuesta devuelta.";
            } else {
                // Jugador pierde (apuesta ya fue descontada)
                cout << "PIERDES. Apuesta perdida.";
            }
        }
    }
}

/**
 * Calcula el pago por Blackjack (3:2)
 */
double ControladorJuego::calcularPagoBlackjack(double apuesta) const {
    return apuesta * 1.5;  // 3:2 = 1.5
}

/**
 * Verifica si los jugadores pueden continuar
 */
bool ControladorJuego::puedenContinuar() const {
    for (const auto& jugador : jugadores) {
        if (jugador->obtenerDinero() > 0) {
            return true;
        }
    }
    return false;
}

/**
 * Limpia las manos para una nueva ronda
 */
void ControladorJuego::limpiarManos() {
    for (auto& jugador : jugadores) {
        jugador->reiniciarMano();
    }
    crupier->reiniciarMano();
}

/**
 * Muestra las estadísticas finales
 */
void ControladorJuego::mostrarEstadisticas() const {
    cout << "\n========================================" << endl;
    cout << "           ESTADÍSTICAS FINALES" << endl;
    cout << "========================================" << endl;
    cout << "Rondas jugadas: " << rondaActual << endl;
    cout << "Cartas restantes en el mazo: " << crupier->obtenerCartasRestantes() << endl;

    cout << "\nEstado final de los jugadores:" << endl;
    for (const auto& jugador : jugadores) {
        cout << "- " << jugador->obtenerInfo() << endl;
    }
}

/**
 * Verifica si el juego ha terminado
 */
bool ControladorJuego::haTerminado() const {
    return juegoTerminado;
}

/**
 * Obtiene el estado actual del juego
 */
EstadoJuego ControladorJuego::obtenerEstadoActual() const {
    return estadoActual;
}

/**
 * Muestra el menú principal
 */
void ControladorJuego::mostrarMenuPrincipal() const {
    cout << "\n========================================" << endl;
    cout << "              MENÚ PRINCIPAL" << endl;
    cout << "========================================" << endl;
    cout << "1. Jugar nueva ronda" << endl;
    cout << "2. Ver estadísticas" << endl;
    cout << "3. Salir" << endl;
    cout << "========================================" << endl;
}