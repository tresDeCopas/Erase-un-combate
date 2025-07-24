#pragma once

#include <vector>
#include "InfoCombo.hpp"
#include "Enums.hpp"

/*
    Esta clase recopila los distintos combos que se están haciendo
    en un combate y los muestra en pantalla
*/
class ContenedorDeCombos
{
    private:
        ContenedorDeCombos(){}
        ~ContenedorDeCombos();

        static ContenedorDeCombos * contenedorDeCombos;

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
        ContenedorDeCombos(ContenedorDeCombos &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const ContenedorDeCombos &) = delete;

        // Devuelve la única instancia
        static ContenedorDeCombos * unicaInstancia();

};