#include "FondoPersonaje.hpp"
#include "Constantes.hpp"
#include "Utilidades.hpp"
#include "ContenedorDeRecursos.hpp"

#include <algorithm>

FondoPersonaje::FondoPersonaje(const sf::Texture& texturaFondo, const std::string& nombrePersonaje, Jugador jugador, int posicionRelativa) :
spriteFondo(texturaFondo), nombrePersonaje(nombrePersonaje), posicionRelativa(posicionRelativa), jugador(jugador)
{
    if(jugador == Jugador::JUGADOR2)
    {
        // Los fondos del jugador 2 están dados la vuelta
        spriteFondo.setScale({-1.f,0.f});
    }

    resetear(posicionRelativa);
}

void FondoPersonaje::resetear(int posicionRelativa)
{
    this->posicionRelativa = posicionRelativa;

    // Se pone el selector y el fondo en las posiciones correctas
    float posicionX = jugador == Jugador::JUGADOR1 ?
                      POSICION_X_FONDO_PERSONAJE_J1 :
                      POSICION_X_FONDO_PERSONAJE_J2;
    
    spriteFondo.setPosition({posicionX + posicionRelativa*DIFERENCIA_POSICION_X_FONDO_PERSONAJE, POSICION_Y_SELECTOR_PERSONAJE});

    // Se pone el color correcto para el fondo
    sf::Color colorSelector = COLOR_SELECTOR_PERSONAJE_POSICION_RELATIVA_0;
    colorSelector.a = std::clamp(colorSelector.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR_PERSONAJE,0,255);
    spriteSelector.setColor(colorSelector);

    if(jugador == Jugador::JUGADOR1)
        spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});
    else
        spriteSelector.setScale({-escalaDeseadaSprite,escalaDeseadaSprite});
    
    bordeCuadrado.setPosition(spriteSelector.getPosition());
    bordeCuadrado.setScale(spriteSelector.getScale());
    bordeCuadrado.setOutlineColor(spriteSelector.getColor());
}

void SelectorPersonaje::actualizar()
{
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_PERSONAJE_POSICION_RELATIVA_0;
    sf::Vector2f posicionDeseadaFondo;
    sf::Color colorDeseadoFondo;

    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR_PERSONAJE;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    posicionDeseadaSprite.x = jugador == Jugador::JUGADOR1 ?
                              POSICION_X_SELECTOR_PERSONAJE_J1 :
                              POSICION_X_SELECTOR_PERSONAJE_J2;
    posicionDeseadaSprite.x += posicionRelativa*DIFERENCIA_POSICION_X_SELECTOR_PERSONAJE*escalaDeseadaSprite;
    posicionDeseadaSprite.y = POSICION_Y_SELECTOR_PERSONAJE;

    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR_PERSONAJE,0,255);

    spriteSelector.setPosition(util::aproximarVector2f(spriteSelector.getPosition(),posicionDeseadaSprite,0.8f));
    spriteSelector.setColor(util::aproximarColor(spriteSelector.getColor(),colorDeseadoSprite,0.8f));

    if(jugador == Jugador::JUGADOR1)
        spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{escalaDeseadaSprite,escalaDeseadaSprite},0.8f));
    else
        spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{-escalaDeseadaSprite,escalaDeseadaSprite},0.8f));

    bordeCuadrado.setPosition(spriteSelector.getPosition());
    bordeCuadrado.setScale(spriteSelector.getScale());
    bordeCuadrado.setOutlineColor(spriteSelector.getColor());
}

void SelectorPersonaje::seleccionar()
{
    spriteSelector.setScale(spriteSelector.getScale()/2.f);
}

void SelectorPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(spriteSelector,states);
    target.draw(bordeCuadrado,states);

    if(posicionRelativa == 0)
        target.draw(spriteNombrePersonaje,states);
}