#ifndef JUGADOR_H
#define JUGADOR_H

#include "Mano.h"
#include <string>
using namespace std;

/**
 * @class Jugador
 * @brief Clase base que representa un jugador en el juego de Blackjack
 * 
 * Esta clase implementa la funcionalidad básica de un jugador,
 * incluyendo gestión de la mano, dinero y decisiones de juego.
 * Utiliza herencia para permitir diferentes tipos de jugadores.
 */
class Jugador {
protected:
    string nombre;           ///< Nombre del jugador
    Mano mano;              ///< Mano de cartas del jugador
    double dinero;          ///< Dinero disponible del jugador
    double apuestaActual;   ///< Apuesta actual del jugador

public:
    /**
     * @brief Constructor de la clase Jugador
     * @param nombre Nombre del jugador
     * @param dineroInicial Dinero inicial del jugador
     * @post Crea un jugador con el nombre y dinero especificados
     */
    Jugador(const string& nombre, double dineroInicial = 1000.0);

    /**
     * @brief Destructor virtual para permitir herencia
     */
    virtual ~Jugador() = default;

    /**
     * @brief Recibe una carta y la agrega a la mano
     * @param carta Puntero compartido a la carta recibida
     * @pre carta no debe ser nullptr
     * @post La carta se agrega a la mano del jugador
     */
    void recibirCarta(shared_ptr<Carta> carta);

    /**
     * @brief Realiza una apuesta
     * @param cantidad Cantidad a apostar
     * @return true si la apuesta es válida, false en caso contrario
     * @pre cantidad debe ser positiva y menor o igual al dinero disponible
     * @post Si es válida, se descuenta del dinero y se establece como apuesta actual
     */
    bool apostar(double cantidad);

    /**
     * @brief Gana dinero por una apuesta
     * @param cantidad Cantidad ganada
     * @post El dinero se suma al total del jugador
     */
    void ganar(double cantidad);

    /**
     * @brief Decide si quiere otra carta (implementación virtual)
     * @return true si quiere otra carta, false en caso contrario
     */
    virtual bool quiereOtraCarta() const;

    /**
     * @brief Reinicia la mano para una nueva ronda
     * @post La mano se limpia y la apuesta actual se reinicia
     */
    void reiniciarMano();

    // Getters
    string obtenerNombre() const;
    Mano& obtenerMano();
    const Mano& obtenerMano() const;
    double obtenerDinero() const;
    double obtenerApuestaActual() const;

    /**
     * @brief Verifica si el jugador puede apostar una cantidad
     * @param cantidad Cantidad a verificar
     * @return true si puede apostar esa cantidad, false en caso contrario
     */
    bool puedeApostar(double cantidad) const;

    /**
     * @brief Obtiene información del jugador
     * @return String con información del jugador
     */
    string obtenerInfo() const;
};

#endif // JUGADOR_H