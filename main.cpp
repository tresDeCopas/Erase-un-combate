#include "Combate.hpp"
#include "ContenedorDeRecursos.hpp"
#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeEfectos.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main(){

    ContenedorDePersonajes::unicaInstancia()->cargarTodosLosPersonajes();

    ContenedorDeEfectos::unicaInstancia()->cargarTodosLosEfectos();

    Combate combate("juan-cuesta-sin-casco", "juan-cuesta-con-casco", "Prueba");

    combate.comenzar();
}
