#include "ContadorDeCombos.hpp"
#include "Constantes.hpp"
#include <iostream>

ContadorDeCombos *ContadorDeCombos::contadorDeCombos = nullptr;

ContadorDeCombos *ContadorDeCombos::unicaInstancia()
{
    if (contadorDeCombos == nullptr)
        contadorDeCombos = new ContadorDeCombos();
    return contadorDeCombos;
}

ContadorDeCombos::~ContadorDeCombos()
{
    if (contadorDeCombos != nullptr)
        delete contadorDeCombos;
}

void ContadorDeCombos::actualizar()
{
    for(InfoCombo& infoCombo : combos)
    {
        infoCombo.framesTotales++;

        if(infoCombo.comboActivo)
        {
            if(infoCombo.framesRestantes == 0)
                infoCombo.comboActivo = false;
            else
                infoCombo.framesRestantes--;
        }
    }
}

void ContadorDeCombos::informar(Jugador jugador, bool continuaCombo, int ataque)
{
    // Es importante comprobar si existe un combo
    bool comboEncontrado = false;

    for(InfoCombo& infoCombo : combos)
    {
        if(infoCombo.jugador == jugador && infoCombo.comboActivo)
        {
            comboEncontrado = true;

            if(continuaCombo)
            {
                infoCombo.ataqueCausado+=ataque;
                infoCombo.numeroGolpes++;
                infoCombo.framesRestantes = FRAMES_RESTANTES_COMBO;
            }
            else
            {
                infoCombo.framesRestantes = 0;
                infoCombo.comboActivo = false;
            }

            std::cerr << "\rCombo J" << (infoCombo.jugador == Jugador::JUGADOR1 ? "1" : "2") << ": " << infoCombo.numeroGolpes << " golpes, " << std::to_string(infoCombo.ataqueCausado) << " de ataque";
        }
    }

    // Si no hay ningún combo activo realizado por el jugador indicado,
    // es necesario crear un nuevo combo
    if(continuaCombo && !comboEncontrado)
    {
        InfoCombo nuevoCombo;
        nuevoCombo.ataqueCausado = ataque;
        nuevoCombo.comboActivo = true;
        nuevoCombo.framesRestantes = FRAMES_RESTANTES_COMBO;
        nuevoCombo.framesTotales = 0;
        nuevoCombo.jugador = jugador;
        nuevoCombo.numeroGolpes = 1;

        combos.push_back(nuevoCombo);

        std::cerr << "\nCombo J" << (nuevoCombo.jugador == Jugador::JUGADOR1 ? "1" : "2") << ": " << nuevoCombo.numeroGolpes << " golpes, " << std::to_string(nuevoCombo.ataqueCausado) << " de ataque";
    }
}