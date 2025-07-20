#include "ContenedorDePersonajes.hpp"
#include "Bitacora.hpp"

ContenedorDePersonajes * ContenedorDePersonajes::contenedorDePersonajes = nullptr;

ContenedorDePersonajes * ContenedorDePersonajes::unicaInstancia()
{
    if(contenedorDePersonajes==nullptr)
        contenedorDePersonajes = new ContenedorDePersonajes();
    return contenedorDePersonajes;
}

Personaje ContenedorDePersonajes::obtenerPersonaje(std::string nombre){
    return personajes.at(nombre);
}

void ContenedorDePersonajes::cargarTodosLosPersonajes()
{
    while(false){

        std::map<EstadoPersonaje,Animacion*> animaciones;

        // TODO: un follon de tres pares de cojones

        //personajes[nombre] = Personaje();
    }
}
