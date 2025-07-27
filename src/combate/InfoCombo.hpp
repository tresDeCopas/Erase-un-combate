#pragma once

#include "Enums.hpp"
#include <SFML/Graphics.hpp>

/*
    Esta clase almacena información de un combo
    realizado por un jugador cualquiera
*/
class InfoCombo : public sf::Drawable {
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

        // La posición a la que se debe acercar la info sobre
        // el combo. Esto hace que la info se mueva gradualmente
        // en vez de teletransportarse
        sf::Vector2f posicionDeseada;

        // Un sprite con un texto que dice "GOLPES" arriba y
        // "DAÑO" abajo para poder indicar el número de golpes
        // que tiene el combo y el daño causado
        sf::Sprite spriteTexto;

        // Varios sprites con los números que indican la cantidad
        // de golpes del combo
        std::vector<sf::Sprite> spritesNumeroGolpes;

        // Varios sprites con los números que indican la cantidad
        // de puntos de daño que se han causado durante el combo
        std::vector<sf::Sprite> spritesNumeroPuntosDeDano;
    
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

        // Indica si el combo sigue activo y se puede continuar
        bool sigueActivo();

        // Indica si los sprites del combo ya han desaparecido de
        // la pantalla, por lo que este InfoCombo deja de ser
        // necesario y puede destruirse
        bool haTerminado();

        // Dibuja la información sobre el combo realizado
        void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};