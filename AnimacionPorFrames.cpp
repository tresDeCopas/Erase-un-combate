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

AnimacionPorFrames::AnimacionPorFrames(int posicionX, int posicionY, int origenX, int origenY, int numRectangulos, sf::Texture &textura, TipoBucle tipoBucle, int numRepeticionesTotal, std::map<int,std::list<Hitbox>> hitboxes, std::map<int,int> rectanguloCorrespondiente, sf::Sound sonido, std::set<int> framesConSonido, bool repetirSonido) {

    sprite.setTexture(textura);
    sprite.setTextureRect(sf::IntRect(0, 0, textura.getSize().x/numRectangulos, textura.getSize().y));
    sprite.setOrigin(origenX,origenY);
    sprite.setPosition(posicionX,posicionY);

    this->tipoBucle = tipoBucle;
    this->numRepeticionesTotal = numRepeticionesTotal;
    this->hitboxes = hitboxes;
    this->rectanguloCorrespondiente = rectanguloCorrespondiente;
    this->sonido = sonido;
    this->framesConSonido = framesConSonido;
    this->repetirSonido = repetirSonido;

    sonidoYaReproducido = false;

    resetear();
}

void AnimacionPorFrames::actualizar() {

    if(!sonidoYaReproducido && framesConSonido.count(frameActual)) sonido.play();

    if(tipoBucle == TipoBucle::NORMAL){
        frameActual++;
        if(frameActual >= rectanguloCorrespondiente.size()) {
            frameActual = 0;
            if(!repetirSonido) sonidoYaReproducido = true;
        }
    } else if (tipoBucle == TipoBucle::AL_REVES){
        if(frameActual == 0) {
            frameActual = rectanguloCorrespondiente.size()-1;
            if(!repetirSonido) sonidoYaReproducido = true;
        }
        else frameActual--;
    } else if (tipoBucle == TipoBucle::SIN_BUCLE){
        if(frameActual < rectanguloCorrespondiente.size()-1)
            frameActual++;
    }

    sprite.setTextureRect(sf::IntRect(rectanguloCorrespondiente[frameActual]*sprite.getTextureRect().width,0,sprite.getTextureRect().width,sprite.getTextureRect().height));
}

void AnimacionPorFrames::voltear(){
    // Al escalar el eje X por -1 se le da la vuelta muy guay todo pero no es suficiente
    sprite.scale(-1,1);

    // También hay que voltear las hitboxes
    for(auto const &[entero, listaHitboxes] : hitboxes){
        std::list<Hitbox> nuevaLista;

        for(Hitbox hitbox : listaHitboxes){

            // Esto se explicaría mejor con un dibujito pero bueno
            int puntoCentral = sprite.getTextureRect().width/2;

            int derecha = hitbox.getRectangulo().left+hitbox.getRectangulo().width;

            int nuevaIzquierda = derecha - (derecha-puntoCentral)*2;

            Hitbox nuevaHitbox(sf::IntRect(nuevaIzquierda,hitbox.getRectangulo().top,hitbox.getRectangulo().width,hitbox.getRectangulo().height),hitbox.getFuerzaAtaque(),hitbox.esAtaqueBajo());

            nuevaLista.push_back(nuevaHitbox);
        }

        hitboxes[entero] = nuevaLista;
    }
}

int AnimacionPorFrames::getNumeroRectangulo() {
    return rectanguloCorrespondiente[frameActual];
}

void AnimacionPorFrames::setTipoBucle(TipoBucle tipoBucle){
    this->tipoBucle = tipoBucle;
}

bool AnimacionPorFrames::haTerminado(){
    return tipoBucle == TipoBucle::SIN_BUCLE && frameActual == rectanguloCorrespondiente.size()-1;
}

void AnimacionPorFrames::resetear(){
    frameActual = 0;
    numRepeticionesActual = 0;
    pingPongHaciaDelante = true;
    sonidoYaReproducido = false;
}

Animacion * AnimacionPorFrames::clonar(){
    return new AnimacionPorFrames(*this);
}

void AnimacionPorFrames::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(sprite,states);

    if(DEBUG){
        for(Hitbox h : hitboxes.at(rectanguloCorrespondiente.at(frameActual))){
            sf::RectangleShape rectanguloHitbox(sf::Vector2f(h.getRectangulo().width,h.getRectangulo().height));
            rectanguloHitbox.setPosition(sprite.getPosition().x-PERSONAJE_PLANTILLA_ORIGEN.x+h.getRectangulo().left,sprite.getPosition().y-PERSONAJE_PLANTILLA_ORIGEN.y+h.getRectangulo().top);
            rectanguloHitbox.setFillColor(sf::Color::Transparent);
            rectanguloHitbox.setOutlineThickness(1);
            rectanguloHitbox.setOutlineColor(h.getFuerzaAtaque() > 0 ? HITBOX_ATAQUE_COLOR : HITBOX_NO_ATAQUE_COLOR);
            target.draw(rectanguloHitbox,states);
        }
    }
}
