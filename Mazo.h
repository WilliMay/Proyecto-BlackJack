#ifndef MAZO_H
#define MAZO_H

#include "Carta.h"
#include <vector>
#include <memory>
using namespace std;

/**
 * @class Mazo
 * @brief Representa un mazo de cartas para el juego de Blackjack
 * 
 * Esta clase gestiona el conjunto de cartas, su inicialización, barajado
 * y reparto. Implementa encapsulamiento ocultando la estructura interna.
 */
class Mazo {
private:
    vector<shared_ptr<Carta>> cartas;  ///< Vector de cartas en el mazo
    int indiceCarta;                   ///< Índice de la próxima carta a repartir

    /**
     * @brief Inicializa el mazo con las 52 cartas estándar
     * @post El mazo contiene todas las cartas de una baraja estándar
     */
    void inicializarMazo();

public:
    /**
     * @brief Constructor de la clase Mazo
     * @post Crea un mazo completo y lo baraja
     */
    Mazo();

    /**
     * @brief Baraja las cartas del mazo
     * @post Las cartas están en orden aleatorio
     */
    void barajar();

    /**
     * @brief Reparte la siguiente carta del mazo
     * @return Puntero compartido a la carta repartida
     * @pre Debe haber cartas disponibles en el mazo
     * @post La carta es removida del mazo disponible
     */
    shared_ptr<Carta> repartirCarta();

    /**
     * @brief Obtiene el número de cartas restantes en el mazo
     * @return Número de cartas que quedan por repartir
     */
    int cartasRestantes() const;

    /**
     * @brief Verifica si el mazo está vacío
     * @return true si no hay cartas, false en caso contrario
     */
    bool estaVacio() const;

    /**
     * @brief Reinicia el mazo completo
     * @post El mazo vuelve a tener todas las cartas barajadas
     */
    void reiniciar();
};

#endif // MAZO_H