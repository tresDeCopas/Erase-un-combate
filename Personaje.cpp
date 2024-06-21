#include "Personaje.hpp"
#include "Enums.hpp"
#include "Constantes.hpp"
#include <iostream>

Personaje::Personaje(std::map<EstadoPersonaje,Animacion*> animaciones){
    puntosDeVida = MAX_PUNTOS_DE_VIDA;
    velY = 0;
    velX = 0;
    this->animaciones = animaciones;
    estado = EstadoPersonaje::QUIETO;
    mirandoDerecha = true;
}

void Personaje::realizarAccion(Accion accion){
    std::cerr << "Realizando accion" << std::endl;
    accionesRealizadas[accion] = true;
}

void Personaje::detenerAccion(Accion accion){
    std::cerr << "Deteniendo accion" << std::endl;
    accionesRealizadas[accion] = false;
}

int Personaje::getPuntosDeVida(){
    return puntosDeVida;
}

void Personaje::setPosicion(float x, float y){
    animaciones[estado]->setPosicion(x,y);
}

void Personaje::setPosicion(sf::Vector2f posicion){
    animaciones[estado]->setPosicion(posicion);
}

sf::Vector2f Personaje::getPosicion(){
    return animaciones[estado]->getPosicion();
}

void Personaje::setJugador(Jugador jugador){
    this->jugador = jugador;
}

std::map<EstadoPersonaje,Animacion*> Personaje::getAnimaciones(){
    return animaciones;
}

void Personaje::setAnimaciones(std::map<EstadoPersonaje,Animacion*> animaciones){
    this->animaciones = animaciones;
}

void Personaje::cambiarEstado(EstadoPersonaje estadoNuevo){

    animaciones.at(estadoNuevo)->setPosicion(animaciones.at(estado)->getPosicion());
    animaciones.at(estadoNuevo)->resetear();
    estado = estadoNuevo;
}

void Personaje::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(*(animaciones.at(estado)),states);
}

void Personaje::moverseIzquierda(){
    // La velocidad disminuye un poco pero sin pasarse
    velX-=VELOCIDAD_ANDAR_AUMENTO;
    if(velX <= -VELOCIDAD_ANDAR_MAX)
        velX = -VELOCIDAD_ANDAR_MAX;
}

void Personaje::moverseDerecha(){
    // La velocidad aumenta un poco pero sin pasarse
    velX+=VELOCIDAD_ANDAR_AUMENTO;
    if(velX >= VELOCIDAD_ANDAR_MAX)
        velX = VELOCIDAD_ANDAR_MAX;
}

void Personaje::pararMovimiento(){
    // Si la velocidad es tan baja que se podría decir que es cero, termina
    // directamente para no entrar en un bucle
    if(std::abs(velX) < UMBRAL_FLOAT) return;

    // Si la velocidad es positiva se baja, si no se sube
    bool positivo = velX > 0;
    if(positivo){
        velX-=VELOCIDAD_ANDAR_AUMENTO;
    } else {
        velX+=VELOCIDAD_ANDAR_AUMENTO;
    }

    // Si la velocidad se ha pasado de 0, se pone a 0 y el personaje ya se para del todo
    if((positivo && velX < 0) ||
       (!positivo && velX > 0)) velX = 0;
}

