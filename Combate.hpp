#ifndef __COMBATE_HPP__
#define __COMBATE_HPP__

#include "Personaje.hpp"
#include "Enums.hpp"

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
        Personaje * personajeJugador1;

        // Personaje asignado al jugador 2
        Personaje * personajeJugador2;

        // Escenario para el combate
        //Escenario escenario;

        // Ronda actual
        int numeroRonda;

    public:

        // Construye el combate en base a los identificadores de los personajes
        // y al escenario en el que se va a pelear
        Combate(IDPersonaje idPersonajeJ1, IDPersonaje idPersonajeJ2, IDEscenario idEscenario);

        // Libera los personajes
        ~Combate();

        // Comienza el combate (la clase pasa a tomar el control de
        // la ventana principal hasta que termine el combate)
        void comenzar();

};

#endif // __COMBATE_HPP__
