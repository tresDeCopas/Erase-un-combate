#ifndef __ANIMACION_HPP__
#define __ANIMACION_HPP__

#include "Hitbox.hpp"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include <list>
#include <memory>

/*
    Clase abstracta para cualquier tipo de animaciones
*/
class Animacion : public sf::Drawable {
    protected:
        // Sprite para la animaci�n
        sf::Sprite sprite;

        // Sonido para la animaci�n
        sf::Sound sonido;

    public:

        // Actualiza la animaci�n (avanza un frame)
        virtual void actualizar() = 0;

        // Resetea la animaci�n al estado inicial
        virtual void resetear() = 0;

        // Le da la vuelta al sprite
        virtual void voltear();

        // Coloca el sprite en la posici�n indicada con respecto a la esquina superior
        // izquierda de la ventana
        void setPosicion(float x, float y);
        void setPosicion(sf::Vector2f posicion);

        // Establece la rotación del sprite en grados centígrados
        void setRotacion(double angulo);

        // Devuelve la posici�n actual del sprite (teniendo en cuenta el origen, sea cual sea)
        sf::Vector2f getPosicion();

        // Devuelve la posición de la esquina superior izquierda del sprite (es decir, no tiene en
        // cuenta el origen que pueda tener)
        sf::Vector2f getPosicionEsqSupIzq() const;

        // Devuelve una lista con las hitboxes
        virtual std::list<Hitbox> getHitboxes() = 0;

        // Mueve la posici�n del sprite con respecto a la posici�n actual
        void mover(float x, float y);
        void mover(sf::Vector2f diferencia);

        // Determina si una animaci�n ha terminado
        virtual bool haTerminado() = 0;

        // Devuelve un clon de la animaci�n
        virtual std::shared_ptr<Animacion> clonar() = 0;

        // Indica a la animación que acaba de chocar contra una hitbox (SE SUPONE QUE
        // LA HITBOX VIENE CON SU POSICION RELATIVA A LA PARTE DE ARRIBA A LA IZQUIERDA)
        virtual void chocar(Hitbox hitbox);

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __ANIMACION_HPP__
