#include "Combate.hpp"
#include "ContenedorDeRecursos.hpp"
#include "ContenedorDePersonajes.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(){

    ContenedorDeTexturas::unicaInstanciaTexturas()->cargarTodasLasTexturas();

    ContenedorDePersonajes::unicaInstancia()->cargarTodosLosPersonajes();


    Combate combate("juan-cuesta", "juan-cuesta", "Prueba");

    combate.comenzar();
}
