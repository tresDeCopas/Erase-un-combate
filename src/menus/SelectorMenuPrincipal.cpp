#include "SelectorMenuPrincipal.hpp"
#include "Constantes.hpp"
#include "Utilidades.hpp"
#include "ContenedorDeEfectos.hpp"
#include <algorithm>

SelectorMenuPrincipal::SelectorMenuPrincipal(sf::Texture& texturaSelector, sf::Texture& texturaFondo, TipoSelectorMenuPrincipal tipoSelector) :
spriteSelector(texturaSelector), spriteFondo(texturaFondo), tipoSelector(tipoSelector), posicionRelativa(static_cast<int>(tipoSelector))
{
    // Se pone el origen en el centro a la izquierda del todo porque mola más
    spriteSelector.setOrigin(sf::Vector2f(spriteSelector.getTextureRect().size)/2.f);
    resetear();
}

void SelectorMenuPrincipal::resetear()
{
    // Se establece la posición relativa en base al tipo de selector (se asume que
    // al resetear los selectores, en el menú principal se pasará a seleccionar
    // el selector 0)
    posicionRelativa = static_cast<int>(tipoSelector);
    
    // Se pone el selector y el fondo en las posiciones correctas
    spriteSelector.setPosition({POSICION_X_SELECTOR, POSICION_INICIAL_Y_SELECTOR + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR});
    spriteFondo.setPosition({0.f, posicionRelativa*DIFERENCIA_POSICION_Y_FONDO_SELECTOR});

    // Se pone el color correcto para el selector y su fondo
    sf::Color colorSelector = COLOR_SELECTOR_POSICION_RELATIVA_0;
    colorSelector.a = std::clamp(colorSelector.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);
    spriteSelector.setColor(colorSelector);

    // Se pone la escala correcta para el sprite
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;
    spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});

    if(posicionRelativa == 0)
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_SELECCIONADO);
    else
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_SIN_SELECCIONAR);
}

void SelectorMenuPrincipal::actualizar()
{
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_POSICION_RELATIVA_0;
    sf::Vector2f posicionDeseadaFondo;
    sf::Color colorDeseadoFondo;

    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    posicionDeseadaSprite.x = POSICION_X_SELECTOR;

    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);

    if(posicionRelativa == 0)
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_SELECCIONADO;
    else
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_SIN_SELECCIONAR;

    posicionDeseadaSprite.y = POSICION_INICIAL_Y_SELECTOR + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR*escalaDeseadaSprite;
    posicionDeseadaFondo.x = 0;
    posicionDeseadaFondo.y = posicionRelativa * DIFERENCIA_POSICION_Y_FONDO_SELECTOR;

    spriteSelector.setPosition(util::aproximarVector2f(spriteSelector.getPosition(),posicionDeseadaSprite,0.8f));
    spriteSelector.setColor(util::aproximarColor(spriteSelector.getColor(),colorDeseadoSprite,0.8f));
    spriteFondo.setPosition(util::aproximarVector2f(spriteFondo.getPosition(),posicionDeseadaFondo,0.8f));
    spriteFondo.setColor(util::aproximarColor(spriteFondo.getColor(),colorDeseadoFondo,0.8f));
    spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{escalaDeseadaSprite,escalaDeseadaSprite},0.8f));
}

void SelectorMenuPrincipal::seleccionar(std::list<std::shared_ptr<Animacion>>& nuevasAnimaciones)
{
    std::shared_ptr<Animacion> anim;

    switch(tipoSelector){
        case TipoSelectorMenuPrincipal::MODO_HISTORIA:
            anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-modo-historia-destello");
            break;
        case TipoSelectorMenuPrincipal::BATALLA_VS:
            anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-batalla-vs-destello");
            break;
        case TipoSelectorMenuPrincipal::OPCIONES:
            anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-opciones-destello");
            break;
    }
    
    sf::Vector2f posicionEfecto = spriteSelector.getPosition();

    anim->setPosicion(posicionEfecto);
    nuevasAnimaciones.push_back(anim);

    spriteSelector.setScale(spriteSelector.getScale()/2.f);
}