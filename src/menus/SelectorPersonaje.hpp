#pragma once

#include "Enums.hpp"
#include <SFML/Graphics.hpp>

/*
    Esta es una clase auxiliar para guardar los selectores para
    cada uno de los personajes que se pueden elegir
*/
class SelectorPersonaje : public sf::Drawable
{
    private:
        // El sprite asociado al selector
        sf::Sprite spriteSelector;

        // El sprite con el nombre del personaje
        sf::Sprite spriteNombrePersonaje;

        // Un borde cuadrado que rodea al sprite del selector
        sf::RectangleShape bordeCuadrado;

        // Indica el nombre del personaje al que hace referencia este selector
        std::string nombrePersonaje;
        
        // La posición relativa a la que se encuentra este selector.
        // Por ejemplo, supongamos que este es el primer selector del vector
        // de selectores (posición cero). Si el jugador acaba de abrir el menú
        // de selección de personaje, este será el selector elegido por defecto, y su
        // posición relativa es 0. Si el jugador se mueve dos selectores a la derecha,
        // ahora la posición relativa es -2 (se encuentra dos posiciones a la izquierda del
        // selector en el que se encuentra el jugador)
        int posicionRelativa;

        // El jugador al que pertenece este selector
        Jugador jugador;
    
    public:
        // Se crea el selector
        SelectorPersonaje(const sf::Texture& texturaSelector, const std::string& nombrePersonaje, Jugador jugador, int posicionRelativa);

        // Se reestablece el selector a su estado inicial (excepto la posición relativa,
        // eso se lo tienes que poner tú antes de resetear)
        void resetear(int posicionRelativa);

        // Se elige el selector, así que sale un brillito y el personaje es elegido
        void seleccionar();

        // Se actualiza la posición y la transparencia del selector y su fondo
        void actualizar();

        // Permite dibujar el selector
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        // Establece el valor de la posición relativa
        void setPosicionRelativa(int posicionRelativa)
        {
            this->posicionRelativa = posicionRelativa;
        }

        // Devuelve el nombre del personaje
        std::string getNombrePersonaje()
        {
            return nombrePersonaje;
        }

        // Devuelve una referencia al sprite del selector
        sf::Sprite& getSprite()
        {
            return spriteSelector;
        }
};
