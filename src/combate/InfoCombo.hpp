#pragma once

#include "Enums.hpp"

/*
    Esta clase almacena información de un combo
    realizado por un jugador cualquiera
*/
class InfoCombo {
    private:
        // El jugador al que pertenece este combo
        Jugador jugador;

        // El número de golpes del combo
        int numeroGolpes;

        // El ataque causado durante el combo
        int ataqueCausado;

        // Indica si el combo está activo o si se ha roto
        bool comboActivo;

        // Indica cuántos frames le quedan al combo para
        // romperse (a no ser que el personaje que está
        // realizando el combo siga atacando)
        int framesRestantes;

        // Indica hace cuántos frames terminó el combo
        // (esto permite seguir mostrar la información
        // del combo en pantalla aunque ya se haya terminado)
        int framesDesdeQueTermino;
    
    public:

        // Crea un combo vacío (sin golpes ni ataques)
        InfoCombo(Jugador jugador);

        // Devuelve el jugador que está haciendo este combo
        Jugador getJugador();

        // Permite continuar el combo, reseteando el contador
        // y aumentando el número de golpes y el daño causado
        void continuarCombo(int ataque);

        // Termina el combo, por lo que ya no se podrá continuar
        void terminarCombo();

        // Actualiza contadores y mueve los sprites si es necesario
        void actualizar();

        // Indica si los sprites del combo ya han desaparecido de
        // la pantalla, por lo que este InfoCombo deja de ser
        // necesario y puede destruirse
        bool haTerminado();
};