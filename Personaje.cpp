#include "Personaje.hpp"
#include "Enums.hpp"
#include "Constantes.hpp"

Personaje::Personaje(std::map<EstadoPersonaje,Animacion*> animaciones){
    puntosDeVida = MAX_PUNTOS_DE_VIDA;
}

void Personaje::realizarAccion(Accion accion){
    accionesRealizadas[accion] = true;
}

void Personaje::detenerAccion(Accion accion){
    accionesRealizadas[accion] = false;
}

int Personaje::getPuntosDeVida(){
    return puntosDeVida;
}

void Personaje::setJugador(Jugador jugador){
    this->jugador = jugador;
}

void Personaje::cambiarEstado(EstadoPersonaje estadoNuevo){

    animaciones.at(estadoNuevo)->setPosicion(animaciones.at(estado)->getPosicion());
    animaciones.at(estadoNuevo)->resetear();
    estado = estadoNuevo;
}
