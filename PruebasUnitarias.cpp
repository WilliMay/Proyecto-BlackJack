
#include "Carta.h"
#include "Mazo.h"
#include "Mano.h"
#include "Jugador.h"
#include "JugadorHumano.h"
#include "Crupier.h"
#include "ControladorJuego.h"
#include <iostream>
#include <cassert>
#include <memory>
#include <functional>
using namespace std;

/**
 * @brief Clase para ejecutar pruebas unitarias del proyecto Blackjack
 * 
 * Esta clase implementa pruebas unitarias usando assert para verificar
 * el correcto funcionamiento de cada método de cada clase.
 */
class PruebasUnitarias {
private:
    int pruebasEjecutadas = 0;
    int pruebasExitosas = 0;

    /**
     * @brief Ejecuta una prueba individual
     * @param nombrePrueba Nombre de la prueba
     * @param prueba Función lambda que ejecuta la prueba
     */
    void ejecutarPrueba(const string& nombrePrueba, function<void()> prueba) {
        try {
            cout << "Ejecutando: " << nombrePrueba << "... ";
            prueba();
            cout << "EXITOSA" << endl;
            pruebasExitosas++;
        } catch (const exception& e) {
            cout << "FALLIDA: " << e.what() << endl;
        } catch (...) {
            cout << "FALLIDA: Error desconocido" << endl;
        }
        pruebasEjecutadas++;
    }

    /**
     * @brief Pruebas para la clase Carta
     */
    void pruebasCarta() {
        cout << "\n--- PRUEBAS CLASE CARTA ---" << endl;

        ejecutarPrueba("Constructor de Carta", []() {
            Carta carta("A", "Corazones");
            assert(carta.obtenerValor() == "A");
            assert(carta.obtenerPalo() == "Corazones");
        });

        ejecutarPrueba("Valor numérico del As", []() {
            Carta as("A", "Picas");
            assert(as.obtenerValorNumerico() == 11);
        });

        ejecutarPrueba("Valor numérico de figura", []() {
            Carta rey("K", "Diamantes");
            assert(rey.obtenerValorNumerico() == 10);
        });

        ejecutarPrueba("Valor numérico de carta normal", []() {
            Carta cinco("5", "Tréboles");
            assert(cinco.obtenerValorNumerico() == 5);
        });

        ejecutarPrueba("Verificar si es As", []() {
            Carta as("A", "Corazones");
            Carta rey("K", "Picas");
            assert(as.esAs() == true);
            assert(rey.esAs() == false);
        });

        ejecutarPrueba("toString de Carta", []() {
            Carta carta("Q", "Diamantes");
            assert(carta.toString() == "Q de Diamantes");
        });
    }

    /**
     * @brief Pruebas para la clase Mazo
     */
    void pruebasMazo() {
        cout << "\n--- PRUEBAS CLASE MAZO ---" << endl;

        ejecutarPrueba("Constructor de Mazo", []() {
            Mazo mazo;
            assert(mazo.cartasRestantes() == 52);
            assert(!mazo.estaVacio());
        });

        ejecutarPrueba("Repartir carta", []() {
            Mazo mazo;
            auto carta = mazo.repartirCarta();
            assert(carta != nullptr);
            assert(mazo.cartasRestantes() == 51);
        });

        ejecutarPrueba("Reiniciar mazo", []() {
            Mazo mazo;
            mazo.repartirCarta();
            mazo.reiniciar();
            assert(mazo.cartasRestantes() == 52);
        });
    }

    /**
     * @brief Pruebas para la clase Mano
     */
    void pruebasMano() {
        cout << "\n--- PRUEBAS CLASE MANO ---" << endl;

        ejecutarPrueba("Mano vacía", []() {
            Mano mano;
            assert(mano.calcularValor() == 0);
            assert(!mano.esBlackjack());
            assert(!mano.sePaso());
        });

        ejecutarPrueba("Agregar carta a mano", []() {
            Mano mano;
            auto carta = make_shared<Carta>("K", "Picas");
            mano.agregarCarta(carta);
            assert(mano.calcularValor() == 10);
        });

        ejecutarPrueba("Blackjack con As y figura", []() {
            Mano mano;
            mano.agregarCarta(make_shared<Carta>("A", "Corazones"));
            mano.agregarCarta(make_shared<Carta>("K", "Picas"));
            assert(mano.esBlackjack());
            assert(mano.calcularValor() == 21);
        });

        ejecutarPrueba("Mano que se pasa", []() {
            Mano mano;
            mano.agregarCarta(make_shared<Carta>("K", "Picas"));
            mano.agregarCarta(make_shared<Carta>("Q", "Corazones"));
            mano.agregarCarta(make_shared<Carta>("5", "Diamantes"));
            assert(mano.sePaso());
            assert(mano.calcularValor() > 21);
        });
    }

