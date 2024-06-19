#include "ContenedorDePersonajes.hpp"
#include "Bitacora.hpp"
#include "JuanCuesta.hpp"

ContenedorDePersonajes * ContenedorDePersonajes::contenedorDePersonajes = nullptr;

ContenedorDePersonajes * ContenedorDePersonajes::unicaInstancia()
{
    if(contenedorDePersonajes==nullptr)
        contenedorDePersonajes = new ContenedorDePersonajes();
    return contenedorDePersonajes;
}

void ContenedorDePersonajes::cargar(IDPersonaje identificador, const std::string ruta)
{
    Personaje * personaje;
    std::map<EstadoPersonaje,Animacion*> animaciones;

    // TODO: un follon de tres pares de cojone

    switch(identificador){
    case IDPersonaje::JUAN_CUESTA:
        personaje = new JuanCuesta(animaciones);
        break;
    }

    personajes[identificador] = personaje;
}

Personaje * ContenedorDePersonajes::obtenerPersonaje(IDPersonaje identificador){
    return personajes[identificador]->clonar();
}

void ContenedorDePersonajes::cargarTodosLosPersonajes()
{
    cargar(IDPersonaje::JUAN_CUESTA,"datos/personajes/juancuesta.dat");
}
