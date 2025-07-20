#ifndef __COMBATE_HPP__
#define __COMBATE_HPP__

#include "Personaje.hpp"
#include "Enums.hpp"
#include "GUIPersonaje.hpp"
#include "AnimacionAgrandable.hpp"

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

        // GUI para el personaje asignado al jugador 2
        GUIPersonaje GUIJugador2;

        // Escenario para el combate
        //Escenario escenario;

        // Rectángulo negro que aparece antes de que empiece el combate y entre rondas
        sf::RectangleShape rectanguloOscuro;

        // Ronda actual
        int numeroRonda;

        // Indica qué jugador se debe actualizar primero en el turno actual. Esto sirve para que no sea
        // siempre el primer jugador el que se actualiza primero, causando situaciones raras e injustas
        Jugador primerJugadorParaActualizar;

        // Cartel que aparece al principio de la ronda en el que pone "¿Todo listo?"
        std::shared_ptr<Animacion> cartelTodoListo;

        // Cartel que aparece al principio de la ronda en el que pone "¡A pelear!"
        std::shared_ptr<Animacion> cartelAPelear;

        // Cartel que aparece al terminar una ronda en el que pone "¡Gana el jugador 1!"
        std::shared_ptr<Animacion> cartelGanaJugador1;

        // Cartel que aparece al terminar una ronda en el que pone "¡Gana el jugador 2!"
        std::shared_ptr<Animacion> cartelGanaJugador2;

    public:

        // Construye el combate en base a los nombres de los personajes
        // y del escenario en el que se va a pelear. Lo demás es común a todos
        // los combates
        Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario);

        // Comienza el combate (la clase pasa a tomar el control de
        // la ventana principal hasta que termine el combate)
        void comenzar();

};

#endif // __COMBATE_HPP__
