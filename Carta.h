#ifndef CARTA_H
#define CARTA_H

#include <string>
using namespace std;

/**
 * @class Carta
 * @brief Representa una carta individual del juego de Blackjack
 * 
 * Esta clase encapsula la información de una carta, incluyendo su valor y palo.
 * Implementa la lógica específica para el cálculo del valor en Blackjack.
 */
class Carta {
private:
    string valor;  ///< Valor de la carta (A, 2-10, J, Q, K)
    string palo;   ///< Palo de la carta (Corazones, Diamantes, Tréboles, Picas)

public:
    /**
     * @brief Constructor de la clase Carta
     * @param valor Valor de la carta
     * @param palo Palo de la carta
     * @pre valor debe ser un valor válido de carta
     * @post Crea una carta con el valor y palo especificados
     */
    Carta(const string& valor, const string& palo);

    /**
     * @brief Obtiene el valor numérico de la carta para Blackjack
     * @return Valor numérico de la carta (1-11)
     * @post Retorna el valor correspondiente según las reglas de Blackjack
     */
    int obtenerValorNumerico() const;

    /**
     * @brief Obtiene el valor de la carta como string
     * @return Valor de la carta
     */
    string obtenerValor() const;

    /**
     * @brief Obtiene el palo de la carta
     * @return Palo de la carta
     */
    string obtenerPalo() const;

    /**
     * @brief Verifica si la carta es un As
     * @return true si es un As, false en caso contrario
     */
    bool esAs() const;

    /**
     * @brief Convierte la carta a string para mostrar
     * @return Representación en string de la carta
     */
    string toString() const;
};

#endif // CARTA_H