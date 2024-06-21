#include "AnimacionPorFrames.hpp"
#include "Constantes.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

AnimacionPorFrames::AnimacionPorFrames(int posicionX, int posicionY, int origenX, int origenY, int numRectangulos, sf::Texture &textura, TipoBucle tipoBucle, int numRepeticionesTotal, std::map<int,std::list<Hitbox>> hitboxes, std::map<int,int> rectanguloCorrespondiente) {

    sprite.setTexture(textura);
    sprite.setTextureRect(sf::IntRect(0, 0, textura.getSize().x/numRectangulos, textura.getSize().y));
    sprite.setOrigin(origenX,origenY);
    sprite.setPosition(posicionX,posicionY);

    this->tipoBucle = tipoBucle;
    this->numRepeticionesTotal = numRepeticionesTotal;
    this->hitboxes = hitboxes;
    this->rectanguloCorrespondiente = rectanguloCorrespondiente;

    resetear();
}

void AnimacionPorFrames::actualizar() {
    if(tipoBucle == TipoBucle::NORMAL){
        frameActual++;
        if(frameActual >= rectanguloCorrespondiente.size()) frameActual = 0;
    } else if (tipoBucle == TipoBucle::AL_REVES){
        if(frameActual == 0) frameActual = rectanguloCorrespondiente.size()-1;
        else frameActual--;
    }

    sprite.setTextureRect(sf::IntRect(rectanguloCorrespondiente[frameActual]*sprite.getTextureRect().width,0,sprite.getTextureRect().width,sprite.getTextureRect().height));
}

int AnimacionPorFrames::getNumeroRectangulo() {
    return rectanguloCorrespondiente[frameActual];
}

void AnimacionPorFrames::setTipoBucle(TipoBucle tipoBucle){
    this->tipoBucle = tipoBucle;
}

void AnimacionPorFrames::resetear(){
    frameActual = 0;
    numRepeticionesActual = 0;
    pingPongHaciaDelante = true;
}

Animacion * AnimacionPorFrames::clonar(){
    return new AnimacionPorFrames(*this);
}

void AnimacionPorFrames::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);

    if(DEBUG){
        for(Hitbox h : hitboxes.at(rectanguloCorrespondiente.at(frameActual))){
            sf::RectangleShape rectanguloHitbox(sf::Vector2f(h.getRectangulo().width,h.getRectangulo().height));
            rectanguloHitbox.setPosition(h.getRectangulo().left,h.getRectangulo().top);
            rectanguloHitbox.setFillColor(sf::Color::Transparent);
            rectanguloHitbox.setOutlineThickness(10);
            rectanguloHitbox.setOutlineColor(h.getFuerzaAtaque() > 0 ? HITBOX_ATAQUE_COLOR : HITBOX_NO_ATAQUE_COLOR);
            target.draw(rectanguloHitbox,states);
        }
    }
}
