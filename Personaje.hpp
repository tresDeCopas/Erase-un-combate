#ifndef __PERSONAJE_HPP__
#define __PERSONAJE_HPP__

#include "AnimacionPorFrames.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <list>

/*
    Esta clase define las cualidades de un personaje genérico, pudiendo ser
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

        // Verdadero si el personaje está mirando hacia la derecha (el enemigo está a la derecha)
        bool mirandoDerecha;

        // Jugador al que está asociado el personaje
        Jugador jugador;

        // Estado en el que se encuentra el personaje
        EstadoPersonaje estado;

        // Animación del personaje según el estado
        std::map<EstadoPersonaje,Animacion*> animaciones;

        // Indica qué acciones están siendo realizadas
        std::map<Accion,bool> accionesRealizadas;

        // Función auxiliar para moverse un poco a la derecha
        void moverseDerecha();

        // Función auxiliar para moverse un poco a la izquierda
        void moverseIzquierda();

        // Función auxiliar para disminuir la velocidad un poco hacia 0
        void pararMovimiento();

    public:

        // Construye el personaje
        Personaje(std::map<EstadoPersonaje,Animacion*> animaciones);

        // Indica que se está pulsando un botón
        void realizarAccion(Accion accion);

        // Indica que se ha soltado un botón
        void detenerAccion(Accion accion);

        // Actualiza la posición del personaje y demás según los botones que estén pulsados
        virtual void actualizar(sf::Vector2f posicionEnemigo);

        // Comprueba si la hitbox del personaje ha colisionado con algún ataque enemigo y
        // reacciona de forma adecuada
        virtual void comprobarColisiones(std::list<Animacion*> &animaciones);

        // Devuelve los puntos de vida actuales
        int getPuntosDeVida();

        // Establece el jugador asociado
        void setJugador(Jugador jugador);

        // Cambia el estado
        void cambiarEstado(EstadoPersonaje estadoNuevo);

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // __PERSONAJE_HPP__
