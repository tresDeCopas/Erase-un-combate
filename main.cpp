#include "Combate.hpp"
#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeEfectos.hpp"

int main(){

    // Los personajes y efectos son recursos que se tienen que cargar desde un principio.
    // Los recursos más sencillos (efectos de sonido, fuentes, texturas) se pueden cargar al vuelo según se
    // necesite
    ContenedorDePersonajes::unicaInstancia()->cargarTodosLosPersonajes();

    ContenedorDeEfectos::unicaInstancia()->cargarTodosLosEfectos();

    Combate combate("juan-cuesta-sin-casco", "juan-cuesta-con-casco", "fachada");

    combate.comenzar();
}