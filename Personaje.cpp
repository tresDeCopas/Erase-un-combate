#include "Personaje.hpp"
#include "Enums.hpp"
#include "Constantes.hpp"
#include "Utilidades.hpp"
#include "ContenedorDeEfectos.hpp"
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
    accionesRealizadas[accion] = true;
}

void Personaje::detenerAccion(Accion accion){
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

EstadoPersonaje Personaje::getEstado(){
    return estado;
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
    // Si la velocidad es tan baja que se podr�a decir que es cero, termina
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
        else if (accionesRealizadas[Accion::ATACAR]){
            cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_1);
        }

        break;

    case EstadoPersonaje::ANDANDO_ACERCANDOSE:

        if (accionesRealizadas[Accion::ATACAR]){
            cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_1);
        } else if(accionesRealizadas[Accion::ARRIBA]){
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

        if (accionesRealizadas[Accion::ATACAR]){
            cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_1);
        } else if(accionesRealizadas[Accion::ARRIBA]){
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
        break;

    case EstadoPersonaje::ATAQUE_NORMAL_1:

        pararMovimiento();

        if(animaciones[estado]->haTerminado()){
            if(accionesRealizadas[Accion::ATACAR])
                cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_2);
            else
                cambiarEstado(EstadoPersonaje::QUIETO);
        }
        break;
    case EstadoPersonaje::ATAQUE_NORMAL_2:

        pararMovimiento();

        if(animaciones[estado]->haTerminado()){
            if(accionesRealizadas[Accion::ATACAR])
                cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_3);
            else
                cambiarEstado(EstadoPersonaje::QUIETO);
        }
        break;
    case EstadoPersonaje::ATAQUE_NORMAL_3:

        pararMovimiento();

        if(animaciones[estado]->haTerminado()){
            cambiarEstado(EstadoPersonaje::QUIETO);
            accionesRealizadas[Accion::ATACAR] = false;
        }
        break;
    
    case EstadoPersonaje::GOLPEADO_PEQUE:
    case EstadoPersonaje::GOLPEADO_MEDIO:
        pararMovimiento();
        if(animaciones[estado]->haTerminado()){
            cambiarEstado(EstadoPersonaje::QUIETO);
        }

        break;
    case EstadoPersonaje::BLOQUEANDO:
        pararMovimiento();
        if(accionesRealizadas[Accion::ATACAR]){
            cambiarEstado(EstadoPersonaje::ATAQUE_NORMAL_1);
        } else if(animaciones[estado]->haTerminado()){
            cambiarEstado(EstadoPersonaje::QUIETO);
        }

        break;
    }

    // Se comprueba si el enemigo está a la derecha o a la izquierda y se voltea el
    // sprite según sea necesario. Si el personaje está atacando o recibiendo un golpe
    // (incluyendo bloqueo), está demasiado ocupado como para ir volteándose
    switch(estado){
        case EstadoPersonaje::ATAQUE_NORMAL_1:
        case EstadoPersonaje::ATAQUE_NORMAL_2:
        case EstadoPersonaje::ATAQUE_NORMAL_3:
        case EstadoPersonaje::ATAQUE_AEREO:
        case EstadoPersonaje::ATAQUE_AGACHADO:
        case EstadoPersonaje::ATAQUE_SUPER:
        case EstadoPersonaje::GOLPEADO_BAJO:
        case EstadoPersonaje::GOLPEADO_PEQUE:
        case EstadoPersonaje::GOLPEADO_MEDIO:
        case EstadoPersonaje::GOLPEADO_GRANDE:
        case EstadoPersonaje::BLOQUEANDO:
            break;
        
        default:
            if((animaciones[estado]->getPosicion().x < posicionEnemigo.x && !mirandoDerecha) ||
                (animaciones[estado]->getPosicion().x > posicionEnemigo.x && mirandoDerecha)){
                    mirandoDerecha = !mirandoDerecha;
                    for(auto const &[estado, anim] : animaciones){
                        anim->voltear();
                    }
                }
            break;
    }

    animaciones[estado]->actualizar();

    // Una vez se hace todo, se aumenta la velocidad según se vea
    animaciones[estado]->mover(velX,velY);

    // Si el personaje se sale por la derecha, no dejar que pase
    if(animaciones[estado]->getPosicion().x > VENTANA_ANCHURA-1){
        animaciones[estado]->setPosicion(VENTANA_ANCHURA-1,animaciones[estado]->getPosicion().y);
        velX = 0;
    } else if (animaciones[estado]->getPosicion().x < 0){
        animaciones[estado]->setPosicion(0,animaciones[estado]->getPosicion().y);
        velX = 0;
    }
}

