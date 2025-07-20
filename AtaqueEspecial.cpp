#include "AtaqueEspecial.hpp"
#include "Constantes.hpp"

AtaqueEspecial::AtaqueEspecial(){
    acciones.push_back(Accion::DERECHA);
    acciones.push_back(Accion::IZQUIERDA);
    acciones.push_back(Accion::ABAJO);
    acciones.push_back(Accion::ATACAR);
    accionActual = 0;
}

// AtaqueEspecial::AtaqueEspecial(const std::vector<Accion> &acciones) : acciones(acciones), accionActual(0) {

// }

bool AtaqueEspecial::actualizar(std::unordered_set<Accion> &accionesRealizadas){

    if(esperandoPausa && accionesRealizadas)

    if(cooldown > 0) cooldown--;
    if(cooldown == 0) accionActual = 0;

    if(accionActual < acciones.size() && accionesRealizadas.size() == 1 && accionesRealizadas.count(acciones[accionActual])){
        accionActual++;
        cooldown = COOLDOWN_ATAQUE_ESPECIAL;
    }

    return accionActual == acciones.size();
}

void AtaqueEspecial::resetear(){
    accionActual = 0;
    cooldown = 0;
}