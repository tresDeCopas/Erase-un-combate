#include "SelectorMenuPrincipal.hpp"
#include "Constantes.hpp"
#include "Utilidades.hpp"
#include "ContenedorDeEfectos.hpp"
#include <cmath>
#include <algorithm>

SelectorMenuPrincipal::SelectorMenuPrincipal(sf::Texture& texturaSelector, TipoSelectorMenuPrincipal tipoSelector) :
spriteSelector(texturaSelector), tipoSelector(tipoSelector), posicionRelativa(static_cast<int>(tipoSelector))
{
    // Se pone el origen en el centro porque mola más
    spriteSelector.setOrigin(sf::Vector2f(spriteSelector.getTextureRect().size)/2.f);
    resetear();
}

void SelectorMenuPrincipal::resetear()
{
    // Se establece la posición relativa en base al tipo de selector (se asume que
    // al resetear los selectores, en el menú principal se pasará a seleccionar
    // el selector 0)
    posicionRelativa = static_cast<int>(tipoSelector);

    // Se pone el color correcto para el selector
    sf::Color colorSelector = COLOR_SELECTOR_PERSONAJE_POSICION_RELATIVA_0;
    colorSelector.a = std::clamp(colorSelector.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR_MENU_PRINCIPAL,0,255);
    spriteSelector.setColor(colorSelector);

    // Se pone la escala correcta para el selector
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR_MENU_PRINCIPAL;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;
    spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});

    // Se pone el selector en la posición correcta
    spriteSelector.setPosition({POSICION_X_SELECTOR_MENU_PRINCIPAL, POSICION_INICIAL_Y_SELECTOR_MENU_PRINCIPAL + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR_MENU_PRINCIPAL*std::sqrt(escalaDeseadaSprite)});
}

void SelectorMenuPrincipal::actualizar()
{
    // Primero se calcula la posición y el color deseados y luego se
    // acerca un poquito la posición y el color actuales a lo deseado
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_MENU_PRINCIPAL_POSICION_RELATIVA_0;

    // La escala depende de la posición relativa del selector. Si se está
    // seleccionando, el tamaño del selector será el normal. Si no, será más
    // pequeño cuanto más lejos esté de la selección actual
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR_MENU_PRINCIPAL;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    // El color se irá trasparentando conforme el selector se aleja de la selección actual
    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR_MENU_PRINCIPAL,0,255);

    // La posición en el eje Y depende de la posición relativa
    posicionDeseadaSprite.x = POSICION_X_SELECTOR_MENU_PRINCIPAL;
    posicionDeseadaSprite.y = POSICION_INICIAL_Y_SELECTOR_MENU_PRINCIPAL + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR_MENU_PRINCIPAL*std::sqrt(escalaDeseadaSprite);

    // Se acerca la posición, el color y la escala del selector a sus valores deseados
    spriteSelector.setPosition(util::aproximarVector2f(spriteSelector.getPosition(),posicionDeseadaSprite,0.8f));
    spriteSelector.setColor(util::aproximarColor(spriteSelector.getColor(),colorDeseadoSprite,0.8f));
    spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{escalaDeseadaSprite,escalaDeseadaSprite},0.8f));
}

void SelectorMenuPrincipal::ajustarPosicion()
{
    // Primero se calcula la posición y el color deseados
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_MENU_PRINCIPAL_POSICION_RELATIVA_0;

    // La escala depende de la posición relativa del selector. Si se está
    // seleccionando, el tamaño del selector será el normal. Si no, será más
    // pequeño cuanto más lejos esté de la selección actual
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR_MENU_PRINCIPAL;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    // El color se irá trasparentando conforme el selector se aleja de la selección actual
    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR_MENU_PRINCIPAL,0,255);

    // La posición en el eje Y depende de la posición relativa
    posicionDeseadaSprite.x = POSICION_X_SELECTOR_MENU_PRINCIPAL;
    posicionDeseadaSprite.y = POSICION_INICIAL_Y_SELECTOR_MENU_PRINCIPAL + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR_MENU_PRINCIPAL*std::sqrt(escalaDeseadaSprite);

    // Se acerca la posición, el color y la escala del selector a sus valores deseados
    spriteSelector.setPosition(posicionDeseadaSprite);
    spriteSelector.setColor(colorDeseadoSprite);
    spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});
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

void SelectorMenuPrincipal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(spriteSelector,states);
}