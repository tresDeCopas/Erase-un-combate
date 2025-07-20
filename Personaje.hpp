#ifndef __PERSONAJE_HPP__
#define __PERSONAJE_HPP__

#include "AnimacionPorFrames.hpp"
#include "Enums.hpp"
#include <SFML/Graphics.hpp>
#include <map>
#include <list>
#include <memory>

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
        std::map<EstadoPersonaje,std::shared_ptr<Animacion>> animaciones;

        // Indica qué acciones están siendo realizadas
        std::map<Accion,bool> accionesRealizadas;

        // Función auxiliar para moverse un poco a la derecha
        void moverseDerecha();

        // Función auxiliar para moverse un poco a la izquierda
        void moverseIzquierda();

        // Función auxiliar para disminuir la velocidad un poco hacia 0
        void pararMovimiento();

        // Función auxiliar para mostrar dos nubes de polvo a los pies del personaje
        void levantarPolvo(std::list<std::shared_ptr<Animacion>> &efectosInsertados);

    public:

        // Construye el personaje
        Personaje(std::map<EstadoPersonaje,std::shared_ptr<Animacion>> animaciones);

        // Indica que se está pulsando un botón
        void realizarAccion(Accion accion);

        // Indica que se ha soltado un botón
        void detenerAccion(Accion accion);

        // Actualiza la posición del personaje y demás según los botones que están pulsados
        virtual void actualizar(sf::Vector2f posicionEnemigo, std::list<std::shared_ptr<Animacion>> &efectosInsertados);

        // Comprueba si la hitbox del personaje ha colisionado con algún ataque enemigo y
        // reacciona de forma adecuada
        virtual void comprobarColisiones(std::list<std::shared_ptr<Animacion>> &animaciones, std::list<std::shared_ptr<Animacion>> &efectosInsertados);

        // Devuelve los puntos de vida actuales
        int getPuntosDeVida();

        // Establece la posición del personaje
        void setPosicion(float x, float y);
        void setPosicion(sf::Vector2f posicion);

        // Devuelve la posición del personaje
        sf::Vector2f getPosicion();

        // Devuelve el estado actual del personaje
        EstadoPersonaje getEstado();

        // Establece el jugador asociado
        void setJugador(Jugador jugador);

        // Devuelve el mapa de animaciones
        std::map<EstadoPersonaje,std::shared_ptr<Animacion>> getAnimaciones();

        // Establece el mapa de animaciones
        void setAnimaciones(std::map<EstadoPersonaje,std::shared_ptr<Animacion>> animaciones);

        // Cambia el estado
        void cambiarEstado(EstadoPersonaje estadoNuevo);

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif // __PERSONAJE_HPP__
