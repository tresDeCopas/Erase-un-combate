#include "Configuracion.hpp"
#include "Constantes.hpp"

Configuracion * Configuracion::configuracion = nullptr;

Configuracion * Configuracion::unicaInstancia()
{
    if(configuracion==nullptr)
        configuracion = new Configuracion();
    return configuracion;
}

Configuracion::Configuracion() : hitboxesVisibles(false), fps(NUMERO_FPS_INICIAL), salidaABitacora(false)
{
    
}

Configuracion::~Configuracion()
{
    
}

void Configuracion::setHitboxesVisibles(bool hitboxesVisibles)
{
    this->hitboxesVisibles = hitboxesVisibles;
}

bool Configuracion::isHitboxesVisibles()
{
    return hitboxesVisibles;
}

void Configuracion::setFPS(int fps)
{
    this->fps = fps;
}

int Configuracion::getFPS()
{
    return fps;
}

void Configuracion::setSalidaABitacora(bool salidaAbitacora)
{
    this->salidaABitacora = salidaABitacora;
}

bool Configuracion::isSalidaABitacora()
{
    return salidaABitacora;
}