#include "InfoCombo.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"
#include "ReproductorDeSonidos.hpp"
#include "Utilidades.hpp"
#include <assert.h>
#include <iostream>

InfoCombo::InfoCombo(Jugador jugador) :
    jugador(jugador), numeroGolpes(0), ataqueCausado(0),
    comboActivo(true), fotogramasRestantes(FRAMES_RESTANTES_COMBO),
    fotogramasDesdeQueTermino(0),
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
    // Para continuar un combo, este debe estar activo
    assert(comboActivo);


    // Se incrementa en 1 el número de golpes y se suma
    // el ataque causado ahora al ataque total causado
    numeroGolpes++;
    ataqueCausado += ataque;

    // Los fotogramas restantes para que se 
    fotogramasRestantes = FRAMES_RESTANTES_COMBO;

    if(numeroGolpes == MIN_GOLPES_MOSTRAR_COMBO)
    {
        if(jugador == Jugador::JUGADOR1)
            posicionDeseada = {MARGEN_HORIZONTAL_INFO_COMBO,POSICION_Y_INFO_COMBO};
        else
            posicionDeseada = {VENTANA_ANCHURA-spriteTexto.getTextureRect().size.x-MARGEN_HORIZONTAL_INFO_COMBO,POSICION_Y_INFO_COMBO};
    }
    else if(numeroGolpes > MIN_GOLPES_MOSTRAR_COMBO)
    {
        spriteTexto.move(MOVIMIENTO_INFO_COMBO_CONTINUAR);

        for(sf::Sprite &sprite : spritesNumeroGolpes)
        {
            sprite.move(MOVIMIENTO_INFO_COMBO_CONTINUAR);
        }

        for(sf::Sprite &sprite : spritesNumeroPuntosDeDano)
        {
            sprite.move(MOVIMIENTO_INFO_COMBO_CONTINUAR);
        }
    }

    // Se reproduce un sonidito cada vez que se continúa el combo (si se ha
    // llegado al mínimo de golpes para que se considere un combo de verdad)
    if(numeroGolpes >= MIN_GOLPES_MOSTRAR_COMBO)
    {
        float tono = (numeroGolpes-MIN_GOLPES_MOSTRAR_COMBO)*0.05f+1.f;

        if(tono > MAX_TONO_SONIDO_CONTINUAR_COMBO)
        {
            tono = MAX_TONO_SONIDO_CONTINUAR_COMBO;
        }

        ReproductorDeSonidos::unicaInstancia()->reproducir("sonidos/combos/continuar-combo.ogg",tono);
    }

    std::cerr << "\rCombo J" << (jugador == Jugador::JUGADOR1 ? "1" : "2") << ": " << numeroGolpes << " golpes, " << ataqueCausado << " de ataque";
}

void InfoCombo::terminarCombo()
{
    if(comboActivo && numeroGolpes >= MIN_GOLPES_MOSTRAR_COMBO)
    {
        ReproductorDeSonidos::unicaInstancia()->reproducir("sonidos/combos/terminar-combo.ogg");

        posicionDeseada = {spriteTexto.getPosition().x,spriteTexto.getPosition().y+spriteTexto.getTextureRect().size.y};
        
        spriteTexto.setColor(COLOR_COMBO_TERMINADO);

        for(sf::Sprite &sprite : spritesNumeroGolpes)
        {
            sprite.setColor(COLOR_COMBO_TERMINADO);
        }

        for(sf::Sprite &sprite : spritesNumeroPuntosDeDano)
        {
            sprite.setColor(COLOR_COMBO_TERMINADO);
        }
    }

    comboActivo = false;
}

void InfoCombo::actualizar()
{
    // Se actualiza la posición
    spriteTexto.setPosition({util::aproximarFloat(spriteTexto.getPosition().x,posicionDeseada.x,0.8),
                             util::aproximarFloat(spriteTexto.getPosition().y,posicionDeseada.y,0.8)});

    if(comboActivo)
    {
        fotogramasRestantes--;
        if(fotogramasRestantes <= 0) terminarCombo();
    }
    else
    {
        fotogramasDesdeQueTermino++;

        // Una vez se llega a la mitad del tiempo en el que se muestra
        // la info del combo tras terminar este, la info se empieza a 
        // desvanecer (se vuelve transparente)
        if(fotogramasDesdeQueTermino > FRAMES_MOSTRAR_COMBO_TERMINADO/2)
        {
            sf::Color nuevoColor = spriteTexto.getColor();
            nuevoColor.a = 255*(1.f-((fotogramasDesdeQueTermino-FRAMES_MOSTRAR_COMBO_TERMINADO/2.f)/(FRAMES_MOSTRAR_COMBO_TERMINADO/2.f)));
            spriteTexto.setColor(nuevoColor);
        }
    }
}

bool InfoCombo::sigueActivo()
{
    return comboActivo;
}

bool InfoCombo::haTerminado()
{
    return !comboActivo && fotogramasDesdeQueTermino == FRAMES_MOSTRAR_COMBO_TERMINADO;
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
