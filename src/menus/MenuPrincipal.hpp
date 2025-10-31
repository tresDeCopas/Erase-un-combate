#pragma once

#include "Animacion.hpp"
#include <memory>
#include <vector>

/*
    Especifica el tipo de un selector del menú principal
*/
enum class TipoSelectorMenuPrincipal {
    MODO_HISTORIA, BATALLA_VS, OPCIONES,
};

/*
    Esta es una clase auxiliar para guardar los selectores para
    cada uno de los sitios a los que puedes ir desde el menú principal
*/
class SelectorMenuPrincipal {
    private:
        // El sprite asociado al selector
        sf::Sprite spriteSelector;

        // El fondo asociado al selector
        sf::Sprite spriteFondo;

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
        // Se crea el selector en base a su textura para el sprite, su textura para
        // el fondo y el tipo de selección al que hace referencia
        SelectorMenuPrincipal(sf::Texture& texturaSelector, sf::Texture& texturaFondo, TipoSelectorMenuPrincipal tipoSelector);

        // Se reestablece el selector a su estado inicial
        void resetear();

        // Se elige el selector, así que sale un brillito y nos vamos al menú seleccionado
        void seleccionar();

        // Se actualiza la posición y la transparencia del selector y su fondo
        void actualizar();

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

        // Devuelve una referencia al sprite del fondo
        sf::Sprite& getFondo()
        {
            return spriteFondo;
        }
};

/*
    Esta clase representa el menú principal en el que puedes elegir el modo
    de juego que quieres jugar o entrar en opciones para cambiar cosicas.
*/
class MenuPrincipal {
    private:
        // El constructor es privado porque la clase es Singleton
        MenuPrincipal();

        ~MenuPrincipal();

        // La única instancia
        static MenuPrincipal * menuPrincipal;

        // Aquí se almacenan las cosas que se pueden
        // hacer desde el menú principal, de las cuales
        // tienes que elegir una para empezar a jugar
        std::vector<SelectorMenuPrincipal> selectores;

        // El índice de la selección actual
        unsigned int seleccionActual;

        // El cartel con el título del juego
        std::shared_ptr<Animacion> cartelTitulo;

        // El efecto que hay a la izquierda que es como dientes de sierra oscuros
        sf::Sprite dientesSierraArriba;
        sf::Sprite dientesSierraAbajo;

        // Shader para hacer que los selectores del menú principal brillen
        std::shared_ptr<sf::Shader> shaderDestello;

        // Del 0 al 1, indica el brillo del selector actual, donde 0 significa que está
        // normal y 1 significa que está completamente blanco
        float brilloSelector;

        // Si está a true, significa que se ha pulsado un selector y es necesario salir
        // lo antes posible del menú principal
        bool selectorPulsado;

        // Rectángulo que tapa el menú principal cuando se selecciona una opción
        sf::RectangleShape rectanguloNegro;

        // Se devuelven los botones y carteles y demás a su posición original
        void resetear();

        // Se avisa a cada selector de su nueva posición relativa cuando se
        // cambia la selección
        void cambiarPosicionRelativa();

    public:

        // Comienza el funcionamiento del menú principal, que toma el control
        // de la ventana hasta que no se selecciona otra cosa
        TipoSelectorMenuPrincipal comenzar();

        // NUNCA SE COPIA UN SINGLETON
        MenuPrincipal(MenuPrincipal &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const MenuPrincipal &) = delete;

        // Devuelve la única instancia
        static MenuPrincipal * unicaInstancia();
};