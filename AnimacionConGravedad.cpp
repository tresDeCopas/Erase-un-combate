#include "AnimacionConGravedad.hpp"
#include "Constantes.hpp"

AnimacionConGravedad::AnimacionConGravedad(sf::Texture &textura, Hitbox hitbox, sf::Vector2f posicion, sf::Vector2f velocidad, double velocidadGiro) : hitbox(hitbox)
{
    sprite.setTexture(textura);

    // El rectángulo será el de la izquierda en un principio
    sf::IntRect rectangulo = sprite.getTextureRect();
    rectangulo.width /= 2;
    sprite.setTextureRect(rectangulo);

    this->velocidad = velocidad;
    this->velocidadGiro = velocidadGiro;

    sprite.setOrigin(rectangulo.width / 2, rectangulo.height / 2);

    sprite.setPosition(posicion);

    resetear();
}

AnimacionConGravedad::AnimacionConGravedad(sf::Texture &textura, Hitbox hitbox, sf::Vector2f posicion, sf::Vector2f velocidad, double velocidadGiro, sf::Sound sonido) : hitbox(hitbox)
{
    sprite.setTexture(textura);

    // El rectángulo será el de la izquierda en un principio
    sf::IntRect rectangulo = sprite.getTextureRect();
    rectangulo.width /= 2;
    sprite.setTextureRect(rectangulo);

    this->velocidad = velocidad;
    this->velocidadGiro = velocidadGiro;

    sprite.setOrigin(rectangulo.width / 2, rectangulo.height / 2);

    sprite.setPosition(posicion);

    this->sonido = sonido;

    resetear();
}

void AnimacionConGravedad::actualizar(std::list<std::shared_ptr<Animacion>> &nuevasAnimaciones, sf::Vector2f &movimiento)
{
    sprite.move(velocidad);
    sprite.rotate(velocidadGiro);

    velocidad.y += GRAVEDAD;

    if (sprite.getPosition().y+std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0 > VENTANA_ALTURA)
    {
        if(!haChocado) {
            haChocado = true;
            sf::IntRect rectangulo = sprite.getTextureRect();
            rectangulo.left = rectangulo.width;
            sprite.setTextureRect(rectangulo);
        }

        velocidad.y /= -2;
        if(velocidad.y > -1) velocidad.y = 0;

        velocidadGiro = velocidad.x*2;

        velocidad.x /= 1.2;
        
        sprite.setPosition(sprite.getPosition().x,VENTANA_ALTURA-std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0);

    } else if (sprite.getPosition().x+std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0 > VENTANA_ANCHURA)
    {
        if(!haChocado) {
            haChocado = true;
            sf::IntRect rectangulo = sprite.getTextureRect();
            rectangulo.left = rectangulo.width;
            sprite.setTextureRect(rectangulo);
        }

        if(velocidad.x > 0) velocidad.x/=-1.3;
        
        sprite.setPosition(VENTANA_ANCHURA-std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0,sprite.getPosition().y);

    } else if (sprite.getPosition().x-std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0 < 0)
    {
        if(!haChocado) {
            haChocado = true;
            sf::IntRect rectangulo = sprite.getTextureRect();
            rectangulo.left = rectangulo.width;
            sprite.setTextureRect(rectangulo);
        }

        if(velocidad.x < 0) velocidad.x/=-1.3;
        
        sprite.setPosition(std::min(sprite.getTextureRect().height,sprite.getTextureRect().width)/2.0,sprite.getPosition().y);
    }

    if(velocidad.y == 0){
        contadorParpadeo++;
    }

    if(contadorParpadeo >= MAX_CONTADOR_PARPADEO){
        sprite.setColor(sf::Color::Transparent);
    } else {
        sf::Uint8 transparencia(((MAX_CONTADOR_PARPADEO-contadorParpadeo)/(double)MAX_CONTADOR_PARPADEO)*255);
        sprite.setColor(sf::Color(255,255,255,transparencia));
    }
}

void AnimacionConGravedad::resetear()
{
    haChocado = false;
    contadorParpadeo = 0;
}

std::list<Hitbox> AnimacionConGravedad::getHitboxes(){
    if(!haChocado){
        std::list<Hitbox> lista = std::list<Hitbox>();
        lista.push_back(hitbox);
        return lista;
    }
    else return std::list<Hitbox>();
}

bool AnimacionConGravedad::haTerminado(){
    return contadorParpadeo > MAX_CONTADOR_PARPADEO;
}

void AnimacionConGravedad::voltear(){
    // Al escalar el eje X por -1 se le da la vuelta muy guay todo pero no es suficiente
    sprite.scale(-1,1);

    // También hay que voltear la hitbox
    int puntoCentral = sprite.getTextureRect().width/2;

    int derecha = hitbox.getRectangulo().left+hitbox.getRectangulo().width;

    int nuevaIzquierda = derecha - (derecha-puntoCentral)*2;

    Hitbox nuevaHitbox(sf::IntRect(nuevaIzquierda,hitbox.getRectangulo().top,hitbox.getRectangulo().width,hitbox.getRectangulo().height),hitbox.getFuerzaAtaque(),hitbox.esAtaqueBajo());

    hitbox = nuevaHitbox;

    // También hay que voltear la velocidad
    velocidad.x = -velocidad.x;
}

void AnimacionConGravedad::setVelocidad(sf::Vector2f velocidad){
    this->velocidad = velocidad;
}

void AnimacionConGravedad::setVelocidadGiro(const double &velocidadGiro){
    this->velocidadGiro = velocidadGiro;
}

std::shared_ptr<Animacion> AnimacionConGravedad::clonar(){
    return std::shared_ptr<Animacion>(new AnimacionConGravedad(*this));
}

void AnimacionConGravedad::chocar(Hitbox hitbox){
    hitbox.getRectangulo();
}

void AnimacionConGravedad::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    if(contadorParpadeo%(DURACION_PARPADEO*2) < DURACION_PARPADEO) target.draw(sprite,states);
}