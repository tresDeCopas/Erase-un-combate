#ifndef __ANIMACION_POR_FRAMES_HPP__
#define __ANIMACION_POR_FRAMES_HPP__

#include "Enums.hpp"
#include "Hitbox.hpp"
#include "Animacion.hpp"
#include <SFML/Graphics.hpp>
#include <list>
#include <map>

/*
    Esta clase define animaciones para personajes y ataques formadas por varios frames
    Cada animación puede tener asociado cualquier número de hitboxes
*/
class AnimacionPorFrames : public Animacion {
    private:

        // Tipo de repetición en bucle
        TipoBucle tipoBucle;

        // Si tipoBucle es PING_PONG, indica si la animación va hacia delante o hacia atrás
        bool pingPongHaciaDelante;

        // Si tipoBucle no es SIN_BUCLE, indica cuántas veces se repetirá la animación (0 es infinito)
        int numRepeticionesTotal;

        // Si numRepeticionesTotal no es 0, indica cuántas veces se ha repetido la animación de momento
        int numRepeticionesActual;

        // Correspondencia entre rectángulo y hitboxes
        std::map<int,std::list<Hitbox>> hitboxes;

        // Correspondencia entre frame y rectángulo (por ejemplo, frame 0 rectángulo 0, o frame 5 rectángulo 2)
        std::map<int,int> rectanguloCorrespondiente;

        // Número de frame actual
        unsigned int frameActual;

    public:

        // Constructor
        AnimacionPorFrames(int posicionX, int posicionY, int origenX, int origenY, int numRectangulos, sf::Texture &textura, TipoBucle tipoBucle, int numRepeticionesTotal, std::map<int,std::list<Hitbox>> hitboxes, std::map<int,int> rectanguloCorrespondiente);

        // Actualiza la animación (avanza un frame)
        virtual void actualizar();

        // Devuelve qué rectángulo se está mostrando actualmente
        int getNumeroRectangulo();

        // Cambia el tipo de bucle para la animación
        void setTipoBucle(TipoBucle tipoBucle);

        // Resetea la animación al primer frame y el primer rectángulo
        virtual void resetear();

        // Devuelve un clon de la animación
        virtual Animacion * clonar();

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __ANIMACION_POR_FRAMES_HPP__
