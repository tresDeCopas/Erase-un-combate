#include "Hitbox.hpp"

Hitbox::Hitbox(sf::IntRect rectangulo, int fuerzaAtaque){
    this->rectangulo = rectangulo;
    this->fuerzaAtaque = fuerzaAtaque;
}

sf::IntRect Hitbox::getRectangulo(){
    return rectangulo;
}

int Hitbox::getFuerzaAtaque(){
    return fuerzaAtaque;
}
