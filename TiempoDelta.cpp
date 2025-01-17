#include "TiempoDelta.hpp"
#include "Constantes.hpp"

// Las variables estáticas para implementar Singleton se inicializan nulas
TiempoDelta * TiempoDelta::tiempoDelta = nullptr;

TiempoDelta * TiempoDelta::unicaInstancia(){
    if(tiempoDelta == nullptr)
        tiempoDelta = new TiempoDelta;
    return tiempoDelta;
}

float TiempoDelta::getFraccionDelta(){
    return fraccionDelta;
}

void TiempoDelta::resetearDelta(){
    fraccionDelta = relojDelta.restart().asSeconds() * NUMERO_FPS;
}