    /**
     * @brief Pruebas para la clase Jugador
     */
    void pruebasJugador() {
        cout << "\n--- PRUEBAS CLASE JUGADOR ---" << endl;

        ejecutarPrueba("Constructor de Jugador", []() {
            JugadorHumano jugador("Test", 100.0);
            assert(jugador.obtenerNombre() == "Test");
            assert(jugador.obtenerDinero() == 100.0);
            assert(jugador.obtenerApuestaActual() == 0.0);
        });

        ejecutarPrueba("Realizar apuesta válida", []() {
            JugadorHumano jugador("Test", 100.0);
            assert(jugador.apostar(50.0) == true);
            assert(jugador.obtenerDinero() == 50.0);
            assert(jugador.obtenerApuestaActual() == 50.0);
        });

        ejecutarPrueba("Apuesta inválida", []() {
            JugadorHumano jugador("Test", 100.0);
            assert(jugador.apostar(150.0) == false);
            assert(jugador.obtenerDinero() == 100.0);
        });

        ejecutarPrueba("Ganar dinero", []() {
            JugadorHumano jugador("Test", 100.0);
            jugador.ganar(50.0);
            assert(jugador.obtenerDinero() == 150.0);
        });
    }

    /**
     * @brief Pruebas para la clase Crupier
     */
    void pruebasCrupier() {
        cout << "\n--- PRUEBAS CLASE CRUPIER ---" << endl;

        ejecutarPrueba("Constructor de Crupier", []() {
            Crupier crupier;
            assert(crupier.obtenerCartasRestantes() == 52);
        });

        ejecutarPrueba("Repartir carta", []() {
            Crupier crupier;
            auto carta = crupier.repartirCarta();
            assert(carta != nullptr);
            assert(crupier.obtenerCartasRestantes() == 51);
        });
    }

    /**
     * @brief Pruebas para la clase ControladorJuego
     */
    void pruebasControladorJuego() {
        cout << "\n--- PRUEBAS CLASE CONTROLADOR JUEGO ---" << endl;

        ejecutarPrueba("Constructor de ControladorJuego", []() {
            ControladorJuego controlador;
            assert(!controlador.haTerminado());
        });

        ejecutarPrueba("Agregar jugador", []() {
            ControladorJuego controlador;
            controlador.agregarJugador("TestPlayer", 100.0);
            // No hay getter directo para verificar, pero no debe fallar
        });
    }

public:
    /**
     * @brief Ejecuta todas las pruebas unitarias
     */
    void ejecutarTodasLasPruebas() {
        cout << "\n========================================" << endl;
        cout << "         EJECUTANDO PRUEBAS UNITARIAS" << endl;
        cout << "========================================" << endl;

        pruebasCarta();
        pruebasMazo();
        pruebasMano();
        pruebasJugador();
        pruebasCrupier();
        pruebasControladorJuego();

        cout << "\n========================================" << endl;
        cout << "           RESULTADOS FINALES" << endl;
        cout << "========================================" << endl;
        cout << "Pruebas ejecutadas: " << pruebasEjecutadas << endl;
        cout << "Pruebas exitosas: " << pruebasExitosas << endl;
        cout << "Pruebas fallidas: " << (pruebasEjecutadas - pruebasExitosas) << endl;
        
        if (pruebasExitosas == pruebasEjecutadas) {
            cout << "¡TODAS LAS PRUEBAS PASARON!" << endl;
        } else {
            cout << "Algunas pruebas fallaron." << endl;
        }
    }
};

/**
 * @brief Función principal para ejecutar las pruebas
 */
int main() {
    PruebasUnitarias pruebas;
    pruebas.ejecutarTodasLasPruebas();
    return 0;
}
