#include "ReproductorDeSonidos.hpp"
#include "ContenedorDeRecursos.hpp"
#include "Bitacora.hpp"
#include <filesystem>

ReproductorDeSonidos * ReproductorDeSonidos::reproductorDeSonidos = nullptr;

ReproductorDeSonidos * ReproductorDeSonidos::unicaInstancia()
{
    if(reproductorDeSonidos==nullptr)
        reproductorDeSonidos = new ReproductorDeSonidos();
    return reproductorDeSonidos;
}

ReproductorDeSonidos::ReproductorDeSonidos(){
    volumenActual = VOLUMEN_MAXIMO_SONIDOS;
}

void ReproductorDeSonidos::reproducir(std::string sonido)
{
    // Primero se crea el sonido si no existe
    if(!sonidos.count(sonido)){
        sonidos[sonido].setBuffer(ContenedorDeSonidos::unicaInstanciaSonidos()->obtener(sonido));
    } 

    // Se reproduce el sonido requerido
    sonidos[sonido].setVolume(volumenActual);
    sonidos[sonido].play();
}

float ReproductorDeSonidos::getVolumen()
{
    return volumenActual;
}

void ReproductorDeSonidos::setVolumen(float nuevoVolumen)
{
    volumenActual = (nuevoVolumen > VOLUMEN_MAXIMO_MUSICA ? VOLUMEN_MAXIMO_MUSICA : nuevoVolumen < 0 ? 0 : nuevoVolumen);
}
