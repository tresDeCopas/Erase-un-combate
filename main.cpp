#include "Combate.hpp"
#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeEfectos.hpp"

int main(){

    ContenedorDePersonajes::unicaInstancia()->cargarTodosLosPersonajes();

    ContenedorDeEfectos::unicaInstancia()->cargarTodosLosEfectos();

    Combate combate("juan-cuesta-sin-casco", "juan-cuesta-con-casco", "Prueba");

    combate.comenzar();
}