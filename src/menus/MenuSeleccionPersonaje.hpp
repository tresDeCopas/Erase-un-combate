#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include "Enums.hpp"
#include <SFML/Graphics.hpp>

/*
    Esta es una clase auxiliar para guardar los selectores para
    cada uno de los personajes que se pueden elegir
*/
class SelectorPersonaje {
    private:
        // El sprite asociado al selector
        sf::Sprite spriteSelector;

        // Un borde cuadrado que rodea al sprite del selector

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
        SelectorPersonaje(const sf::Texture& texturaSelector, const std::string& nombrePersonaje, Jugador jugador);

        // Se reestablece el selector a su estado inicial (excepto la posición relativa,
        // eso se lo tienes que poner tú antes de resetear)
        void resetear();

        // Se elige el selector, así que sale un brillito y el personaje es elegido
        void seleccionar();

        // Se actualiza la posición y la transparencia del selector y su fondo
        void actualizar();

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

/*
    Esta clase representa el menú principal en el que tú y tu rival elegís
    cada uno un personaje (o, si estás jugando contra la máquina, solo tú eliges
    un personaje)
*/
class MenuSeleccionPersonaje {
    private:
        // El constructor es privado porque la clase es Singleton
        MenuSeleccionPersonaje();

        ~MenuSeleccionPersonaje();

        // La única instancia
        static MenuSeleccionPersonaje * menuSeleccionPersonaje;

        // Un vector con todos los nombres de personajes que hay disponibles
        std::vector<std::string> nombresPersonajes;

        // El índice del vector nombresPersonajes donde está el nombre del
        // personaje que está seleccionando cada jugador
        unsigned int indiceJugador1;
        unsigned int indiceJugador2;

        // Indica, para cada jugador, si ya ha elegido a su personaje o aún no
        bool personajeElegidoJugador1;
        bool personajeElegidoJugador2;

        // El sprite del marco principal del menú de selección de personajes
        sf::Sprite spriteMarco;

        // Rectángulo que tapa el menú al entrar y al salir, lo típico
        sf::RectangleShape rectanguloNegro;

        // Vector con todos los selectores de personaje de cada jugador
        std::vector<SelectorPersonaje> selectoresPersonajeJugador1;
        std::vector<SelectorPersonaje> selectoresPersonajeJugador2;

        // Se devuelve todo a su posición inicial
        void resetear();

    public:

        // Comienza el funcionamiento del menú, que toma el control
        // de la ventana. Devuelve un mapa de nombres de personaje, donde
        // por cada uno de los dos jugadores se indica el nombre del personaje
        // que ha elegido. Si el mapa está vacío, significa que se ha cancelado
        // la selección de personaje
        std::unordered_map<Jugador,std::string> comenzarEleccionDoble();

        // Es como comenzarEleccionDoble pero solo el jugador 1 elige a su
        // personaje. Se usa, por ejemplo, en el modo escalera
        std::unordered_map<Jugador,std::string> comenzarEleccionSimple();

        // NUNCA SE COPIA UN SINGLETON
        MenuSeleccionPersonaje(MenuSeleccionPersonaje &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const MenuSeleccionPersonaje &) = delete;

        // Devuelve la única instancia
        static MenuSeleccionPersonaje * unicaInstancia();
};