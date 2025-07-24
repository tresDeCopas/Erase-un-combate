#include "InfoCombo.hpp"
#include "Constantes.hpp"
#include <assert.h>
#include <iostream>

InfoCombo::InfoCombo(Jugador jugador) :
    jugador(jugador), numeroGolpes(0), ataqueCausado(0),
    comboActivo(true), framesRestantes(FRAMES_RESTANTES_COMBO),
    framesDesdeQueTermino(0)
{
    
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