#pragma once

#include <SFML/Graphics.hpp>

/*
    Esta clase define un temporizador que hace que el combate
    termine automáticamente cuando pasa un tiempo
*/
class Temporizador : public sf::Drawable
{
    private:
        // Sprite de fondo del temporizador
        sf::Sprite spriteFondo;

        // Indica cuántos fotogramas tienen que pasar para
        // que baje el contador en uno
        const unsigned int fotogramasPorTick;

        // Indica cuántos ticks tiene el contador (cuántas veces
        // tiene que bajar para que termine el combate)
        const unsigned int ticksContador;

        // Contador de cuántos fotogramas hay que avanzar para
        // bajarle un numerito al contador
        unsigned int fotogramasRestantes;

        // Contador de cuánto queda para que termine el combate
        unsigned int contadorActual;

        // Texto que contiene los numeritos que indican
        // cuánto tiempo queda
        sf::Text textoContador;

    public:
        // Crea un temporizador
        Temporizador(const sf::Texture& texturaSprite, const sf::Font& fuenteContador,
                     unsigned int fotogramasPorTick, unsigned int ticksContador);
        
        // Actualiza el temporizador al pasar un fotograma
        void actualizar();

        // Resetea el contador para comenzar un nuevo combate
        void resetear();

        // Indica si se ha acabado el tiempo
        bool haTerminado();

        // Dibuja el temporizador
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
    
    private:
        // Actualiza el numerito del temporizador para que se muestre por
        // pantalla correctamente
        void actualizarNumeroContador();
};