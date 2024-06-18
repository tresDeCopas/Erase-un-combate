#ifndef __HITBOX_HPP__
#define __HITBOX_HPP__

#include <SFML/Graphics.hpp>

/*
    Clase que implementa una caja de colisiones. Esta caja es un rectángulo
    que indica el área que abarca un ataque o un personaje, TOMANDO SIEMPRE COMO
    REFERENCIA LA ESQUINA SUPERIOR IZQUIERDA DEL SPRITE, SEA CUAL SEA
*/
class Hitbox {
    private:

        // Rectángulo de la hitbox
        sf::IntRect rectangulo;

        // Daño que quita el ataque de la hitbox (si es un ataque)
        int fuerzaAtaque;

    public:

        // Constructor
        Hitbox(sf::IntRect rectangulo, int fuerzaAtaque);

        // Devuelve el rectángulo
        sf::IntRect getRectangulo();

        // Devuelve la fuerza de ataque
        int getFuerzaAtaque();

};

#endif // __HITBOX_HPP__
