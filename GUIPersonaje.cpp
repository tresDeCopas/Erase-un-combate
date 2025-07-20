#include "GUIPersonaje.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"

GUIPersonaje::GUIPersonaje(Personaje &personaje) : personaje(personaje){
    
    rectanguloVidaReal.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_VIDA_IZQUIERDA);
    rectanguloVidaReal.setSize(TAMANO_BARRA_VIDA);
    rectanguloVidaReal.setFillColor(COLOR_BARRA_VIDA_REAL);

    rectanguloVidaAtrasada.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_VIDA_IZQUIERDA);
    rectanguloVidaAtrasada.setSize(TAMANO_BARRA_VIDA);
    rectanguloVidaAtrasada.setFillColor(COLOR_BARRA_VIDA_ATRASADA);

    rectanguloSuper.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_SUPER_IZQUIERDA);
    rectanguloSuper.setSize(sf::Vector2f(0,TAMANO_BARRA_SUPER.y));
    rectanguloSuper.setFillColor(COLOR_BARRA_SUPER);

    contadorVidaAtrasado = MAX_PUNTOS_DE_VIDA;
    retrasoContadorVidaAtrasado = 0;

    spritePortrait.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+personaje.nombre+"/portrait.png"));
    spritePortrait.setPosition(POSICION_GUI_IZQUIERDA+POSICION_PORTRAIT_IZQUIERDA);

    spriteNombre.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+personaje.nombre+"/nombre.png"));
    spriteNombre.setPosition(POSICION_GUI_IZQUIERDA+POSICION_NOMBRE_IZQUIERDA);

    spritePrincipalBase.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/base-izquierda-0.png"));
    spritePrincipalFrente.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/frente-izquierda.png"));
    spritePrincipalBase.setPosition(POSICION_GUI_IZQUIERDA);
    spritePrincipalFrente.setPosition(POSICION_GUI_IZQUIERDA);
}

void GUIPersonaje::actualizar(){
    if(retrasoContadorVidaAtrasado == 0){
        if(personaje.puntosDeVida > contadorVidaAtrasado){
            contadorVidaAtrasado++;
            retrasoContadorVidaAtrasado = MAX_RETRASO_MEDIDOR_VIDA_ATRASADO;
        } else if(personaje.puntosDeVida < contadorVidaAtrasado){
            contadorVidaAtrasado--;
            retrasoContadorVidaAtrasado = MAX_RETRASO_MEDIDOR_VIDA_ATRASADO;
        }
        
    } else {
        retrasoContadorVidaAtrasado--;
    }

    rectanguloVidaReal.setSize(sf::Vector2f(((float)personaje.puntosDeVida/MAX_PUNTOS_DE_VIDA)*TAMANO_BARRA_VIDA.x,rectanguloVidaReal.getSize().y));
    rectanguloVidaAtrasada.setSize(sf::Vector2f(((float)contadorVidaAtrasado/MAX_PUNTOS_DE_VIDA)*TAMANO_BARRA_VIDA.x,rectanguloVidaAtrasada.getSize().y));
    
    rectanguloSuper.setSize(sf::Vector2f(((float)personaje.medidorSuper/MAX_MEDIDOR_SUPER)*TAMANO_BARRA_SUPER.x,rectanguloSuper.getSize().y));
}

void GUIPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(spritePrincipalBase,states);
    target.draw(rectanguloVidaAtrasada,states);
    target.draw(rectanguloVidaReal,states);
    target.draw(rectanguloSuper,states);
    target.draw(spriteNombre,states);
    target.draw(spritePortrait,states);
    target.draw(spritePrincipalFrente,states);
}