#ifndef __PERSONAJE_HPP__
#define __PERSONAJE_HPP__

#include "AnimacionPorFrames.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <list>
#include <memory>

/*
    Esta clase define las cualidades de un personaje gen�rico, pudiendo ser
    utilizada por todos los posibles personajes al ser estos lo suficientemente
    parecidos como para compartir clase
*/
class Personaje : public sf::Drawable {

    private:

        // Cantidad actual de puntos de vida
        int puntosDeVida;

        // Velocidad en el eje Y
        float velY;

        // Velocidad en el eje X
        float velX;

        // Verdadero si el personaje est� mirando hacia la derecha (el enemigo est� a la derecha)
        bool mirandoDerecha;

        // Jugador al que est� asociado el personaje
        Jugador jugador;

        // Estado en el que se encuentra el personaje
        EstadoPersonaje estado;

        // Animaci�n del personaje seg�n el estado
        std::map<EstadoPersonaje,Animacion*> animaciones;

        // Indica qu� acciones est�n siendo realizadas
        std::map<Accion,bool> accionesRealizadas;

        // Funci�n auxiliar para moverse un poco a la derecha
        void moverseDerecha();

        // Funci�n auxiliar para moverse un poco a la izquierda
        void moverseIzquierda();

        // Funci�n auxiliar para disminuir la velocidad un poco hacia 0
        void pararMovimiento();

    public:

        // Construye el personaje
        Personaje(std::map<EstadoPersonaje,Animacion*> animaciones);

        // Indica que se est� pulsando un bot�n
        void realizarAccion(Accion accion);

        // Indica que se ha soltado un bot�n
        void detenerAccion(Accion accion);

        // Actualiza la posici�n del personaje y dem�s seg�n los botones que est�n pulsados
        virtual void actualizar(sf::Vector2f posicionEnemigo);

        // Comprueba si la hitbox del personaje ha colisionado con alg�n ataque enemigo y
        // reacciona de forma adecuada
        virtual void comprobarColisiones(std::list<Animacion*> &animaciones, std::list<Animacion*> &efectosInsertados);

        // Devuelve los puntos de vida actuales
        int getPuntosDeVida();

        // Establece la posici�n del personaje
        void setPosicion(float x, float y);
        void setPosicion(sf::Vector2f posicion);

        // Devuelve la posici�n del personaje
        sf::Vector2f getPosicion();

        // Devuelve el estado actual del personaje
        EstadoPersonaje getEstado();

        // Establece el jugador asociado
        void setJugador(Jugador jugador);

        // Devuelve el mapa de animaciones
        std::map<EstadoPersonaje,Animacion*> getAnimaciones();

        // Establece el mapa de animaciones
        void setAnimaciones(std::map<EstadoPersonaje,Animacion*> animaciones);

        // Cambia el estado
        void cambiarEstado(EstadoPersonaje estadoNuevo);

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // __PERSONAJE_HPP__
