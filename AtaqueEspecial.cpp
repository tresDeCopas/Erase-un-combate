#include "AtaqueEspecial.hpp"
#include "Constantes.hpp"

AtaqueEspecial::AtaqueEspecial(const std::vector<Accion> &acciones) : acciones(acciones), accionActual(0), cooldown(0), esperandoPausa(false){

}

bool AtaqueEspecial::actualizar(std::unordered_set<Accion> &accionesRealizadas){

    if(cooldown > 0) {
        cooldown--;
        if(cooldown == 0){
            resetear();
        }
    }

    if(accionActual < acciones.size()){
        if(esperandoPausa && accionesRealizadas.empty()){
            esperandoPausa = false;
        } else if(!esperandoPausa && accionesRealizadas.size() == 1 && accionesRealizadas.count(acciones[accionActual])){
            accionActual++;
            cooldown = COOLDOWN_ATAQUE_ESPECIAL;
            esperandoPausa = true;
        }
    }
    
    if(accionActual == acciones.size()){
        resetear();
        return true;
    } else {
        return false;
    }
}

void AtaqueEspecial::resetear(){
    accionActual = 0;
    cooldown = 0;
    esperandoPausa = false;
}