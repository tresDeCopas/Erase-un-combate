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
    Cada animaci�n puede tener asociado cualquier n�mero de hitboxes
*/
class AnimacionPorFrames : public Animacion {
    private:

        // Tipo de repetici�n en bucle
        TipoBucle tipoBucle;

        // Si tipoBucle es PING_PONG, indica si la animaci�n va hacia delante o hacia atr�s
        bool pingPongHaciaDelante;

        // Si tipoBucle no es SIN_BUCLE, indica cu�ntas veces se repetir� la animaci�n (0 es infinito)
        int numRepeticionesTotal;

        // Si numRepeticionesTotal no es 0, indica cu�ntas veces se ha repetido la animaci�n de momento
        int numRepeticionesActual;

        // Correspondencia entre rect�ngulo y hitboxes
        std::map<int,std::list<Hitbox>> hitboxes;

        // Correspondencia entre frame y rect�ngulo (por ejemplo, frame 0 rect�ngulo 0, o frame 5 rect�ngulo 2)
        std::map<int,int> rectanguloCorrespondiente;

        // Indica qu� frames deben hacer sonar el sonido de la animaci�n
        std::set<int> framesConSonido;

        // Indica si el sonido se debe repetir cada vez que vuelva a salir el frame o si una vez se
        // termine el bucle no hay que repetirlo
        bool repetirSonido;

        // Si repetirSonido est� a false, indica si el sonido ya se ha reproducido durante todo un bucle,
        // por lo que habr�a que resetear la animaci�n para que volviera a sonar
        bool sonidoYaReproducido;

        // N�mero de frame actual
        int frameActual;

        // Indica si es el primer frame, para no ir al siguiente (si no, nunca se mostraría el primer frame al actualizarlo inmediatamente)
        bool primerFrame;

    public:

        // Constructor sin sonido
        AnimacionPorFrames(int posicionX, int posicionY, int origenX, int origenY, int numRectangulos, sf::Texture &textura, TipoBucle tipoBucle, int numRepeticionesTotal, std::map<int,std::list<Hitbox>> hitboxes, std::map<int,int> rectanguloCorrespondiente);

        // Constructor con sonido
        AnimacionPorFrames(int posicionX, int posicionY, int origenX, int origenY, int numRectangulos, sf::Texture &textura, TipoBucle tipoBucle, int numRepeticionesTotal, std::map<int,std::list<Hitbox>> hitboxes, std::map<int,int> rectanguloCorrespondiente, sf::Sound sonido, std::set<int> framesConSonido, bool repetirSonido);

        // Actualiza la animaci�n (avanza un frame)
        virtual void actualizar();

        // Le da la vuelta al sprite
        virtual void voltear();

        // Devuelve qu� rect�ngulo se est� mostrando actualmente
        int getNumeroRectangulo();

        // Devuelve qué frame se está mostrando actualmente
        int getNumeroFrame();

        // Cambia el tipo de bucle para la animaci�n
        void setTipoBucle(TipoBucle tipoBucle);

        // Devuelve si ha terminado la animaci�n (si el tipo de bucle es "SIN_BUCLE")
        bool haTerminado();

        // Resetea la animaci�n al primer frame y el primer rect�ngulo
        virtual void resetear();

        // Devuelve un clon de la animaci�n
        virtual std::shared_ptr<Animacion> clonar();

        // Devuelve una lista con las hitboxes del frame actual
        virtual std::list<Hitbox> getHitboxes();

        // Las clases que heredan de sf::Drawable deben implementar draw
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __ANIMACION_POR_FRAMES_HPP__
