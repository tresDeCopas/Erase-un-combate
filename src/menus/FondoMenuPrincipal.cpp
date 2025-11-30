#include "FondoMenuPrincipal.hpp"
#include "Constantes.hpp"
#include "Utilidades.hpp"

FondoMenuPrincipal::FondoMenuPrincipal(sf::Texture& texturaFondo, TipoSelectorMenuPrincipal tipoSelector) :
spriteFondo(texturaFondo), tipoSelector(tipoSelector), posicionRelativa(static_cast<int>(tipoSelector))
{
    resetear();
}

void FondoMenuPrincipal::resetear()
{

    // Se establece la posición relativa en base al tipo de selector (se asume que
    // al resetear los selectores, en el menú principal se pasará a seleccionar
    // el selector 0)
    posicionRelativa = static_cast<int>(tipoSelector);

    // Se coloca el sprite en la posición correcta
    spriteFondo.setPosition({0.f, posicionRelativa*DIFERENCIA_POSICION_Y_FONDO_SELECTOR_MENU_PRINCIPAL});

    // Según si la posición relativa es 0 o no, el fondo tendrá un color distinto
    if(posicionRelativa == 0)
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_MENU_PRINCIPAL_SELECCIONADO);
    else
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_MENU_PRINCIPAL_SIN_SELECCIONAR);
}

void FondoMenuPrincipal::actualizar()
{
    // Primero se calcula la posición y el color deseados y luego se
    // acerca un poquito la posición y el color actuales a lo deseado
    sf::Vector2f posicionDeseadaFondo;
    sf::Color colorDeseadoFondo;

    // Si el selector asociado al fondo está seleccionado, se debe ver
    if(posicionRelativa == 0)
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_MENU_PRINCIPAL_SELECCIONADO;
    else
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_MENU_PRINCIPAL_SIN_SELECCIONAR;
    
    // Según la posición relativa, el fondo tendrá una altura u otra
    posicionDeseadaFondo.x = 0;
    posicionDeseadaFondo.y = posicionRelativa * DIFERENCIA_POSICION_Y_FONDO_SELECTOR_MENU_PRINCIPAL;

    // Se acerca la posición y el color del fondo a sus valores deseados
    spriteFondo.setPosition(util::aproximarVector2f(spriteFondo.getPosition(),posicionDeseadaFondo,0.8f));
    spriteFondo.setColor(util::aproximarColor(spriteFondo.getColor(),colorDeseadoFondo,0.8f));
}

void FondoMenuPrincipal::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(spriteFondo,states);
}