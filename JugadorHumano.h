#ifndef JUGADOR_HUMANO_H
#define JUGADOR_HUMANO_H

#include "Jugador.h"
using namespace std;

/**
 * @class JugadorHumano
 * @brief Representa un jugador humano en el juego de Blackjack
 * 
 * Esta clase hereda de Jugador e implementa la funcionalidad específica
 * para un jugador humano, incluyendo interacción por consola.
 * Demuestra el uso de herencia y polimorfismo.
 */
class JugadorHumano : public Jugador {
public:
    /**
     * @brief Constructor de la clase JugadorHumano
     * @param nombre Nombre del jugador humano
     * @param dineroInicial Dinero inicial del jugador
     * @post Crea un jugador humano con el nombre y dinero especificados
     */
    JugadorHumano(const string& nombre, double dineroInicial = 1000.0);

    /**
     * @brief Destructor de la clase JugadorHumano
     */
    ~JugadorHumano() override = default;

    /**
     * @brief Pregunta al jugador si quiere otra carta (polimorfismo)
     * @return true si quiere otra carta, false en caso contrario
     * @post Muestra la mano actual y solicita decisión del usuario
     */
    bool quiereOtraCarta() const override;

    /**
     * @brief Solicita al jugador que realice una apuesta
     * @return Cantidad apostada (0 si no quiere apostar)
     * @post Muestra información del jugador y solicita apuesta
     */
    double solicitarApuesta() const;

    /**
     * @brief Muestra la mano actual del jugador
     * @post Imprime la mano y el valor total en consola
     */
    void mostrarMano() const;
};

#endif // JUGADOR_HUMANO_H