void Personaje::comprobarColisiones(std::list<Animacion*> &animaciones, std::list<Animacion*> &efectosInsertados){

    // Se sacan las hitboxes de la animación del estado actual
    std::list<Hitbox> hitboxes = this->animaciones[estado]->getHitboxes();

    // Si la animación del estado actual no tiene hitboxes en este momento, no hace falta comprobar nada
    if(hitboxes.size() == 0) return;

    // Se eliminan las hitboxes con daño
    auto it = hitboxes.begin();
    
    while(it != hitboxes.end()){
        if(it->getFuerzaAtaque() > 0)
            it = hitboxes.erase(it);
        else it++;
    }

    // Se encuentra una colisión entre una hitbox del personaje (hurtbox como la llama la chaviza)
    // y una hitbox del enemigo (la que colisione con más daño)
    Hitbox hitboxElegidaEnemigo = Hitbox(sf::IntRect(0,0,0,0),0,false);
    Hitbox hitboxElegidaPropia = Hitbox(sf::IntRect(0,0,0,0),0,false);

    for(Animacion * anim : animaciones){
        for(Hitbox hEnemigo : anim->getHitboxes()){
            for(Hitbox hPropia : hitboxes){
                
                sf::IntRect rectEnemigo = hEnemigo.getRectangulo();
                rectEnemigo.left += anim->getPosicionEsqSupIzq().x;
                rectEnemigo.top += anim->getPosicionEsqSupIzq().y;

                sf::IntRect rectPropio = hPropia.getRectangulo();
                rectPropio.left += this->animaciones[estado]->getPosicionEsqSupIzq().x;
                rectPropio.top += this->animaciones[estado]->getPosicionEsqSupIzq().y;

                if(rectEnemigo.intersects(rectPropio) && hEnemigo.getFuerzaAtaque() > hitboxElegidaEnemigo.getFuerzaAtaque()){
                    hitboxElegidaEnemigo = Hitbox(rectEnemigo,hEnemigo.getFuerzaAtaque(),hEnemigo.esAtaqueBajo());
                    hitboxElegidaPropia = Hitbox(rectPropio,hPropia.getFuerzaAtaque(),hPropia.esAtaqueBajo());
                }
            }
        }
    }

    // Si no hubo golpe, no hay nada que hacer
    if(hitboxElegidaEnemigo.getFuerzaAtaque() == 0){
        return;
    }

    // Si sí que hubo golpe, depende ya de cómo le pille al personaje
    switch(estado){
        case EstadoPersonaje::GOLPEADO_PEQUE:
        case EstadoPersonaje::QUIETO:
        case EstadoPersonaje::ANDANDO_ACERCANDOSE:
        case EstadoPersonaje::ATAQUE_NORMAL_1:
        case EstadoPersonaje::ATAQUE_NORMAL_2:
        case EstadoPersonaje::ATAQUE_NORMAL_3:

            // TODO Tener en cuenta ataques bajos
            // TODO Tener en cuenta bloqueos

            if(hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_PEQUE){
                velX = mirandoDerecha ? -IMPULSO_GOLPE_PEQUE : IMPULSO_GOLPE_PEQUE;
                cambiarEstado(EstadoPersonaje::GOLPEADO_PEQUE);
            } else if (hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_MEDIO){
                velX = mirandoDerecha ? -IMPULSO_GOLPE_MEDIO : IMPULSO_GOLPE_MEDIO;
                cambiarEstado(EstadoPersonaje::GOLPEADO_MEDIO);
            }
            break;
        
        case EstadoPersonaje::BLOQUEANDO:
        case EstadoPersonaje::ANDANDO_ALEJANDOSE:

            if(hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_PEQUE){
                velX = mirandoDerecha ? -IMPULSO_GOLPE_PEQUE : IMPULSO_GOLPE_PEQUE;
                cambiarEstado(EstadoPersonaje::BLOQUEANDO);
            } else if (hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_MEDIO){
                velX = mirandoDerecha ? -IMPULSO_GOLPE_MEDIO : IMPULSO_GOLPE_MEDIO;
                cambiarEstado(EstadoPersonaje::BLOQUEANDO);
            }
            break;
    }

    // Ahora, se añaden efectos según haya salido la cosa

    // Primero, se va a calcular el punto exacto en el que se debería
    
    sf::Vector2f posicionMedia = util::centroDeInterseccion(hitboxElegidaEnemigo.getRectangulo(),hitboxElegidaPropia.getRectangulo());
    
    Animacion* anim;
    
    // Una vez se sabe dónde se va a colocar, se comprueba cómo está el personaje ahora mismo
    if(estado == EstadoPersonaje::BLOQUEANDO){
        anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("bloqueado");
    } else if (hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_PEQUE){
        anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("golpeado-peque");
    } else if (hitboxElegidaEnemigo.getFuerzaAtaque() <= MAX_ATAQUE_MEDIO){
        anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("golpeado-medio");
    } else {
        // Es importante volver antes de tiempo o si no estaríamos modificando anim mientras
        // es un puntero sin inicializar, lo cual está feo
        return;
    }

    anim->setPosicion(posicionMedia);
    
    efectosInsertados.push_back(anim);

}
