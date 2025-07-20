#ifndef MANO_H
#define MANO_H

#include "Carta.h"
#include <vector>
#include <memory>
using namespace std;

/**
 * @class Mano
 * @brief Representa una mano de cartas en el juego de Blackjack
 * 
 * Esta clase gestiona las cartas que tiene un jugador o crupier,
 * calcula el valor total y maneja la lógica especial de los Ases.
 */
class Mano {
private:
    vector<shared_ptr<Carta>> cartas;  ///< Vector de cartas en la mano

public:
    /**
     * @brief Constructor de la clase Mano
     * @post Crea una mano vacía
     */
    Mano();

    /**
     * @brief Destructor virtual para permitir herencia
     */
    virtual ~Mano() = default;

    /**
     * @brief Agrega una carta a la mano
     * @param carta Puntero compartido a la carta a agregar
     * @pre carta no debe ser nullptr
     * @post La carta se agrega a la mano
     */
    void agregarCarta(shared_ptr<Carta> carta);

    /**
     * @brief Calcula el valor total de la mano
     * @return Valor total de las cartas en la mano
     * @post Retorna el mejor valor posible sin exceder 21 si es posible
     */
    virtual int calcularValor() const;

    /**
     * @brief Obtiene el número de cartas en la mano
     * @return Número de cartas
     */
    int obtenerNumeroCartas() const;

    /**
     * @brief Verifica si la mano es Blackjack
     * @return true si es Blackjack (21 con 2 cartas), false en caso contrario
     */
    bool esBlackjack() const;

    /**
     * @brief Verifica si la mano se pasó de 21
     * @return true si el valor excede 21, false en caso contrario
     */
    bool sePaso() const;

    /**
     * @brief Limpia todas las cartas de la mano
     * @post La mano queda vacía
     */
    void limpiar();

    /**
     * @brief Obtiene todas las cartas de la mano
     * @return Vector de punteros compartidos a las cartas
     */
    vector<shared_ptr<Carta>> obtenerCartas() const;

    /**
     * @brief Convierte la mano a string para mostrar
     * @return Representación en string de la mano
     */
    string toString() const;

    /**
     * @brief Muestra la mano parcialmente (solo primera carta)
     * @return String con la primera carta visible
     */
    string toStringParcial() const;
};

#endif // MANO_H