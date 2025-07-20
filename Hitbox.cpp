#include "Hitbox.hpp"

Hitbox::Hitbox(sf::IntRect rectangulo, int fuerzaAtaque, bool bajo){
    this->rectangulo = rectangulo;
    this->fuerzaAtaque = fuerzaAtaque;
    this->bajo = bajo;
}

sf::IntRect Hitbox::getRectangulo(){
    return rectangulo;
}

int Hitbox::getFuerzaAtaque(){
    return fuerzaAtaque;
}

bool Hitbox::esAtaqueBajo(){
    return bajo;
}
