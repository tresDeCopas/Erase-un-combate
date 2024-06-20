#include "Animacion.hpp"

void Animacion::voltear(){
    // Al escalar el eje X por -1 se le da la vuelta muy guay todo
    sprite.scale(-1,1);
}

void Animacion::setPosicion(float x, float y){
    sprite.setPosition(x,y);
}

void Animacion::setPosicion(sf::Vector2f posicion){
    setPosicion(posicion.x,posicion.y);
}

sf::Vector2f Animacion::getPosicion(){
    return sprite.getPosition();
}

void Animacion::mover(float x, float y){
    sprite.move(x,y);
}

void Animacion::mover(sf::Vector2f diferencia){
    mover(diferencia.x,diferencia.y);
}

void Animacion::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);
}
