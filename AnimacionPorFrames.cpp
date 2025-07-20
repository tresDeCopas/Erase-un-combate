#include "AnimacionPorFrames.hpp"
#include "Constantes.hpp"
#include <SFML/Graphics.hpp>

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
    // TODO
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

void AnimacionPorFrames::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);

    if(HITBOX_MOSTRAR){
        for(Hitbox h : hitboxes.at(rectanguloCorrespondiente.at(frameActual))){
            sf::RectangleShape rectanguloHitbox;
            rectanguloHitbox.setFillColor(sf::Color::Transparent);
            rectanguloHitbox.setOutlineColor(h.getFuerzaAtaque() > 0 ? HITBOX_ATAQUE_COLOR : HITBOX_NO_ATAQUE_COLOR);
            target.draw(rectanguloHitbox,states);
        }
    }
}
