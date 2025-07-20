#include "JuanCuesta.hpp"
#include "Constantes.hpp"

void JuanCuesta::actualizar(sf::Vector2u posicionEnemigo){
    animaciones[estado]->actualizar();

    switch(estado){
    case EstadoPersonaje::QUIETO:

        if(accionesRealizadas[Accion::ARRIBA]){
            velY = VELOCIDAD_INICIAL_SALTO;
            cambiarEstado(EstadoPersonaje::SALTANDO);
        } else if (accionesRealizadas[Accion::DERECHA]){
            velX+=VELOCIDAD_ANDAR_AUMENTO;
            if(velX >= VELOCIDAD_ANDAR_MAX)
                velX = VELOCIDAD_ANDAR_MAX;

            if(posicionEnemigo.x < animaciones[EstadoPersonaje::QUIETO]){
                ((AnimacionPorFrames*)animaciones[EstadoPersonaje::ANDANDO_DERECHA])->setTipoBucle(TipoBucle::NORMAL);
            } else {
                ((AnimacionPorFrames*)animaciones[EstadoPersonaje::ANDANDO_DERECHA])->setTipoBucle(TipoBucle::AL_REVES);
            }

            cambiarEstado(EstadoPersonaje::ANDANDO_DERECHA);

        } else if (accionesRealizadas[Accion::IZQUIERDA]){
            velX-=VELOCIDAD_ANDAR_AUMENTO;
            if(velX <= -VELOCIDAD_ANDAR_MAX)
                velX = -VELOCIDAD_ANDAR_MAX;

            if(posicionEnemigo.x > animaciones[EstadoPersonaje::QUIETO]){
                ((AnimacionPorFrames*)animaciones[EstadoPersonaje::ANDANDO_IZQUIERDA])->setTipoBucle(TipoBucle::NORMAL);
            } else {
                ((AnimacionPorFrames*)animaciones[EstadoPersonaje::ANDANDO_IZQUIERDA])->setTipoBucle(TipoBucle::AL_REVES);
            }

            cambiarEstado(EstadoPersonaje::ANDANDO_DERECHA);
        }

        break;

    case EstadoPersonaje::ANDANDO_DERECHA:



        break;
    }
}

void JuanCuesta::comprobarColisiones(std::list<Animacion*> &animaciones){

}

Personaje * JuanCuesta::clonar(){
    return new JuanCuesta(*this);
}
