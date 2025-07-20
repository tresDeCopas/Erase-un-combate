#ifndef __GESTOR_DE_CONTROLES_HPP__
#define __GESTOR_DE_CONTROLES_HPP__

#include <SFML/Graphics.hpp>
#include "ContenedorDeRecursos.hpp"
#include "Enums.hpp"
#include <map>
#include <vector>

/*
    Clase que se encarga de la correspondencia entre jugadores y controles,
    además de indicar qué significan las teclas y botones que se pulsan
*/
class GestorDeControles
{
    protected:
        GestorDeControles();
        static GestorDeControles * gestorDeControles;

    private:

        // Mapa que guarda, para cada control, el jugador al que está asignado
        std::map<Control, Jugador> controlAJugador;

        // Mapa que guarda, para cada tecla válida (excepto la tecla de salir), la parte del teclado y la acción asociada
        std::map<sf::Keyboard::Key,std::pair<Control,Accion>> teclaAControlYAccion;

        // Función que indica si un control está libre
        bool estaLibre(Control c);

    public:

        // Dado un evento, devuelve el jugador y la acción que está haciendo
        std::pair<Jugador,Accion> comprobarEvento(sf::Event evento);

        // Permite establecer un mando para que lo use un jugador
        bool conectarMando(Jugador j, Control c);

        // NUNCA SE COPIA UN SINGLETON
        GestorDeControles(GestorDeControles &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const GestorDeControles &) = delete;

        // Devuelve la única instancia
        static GestorDeControles * unicaInstancia();
};

#endif // __GESTOR_DE_CONTROLES_HPP__
