#include "InfoCombo.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"
#include <assert.h>
#include <iostream>

InfoCombo::InfoCombo(Jugador jugador) :
    jugador(jugador), numeroGolpes(0), ataqueCausado(0),
    comboActivo(true), framesRestantes(FRAMES_RESTANTES_COMBO),
    framesDesdeQueTermino(0),
    spriteGolpes(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/combos/golpes.png")),
    spritePuntosDeDano(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/combos/puntos-de-daño.png"))
{
    if(jugador == Jugador::JUGADOR1)
    {
        spriteGolpes.setColor(COLOR_INFO_COMBO_J1);
        spritePuntosDeDano.setColor(COLOR_INFO_COMBO_J1);
        spriteGolpes.setPosition(POSICION_INFO_COMBO_GOLPES_J1);
    }
    else if(jugador == Jugador::JUGADOR2)
    {
        spriteGolpes.setColor(COLOR_INFO_COMBO_J2);
        spritePuntosDeDano.setColor(COLOR_INFO_COMBO_J2);
        spriteGolpes.setPosition(POSICION_INFO_COMBO_GOLPES_J2);
    }

    spritePuntosDeDano.setPosition(spriteGolpes.getPosition() + POSICION_RELATIVA_INFO_COMBO_PUNTOS_DE_DANO);
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

    std::cerr << "\rCombo J" << (jugador == Jugador::JUGADOR1 ? "1" : "2") << ": " << numeroGolpes << " golpes, " << ataqueCausado << " de ataque";
}

void InfoCombo::terminarCombo()
{
    comboActivo = false;
}

void InfoCombo::actualizar()
{
    if(comboActivo)
    {
        framesRestantes--;
        if(framesRestantes <= 0) terminarCombo();
    }
    else
    {
        framesDesdeQueTermino++;
    }
}

bool InfoCombo::haTerminado()
{
    return !comboActivo;
}

void InfoCombo::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(spriteGolpes,states);
    target.draw(spritePuntosDeDano,states);

    for(const sf::Sprite& sprite : spritesNumeroGolpes)
    {
        target.draw(sprite,states);
    }

    for(const sf::Sprite& sprite : spritesNumeroPuntosDeDano)
    {
        target.draw(sprite,states);
    }
}