#pragma once

#include "Animacion.hpp"
#include "SFML/Graphics.hpp"
#include <string>

/*
    Esta clase define animaciones que son un símbolo que sale de un sitio con
    una velocidad grande pero va haciéndose más lenta y pequeña conforme
    vaya acercándose a su destino
*/
class AnimacionParticulaLineal : public Animacion
{
    private:
        // Indica desde dónde sale la partícula
        sf::Vector2f posicionInicial;

        // Indica hacia dónde debe ir la partícula
        sf::Vector2f posicionFinal;

    public:

        // Este constructor sirve cuando no tienes ni idea de las posiciones del objeto
        AnimacionParticulaLineal(sf::Texture &textura);

        // Este constructor sirve cuando sabes exactamente la posición hacia la que
        // quieres que se dirija la partícula
        AnimacionParticulaLineal(sf::Texture &textura, sf::Vector2f posicionInicial, sf::Vector2f posicionFinal);

        // Este constructor sirve cuando solo sabes la posición inicial, el ángulo
        // y la longitud del movimiento
        AnimacionParticulaLineal(sf::Texture &textura, sf::Vector2f posicionInicial, float angulo, float longitud);

        // Establece la posición inicial
        void setPosicionInicial(sf::Vector2f posicionInicial);

        // Establece la posición final
        void setPosicionFinal(sf::Vector2f posicionFinal);

        // Calcula la posición final en base a la posición inicial, el ángulo del movimiento
        // y su longitud
        void setPosicionFinal(float angulo, float longitud);

        // Actualiza la animación, moviendo el círculo a su destino y haciendo que se haga más pequeño
        void actualizar(std::list<std::shared_ptr<Animacion>> &nuevasAnimaciones);

        // Resetea la animación al estado inicial
        void resetear();

        // Le da la vuelta a la animación
        void voltear();

        // Devuelve un vector con las hitboxes
        std::vector<Hitbox> getHitboxes();

        // Determina si una animación ha terminado
        bool haTerminado();

        // Devuelve un clon de la animación
        std::shared_ptr<Animacion> clonar();

        // Dibuja la animación
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};