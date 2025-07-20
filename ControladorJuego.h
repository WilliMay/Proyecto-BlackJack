#ifndef CONTROLADOR_JUEGO_H
#define CONTROLADOR_JUEGO_H

#include "Crupier.h"
#include "JugadorHumano.h"
#include <vector>
#include <memory>
using namespace std;

/**
 * @enum EstadoJuego
 * @brief Enumeración que representa los diferentes estados del juego
 */
enum class EstadoJuego {
    INICIAL,
    APOSTANDO,
    REPARTIENDO,
    TURNO_JUGADOR,
    TURNO_CRUPIER,
    DETERMINANDO_GANADOR,
    FINALIZADO
};

/**
 * @class ControladorJuego
 * @brief Clase controladora que gestiona el flujo del juego de Blackjack
 * 
 * Esta clase implementa el patrón Controller y State para manejar
 * el flujo del juego, las interacciones entre jugadores y crupier,
 * y la aplicación de las reglas del Blackjack.
 */
class ControladorJuego {
private:
    unique_ptr<Crupier> crupier;                    ///< Crupier del juego
    vector<unique_ptr<JugadorHumano>> jugadores;    ///< Lista de jugadores
    EstadoJuego estadoActual;                       ///< Estado actual del juego
    int rondaActual;                                ///< Número de ronda actual
    bool juegoTerminado;                            ///< Flag para terminar el juego

    /**
     * @brief Maneja el estado de apuestas
     * @post Los jugadores realizan sus apuestas
     */
    void manejarEstadoApostando();

    /**
     * @brief Maneja el estado de reparto de cartas
     * @post Se reparten las cartas iniciales
     */
    void manejarEstadoRepartiendo();

    /**
     * @brief Maneja el turno de los jugadores
     * @post Los jugadores toman sus decisiones
     */
    void manejarTurnoJugadores();

    /**
     * @brief Maneja el turno del crupier
     * @post El crupier juega automáticamente
     */
    void manejarTurnoCrupier();

    /**
     * @brief Determina los ganadores y paga las apuestas
     * @post Se determinan los resultados y se pagan las apuestas
     */
    void determinarGanadores();

    /**
     * @brief Verifica si algún jugador tiene dinero para continuar
     * @return true si al menos un jugador puede continuar, false en caso contrario
     */
    bool puedenContinuar() const;

    /**
     * @brief Limpia las manos para una nueva ronda
     * @post Todas las manos se reinician
     */
    void limpiarManos();

    /**
     * @brief Muestra el estado actual del juego
     * @post Imprime información relevante en consola
     */
    void mostrarEstadoJuego() const;

    /**
     * @brief Procesa el turno de un jugador individual
     * @param jugador Puntero al jugador
     * @post El jugador toma cartas hasta plantarse o pasarse
     */
    void procesarTurnoJugador(JugadorHumano* jugador);

    /**
     * @brief Calcula el pago por Blackjack (3:2)
     * @param apuesta Apuesta original
     * @return Cantidad a pagar por Blackjack
     */
    double calcularPagoBlackjack(double apuesta) const;

public:
    /**
     * @brief Constructor de la clase ControladorJuego
     * @post Inicializa el juego con un crupier
     */
    ControladorJuego();

    /**
     * @brief Destructor de la clase ControladorJuego
     */
    ~ControladorJuego() = default;

    /**
     * @brief Agrega un jugador al juego
     * @param nombre Nombre del jugador
     * @param dineroInicial Dinero inicial del jugador
     * @post Se agrega un nuevo jugador al juego
     */
    void agregarJugador(const string& nombre, double dineroInicial = 1000.0);

    /**
     * @brief Inicia el juego principal
     * @post Ejecuta el bucle principal del juego
     */
    void iniciarJuego();

    /**
     * @brief Muestra el menú principal
     * @post Imprime las opciones disponibles
     */
    void mostrarMenuPrincipal() const;

    /**
     * @brief Muestra las estadísticas finales
     * @post Imprime las estadísticas de todos los jugadores
     */
    void mostrarEstadisticas() const;

    /**
     * @brief Verifica si el juego ha terminado
     * @return true si el juego terminó, false en caso contrario
     */
    bool haTerminado() const;

    /**
     * @brief Procesa una ronda completa del juego
     * @post Ejecuta una ronda desde apuestas hasta determinar ganadores
     */
    void procesarRonda();

    /**
     * @brief Obtiene el estado actual del juego
     * @return Estado actual del juego
     */
    EstadoJuego obtenerEstadoActual() const;
};

#endif // CONTROLADOR_JUEGO_H