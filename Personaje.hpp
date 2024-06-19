#ifndef __PERSONAJE_HPP__
#define __PERSONAJE_HPP__

#include "AnimacionPorFrames.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <list>

/*
    Esta clase abstracta define las cualidades de un personaje genérico
    Los personajes creados deben heredar de esta clase obligatoriamente e implementar
    todas las funciones por su cuenta, incluyendo el constructor
*/
class Personaje : public sf::Drawable {

    private:

        // Cantidad actual de puntos de vida
        int puntosDeVida;

        // Jugador al que está asociado el personaje
        Jugador jugador;

        // Estado en el que se encuentra el personaje
        EstadoPersonaje estado;

        // Animación del personaje según el estado
        std::map<EstadoPersonaje,Animacion*> animaciones;

        // Indica qué acciones están siendo realizadas
        std::map<Accion,bool> accionesRealizadas;

    public:

        // Construye el personaje
        Personaje(std::map<EstadoPersonaje,Animacion*> animaciones);

        // Indica que se está pulsando un botón
        void realizarAccion(Accion accion);

        // Indica que se ha soltado un botón
        void detenerAccion(Accion accion);

        // Actualiza la posición del personaje y demás según los botones que estén pulsados
        virtual void actualizar() = 0;

        // Comprueba si la hitbox del personaje ha colisionado con algún ataque enemigo y
        // reacciona de forma adecuada
        virtual void comprobarColisiones(std::list<Animacion*> &animaciones) = 0;

        // Devuelve los puntos de vida actuales
        int getPuntosDeVida();

        // Establece el jugador asociado
        void setJugador(Jugador jugador);

        // Cambia el estado
        void cambiarEstado(EstadoPersonaje estadoNuevo);

        // Devuelve un puntero a un clon del personaje
        virtual Personaje * clonar() = 0;

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

};

#endif // __PERSONAJE_HPP__
