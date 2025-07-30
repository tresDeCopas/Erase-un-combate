#include "AnimacionDesvaneciente.hpp"
#include "Utilidades.hpp"
#include "ReproductorDeSonidos.hpp"

AnimacionDesvaneciente::AnimacionDesvaneciente(sf::Texture &textura, float escalado, std::string rutaSonido) :
    Animacion(textura), escalado(escalado), sonidoReproducido(false), rutaSonido(rutaSonido)
{
    sprite.setOrigin(sf::Vector2f(sprite.getTextureRect().size/2));
}

void AnimacionDesvaneciente::actualizar(std::list<std::shared_ptr<Animacion>> &nuevasAnimaciones)
{
    if(!sonidoReproducido && rutaSonido != "")
    {
        ReproductorDeSonidos::unicaInstancia()->reproducir(rutaSonido);
        sonidoReproducido = true;
    }

    sprite.setScale({util::aproximarFloat(sprite.getScale().x,escalado,0.95f),util::aproximarFloat(sprite.getScale().y,escalado,0.95f)});
    sf::Color colorDestino = sprite.getColor();
    colorDestino.a = 0;
    sprite.setColor(util::aproximarColor(sprite.getColor(),colorDestino,0.95f));
}

void AnimacionDesvaneciente::resetear()
{
    sprite.setScale(sf::Vector2f(1.f,1.f));
    sprite.setColor(sf::Color::White);
}

void AnimacionDesvaneciente::voltear()
{
    sprite.setScale(sf::Vector2f(sprite.getScale().x*-1,sprite.getScale().y));
}

std::vector<Hitbox> AnimacionDesvaneciente::getHitboxes()
{
    return std::vector<Hitbox>();
}

bool AnimacionDesvaneciente::haTerminado()
{
    return sprite.getColor().a == 0;
}

std::shared_ptr<Animacion> AnimacionDesvaneciente::clonar()
{
    return std::make_shared<AnimacionDesvaneciente>(*this);
}