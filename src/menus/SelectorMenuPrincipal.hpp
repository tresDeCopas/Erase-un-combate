#pragma once

#include "Animacion.hpp"
#include <list>
#include <SFML/Graphics.hpp>
#include "Enums.hpp"

/*
    Esta es una clase auxiliar para guardar los selectores para
    cada uno de los sitios a los que puedes ir desde el menú principal
*/
class SelectorMenuPrincipal : public sf::Drawable {
    private:
        // El sprite asociado al selector
        sf::Sprite spriteSelector;

        // Indica a qué selección hace referencia este selector
        TipoSelectorMenuPrincipal tipoSelector;
        
        // La posición relativa a la que se encuentra este selector.
        // Por ejemplo, supongamos que este es el primer selector del vector
        // de selectores del menú principal (posición cero). Si el jugador acaba
        // de abrir el juego, este será el selector elegido por defecto, y su
        // posición relativa es 0. Si el jugador baja dos selectores más abajo,
        // ahora la posición relativa es 2 (se encuentra dos posiciones arriba del
        // selector en el que se encuentra el jugador)
        int posicionRelativa;
    
    public:
        // Se crea el selector en base a su textura para el sprite y el tipo de
        // selección al que hace referencia
        SelectorMenuPrincipal(sf::Texture& texturaSelector, TipoSelectorMenuPrincipal tipoSelector);

        // Se reestablece el selector a su estado inicial
        void resetear();

        // Se elige el selector, así que sale un brillito y nos vamos al menú seleccionado
        void seleccionar(std::list<std::shared_ptr<Animacion>>& nuevasAnimaciones);

        // Se actualiza la posición y la transparencia del selector y su fondo
        void actualizar();

        // Se lleva el selector a la posición exacta a la que debería estar, y también
        // se pone la escala correcta inmediatemente en vez de esperar a que lo haga
        void ajustarPosicion();

        // Permite dibujar el selector
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;

        // Establece el valor de la posición relativa
        void setPosicionRelativa(int posicionRelativa)
        {
            this->posicionRelativa = posicionRelativa;
        }

        // Devuelve el tipo de selector
        TipoSelectorMenuPrincipal getTipoSelector()
        {
            return tipoSelector;
        }

        // Devuelve una referencia al sprite del selector
        sf::Sprite& getSprite()
        {
            return spriteSelector;
        }
};