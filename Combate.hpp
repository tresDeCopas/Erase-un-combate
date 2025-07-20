#ifndef __COMBATE_HPP__
#define __COMBATE_HPP__

#include "Personaje.hpp"
#include "Enums.hpp"
#include "GUIPersonaje.hpp"

/*
    Esta clase define un combate, formado por dos jugadores, cada
    uno manejando un personaje. El combate tiene varias rondas,
    las cuales terminan cuando uno de los personajes llega a 0 puntos de
    vida. A las 2 rondas ganadas por parte de uno de los personajes, el
    combate termina.
*/
class Combate{
    private:

        // Personaje asignado al jugador 1
        Personaje personajeJugador1;

        // Personaje asignado al jugador 2
        Personaje personajeJugador2;

        // GUI para el personaje asignado al jugador 1
        GUIPersonaje GUIJugador1;

        // Escenario para el combate
        //Escenario escenario;

        // Ronda actual
        int numeroRonda;

    public:

        // Construye el combate en base a los nombres de los personajes
        // y del escenario en el que se va a pelear
        Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario);

        // Comienza el combate (la clase pasa a tomar el control de
        // la ventana principal hasta que termine el combate)
        void comenzar();

};

#endif // __COMBATE_HPP__
