#ifndef CRUPIER_H
#define CRUPIER_H

#include "Jugador.h"
#include "Mazo.h"
#include <memory>
using namespace std;

/**
 * @class Crupier
 * @brief Representa al crupier en el juego de Blackjack
 * 
 * Esta clase hereda de Jugador e implementa la lógica específica del crupier,
 * incluyendo las reglas automáticas para pedir cartas y gestionar el mazo.
 * Demuestra herencia y polimorfismo.
 */
class Crupier : public Jugador {
private:
    unique_ptr<Mazo> mazo;  ///< Mazo de cartas que maneja el crupier

public:
    /**
     * @brief Constructor de la clase Crupier
     * @post Crea un crupier con un mazo nuevo
     */
    Crupier();

    /**
     * @brief Destructor de la clase Crupier
     */
    ~Crupier() override = default;

    /**
     * @brief Implementación polimórfica para decidir si quiere otra carta
     * @return true si el valor de la mano es menor a 17, false en caso contrario
     * @post Aplica la regla estándar del crupier (pedir hasta 17)
     */
    bool quiereOtraCarta() const override;

    /**
     * @brief Reparte una carta del mazo
     * @return Puntero compartido a la carta repartida
     * @pre El mazo no debe estar vacío
     * @post Se remueve una carta del mazo
     */
    shared_ptr<Carta> repartirCarta();

    /**
     * @brief Reparte las cartas iniciales a un jugador
     * @param jugador Puntero al jugador que recibe las cartas
     * @pre jugador no debe ser nullptr
     * @post El jugador recibe 2 cartas iniciales
     */
    void repartirCartasIniciales(Jugador* jugador);

    /**
     * @brief Juega el turno del crupier automáticamente
     * @post El crupier pide cartas según las reglas hasta alcanzar 17 o más
     */
    void jugarTurno();

    /**
     * @brief Muestra la mano del crupier parcialmente
     * @post Muestra solo la primera carta, ocultando la segunda
     */
    void mostrarManoParcial() const;

    /**
     * @brief Muestra la mano completa del crupier
     * @post Muestra todas las cartas y el valor total
     */
    void mostrarManoCompleta() const;

    /**
     * @brief Determina el resultado entre el crupier y un jugador
     * @param jugador Puntero al jugador a comparar
     * @return 1 si gana el jugador, 0 si empate, -1 si gana el crupier
     * @pre jugador no debe ser nullptr
     */
    int determinarGanador(const Jugador* jugador) const;

    /**
     * @brief Reinicia el mazo para una nueva partida
     * @post El mazo se reinicia y se baraja
     */
    void reiniciarMazo();

    /**
     * @brief Obtiene el número de cartas restantes en el mazo
     * @return Número de cartas que quedan en el mazo
     */
    int obtenerCartasRestantes() const;

    /**
     * @brief Reinicia la mano del crupier para una nueva ronda
     * @post La mano se limpia
     */
    void reiniciarMano();
};

#endif // CRUPIER_H