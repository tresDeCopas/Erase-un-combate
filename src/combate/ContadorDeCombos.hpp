#pragma once

#include <vector>
#include "Enums.hpp"

// Esta estructura guarda información sobre un combo
struct InfoCombo{

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

    // Indica hace cuántos frames comenzó el combo
    int framesTotales;
};

/*
    Esta clase se encarga de hacer un recuento de los golpes que
    sufre el personaje de cada jugador, mostrando en pantalla los
    combos que se hacen y su longitud. Es una clase Singleton, por
    lo que ambos personajes la comparten y le deben dar información
    sobre los ataques que se están haciendo
*/
class ContadorDeCombos
{
    private:
        ContadorDeCombos(){}
        ~ContadorDeCombos();

        static ContadorDeCombos * contadorDeCombos;

        // Todos los combos que se están haciendo actualmente
        std::vector<InfoCombo> combos;
        

    public:

        // Permite actualizar el estado de los combos que se están haciendo
        void actualizar();

        // Permite informar sobre un suceso de relevancia para los combos. Se debe indicar
        // el jugador que ha realizado la acción que se quiere informar, junto con un booleano
        // que indica si esa acción ha permitido o no continuar un combo, y un entero que indica
        // (en caso de que se continúe o comience el combo) el daño causado. Por ejemplo, si un
        // jugador bloquea un ataque, el combo del otro jugador se rompe y se debe informar.
        // Por otra parte, si un jugador ataca al otro, el primero continúa (o comienza) un
        // combo, y es necesario indicar el daño causado por el combo
        void informar(Jugador jugador, bool continuaComboo, int ataque = 0);

        // NUNCA SE COPIA UN SINGLETON
        ContadorDeCombos(ContadorDeCombos &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const ContadorDeCombos &) = delete;

        // Devuelve la única instancia
        static ContadorDeCombos * unicaInstancia();

};