void Personaje::actualizar(sf::Vector2f posicionEnemigo){

    // Se comprueba si el enemigo está a la derecha o a la izquierda
    if((animaciones[estado]->getPosicion().x < posicionEnemigo.x && !mirandoDerecha) ||
       (animaciones[estado]->getPosicion().x > posicionEnemigo.x && mirandoDerecha)){
        mirandoDerecha = !mirandoDerecha;
        for(auto const &[estado, anim] : animaciones){
            anim->voltear();
        }
    }
    animaciones[estado]->actualizar();

    // Según el estado, se hace una cosa u otra
    switch(estado){
    case EstadoPersonaje::QUIETO:

        pararMovimiento();

        if(accionesRealizadas[Accion::ARRIBA])
        {
            velY = VELOCIDAD_SALTO;
            accionesRealizadas[Accion::ARRIBA] = false;
            cambiarEstado(EstadoPersonaje::SALTANDO_SUBIENDO);
        }
        else if (accionesRealizadas[Accion::DERECHA])
        {
            velX+=VELOCIDAD_ANDAR_AUMENTO;
            if(velX >= VELOCIDAD_ANDAR_MAX)
                velX = VELOCIDAD_ANDAR_MAX;

            if(mirandoDerecha)
                cambiarEstado(EstadoPersonaje::ANDANDO_ACERCANDOSE);
            else
                cambiarEstado(EstadoPersonaje::ANDANDO_ALEJANDOSE);

        }
        else if (accionesRealizadas[Accion::IZQUIERDA])
        {
            velX-=VELOCIDAD_ANDAR_AUMENTO;
            if(velX <= -VELOCIDAD_ANDAR_MAX)
                velX = -VELOCIDAD_ANDAR_MAX;

            if(!mirandoDerecha)
                cambiarEstado(EstadoPersonaje::ANDANDO_ACERCANDOSE);
            else
                cambiarEstado(EstadoPersonaje::ANDANDO_ALEJANDOSE);
        }

        break;

    case EstadoPersonaje::ANDANDO_ACERCANDOSE:

        if(accionesRealizadas[Accion::ARRIBA]){
            velY = VELOCIDAD_SALTO;
            accionesRealizadas[Accion::ARRIBA] = false;
            cambiarEstado(EstadoPersonaje::SALTANDO_SUBIENDO);
        } else if(accionesRealizadas[Accion::DERECHA]){
            moverseDerecha();
            if(!mirandoDerecha){
                cambiarEstado(EstadoPersonaje::ANDANDO_ALEJANDOSE);
            }
        } else if(accionesRealizadas[Accion::IZQUIERDA]){
            moverseIzquierda();
            if(mirandoDerecha){
                cambiarEstado(EstadoPersonaje::ANDANDO_ALEJANDOSE);
            }
        } else {
            pararMovimiento();
            cambiarEstado(EstadoPersonaje::QUIETO);
        }

        break;
    case EstadoPersonaje::ANDANDO_ALEJANDOSE:

        if(accionesRealizadas[Accion::ARRIBA]){
            velY = VELOCIDAD_SALTO;
            accionesRealizadas[Accion::ARRIBA] = false;
            cambiarEstado(EstadoPersonaje::SALTANDO_SUBIENDO);
        } else if(accionesRealizadas[Accion::DERECHA]){
            moverseDerecha();
            if(mirandoDerecha){
                cambiarEstado(EstadoPersonaje::ANDANDO_ACERCANDOSE);
            }
        } else if(accionesRealizadas[Accion::IZQUIERDA]){
            moverseIzquierda();
            if(!mirandoDerecha){
                cambiarEstado(EstadoPersonaje::ANDANDO_ACERCANDOSE);
            }
        } else {
            pararMovimiento();
            cambiarEstado(EstadoPersonaje::QUIETO);
        }

        break;

    case EstadoPersonaje::SALTANDO_SUBIENDO:
        velY+=GRAVEDAD;

        if(accionesRealizadas[Accion::DERECHA]) moverseDerecha();
        else if (accionesRealizadas[Accion::IZQUIERDA]) moverseIzquierda();

        if(velY > 0)
            cambiarEstado(EstadoPersonaje::SALTANDO_BAJANDO);
        break;

    case EstadoPersonaje::SALTANDO_BAJANDO:
        velY+=GRAVEDAD;

        if(accionesRealizadas[Accion::DERECHA]) moverseDerecha();
        else if (accionesRealizadas[Accion::IZQUIERDA]) moverseIzquierda();

        if(animaciones[estado]->getPosicion().y > ALTURA_SUELO){
            animaciones[estado]->setPosicion(animaciones[estado]->getPosicion().x,ALTURA_SUELO);
            velY = 0;
            cambiarEstado(EstadoPersonaje::QUIETO);
        }
    }

    // Una vez se hace todo, se aumenta la velocidad según se vea
    animaciones[estado]->mover(velX,velY);
}

void Personaje::comprobarColisiones(std::list<Animacion*> &animaciones){

}
