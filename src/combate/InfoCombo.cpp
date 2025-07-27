#include "InfoCombo.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"
#include "Utilidades.hpp"
#include <assert.h>
#include <iostream>

InfoCombo::InfoCombo(Jugador jugador) :
    jugador(jugador), numeroGolpes(0), ataqueCausado(0),
    comboActivo(true), framesRestantes(FRAMES_RESTANTES_COMBO),
    framesDesdeQueTermino(0),
    spriteTexto(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/combos/j" + std::string(jugador == Jugador::JUGADOR1 ? "1" : "2") + "-texto.png"))
{
    if(jugador == Jugador::JUGADOR1)
    {
        spriteTexto.setPosition({0.f-MARGEN_HORIZONTAL_INFO_COMBO-spriteTexto.getTextureRect().size.x,POSICION_Y_INFO_COMBO});
    }
    else if(jugador == Jugador::JUGADOR2)
    {
        spriteTexto.setPosition({VENTANA_ANCHURA+MARGEN_HORIZONTAL_INFO_COMBO,POSICION_Y_INFO_COMBO});
    }

    posicionDeseada = spriteTexto.getPosition();
}

Jugador InfoCombo::getJugador()
{
    return jugador;
}

void InfoCombo::continuarCombo(int ataque)
{
    assert(comboActivo);

    numeroGolpes++;
    ataqueCausado += ataque;
    framesRestantes = FRAMES_RESTANTES_COMBO;

    if(numeroGolpes == MIN_GOLPES_MOSTRAR_COMBO)
    {
        if(jugador == Jugador::JUGADOR1)
            posicionDeseada = {MARGEN_HORIZONTAL_INFO_COMBO,POSICION_Y_INFO_COMBO};
        else
            posicionDeseada = {VENTANA_ANCHURA-spriteTexto.getTextureRect().size.x-MARGEN_HORIZONTAL_INFO_COMBO,POSICION_Y_INFO_COMBO};
    }

    std::cerr << "\rCombo J" << (jugador == Jugador::JUGADOR1 ? "1" : "2") << ": " << numeroGolpes << " golpes, " << ataqueCausado << " de ataque";
}

void InfoCombo::terminarCombo()
{
    if(comboActivo)
    {
        comboActivo = false;
        posicionDeseada = {spriteTexto.getPosition().x,spriteTexto.getPosition().y+spriteTexto.getTextureRect().size.y};
    }
}

void InfoCombo::actualizar()
{
    // Se actualiza la posición
    spriteTexto.setPosition({util::aproximarFloat(spriteTexto.getPosition().x,posicionDeseada.x,0.8),
                             util::aproximarFloat(spriteTexto.getPosition().y,posicionDeseada.y,0.8)});

    if(comboActivo)
    {
        framesRestantes--;
        if(framesRestantes <= 0) terminarCombo();
    }
    else
    {
        framesDesdeQueTermino++;

        // Una vez se llega a la mitad del tiempo en el que se muestra
        // la info del combo tras terminar este, la info se empieza a 
        // desvanecer (se vuelve transparente)
        if(framesDesdeQueTermino > FRAMES_MOSTRAR_COMBO_TERMINADO/2)
        {
            spriteTexto.setColor(sf::Color(255,255,255,255*(1.f-((framesDesdeQueTermino-FRAMES_MOSTRAR_COMBO_TERMINADO/2.f)/(FRAMES_MOSTRAR_COMBO_TERMINADO/2.f)))));
        }
    }
}

bool InfoCombo::sigueActivo()
{
    return comboActivo;
}

bool InfoCombo::haTerminado()
{
    return !comboActivo && framesDesdeQueTermino == FRAMES_MOSTRAR_COMBO_TERMINADO;
}

void InfoCombo::draw(sf::RenderTarget& target, sf::RenderStates states) const {

    // Si no se llega al mínimo número de golpes para mostrar
    // el combo, no se dibuja
    if(numeroGolpes < MIN_GOLPES_MOSTRAR_COMBO)
        return;

    target.draw(spriteTexto,states);

    for(const sf::Sprite& sprite : spritesNumeroGolpes)
    {
        target.draw(sprite,states);
    }

    for(const sf::Sprite& sprite : spritesNumeroPuntosDeDano)
    {
        target.draw(sprite,states);
    }
}
