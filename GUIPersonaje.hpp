#ifndef __GUI_PERSONAJE_HPP__
#define __GUI_PERSONAJE_HPP__

#include "Personaje.hpp"
#include "SFML/Graphics.hpp"

// Una GUI (Graphical User Interface (Interfaz gráfica de usuario)) es una
// forma que tienen los programas informáticos de mostrar información hacia fuera.
// En este caso, esta GUI muestra la barra de vida de un personaje, una foto suya,
// el medidor de súper ataque, su nombre y el número de rondas que ha ganado
class GUIPersonaje : public sf::Drawable {

    private:

        // El personaje del que esta GUI muestra información
        Personaje& personaje;

        // El sprite principal de la GUI (base y frente (la base es el fondo y el
        // frente son los medidores transparentes que hay en las barras de
        // vida y de súper))
        sf::Sprite spritePrincipalBase;
        sf::Sprite spritePrincipalFrente;
    
    public:

        // Construye la GUI dada una referencia a un personaje
        GUIPersonaje(Personaje &personaje);

        // Actualiza la GUI en base a los datos del personaje
        void actualizar();

        // Dibuja la GUI en pantalla
        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif