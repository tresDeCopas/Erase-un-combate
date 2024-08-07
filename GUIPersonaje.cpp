#include "GUIPersonaje.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"

GUIPersonaje::GUIPersonaje(Personaje &personaje, bool parteIzquierda) : personaje(personaje), parteIzquierda(parteIzquierda){
    
    rectanguloVidaReal.setSize(TAMANO_BARRA_VIDA);
    rectanguloVidaReal.setFillColor(COLOR_BARRA_VIDA_REAL);

    rectanguloVidaAtrasada.setSize(TAMANO_BARRA_VIDA);
    rectanguloVidaAtrasada.setFillColor(COLOR_BARRA_VIDA_ATRASADA);

    rectanguloSuper.setSize(sf::Vector2f(0,TAMANO_BARRA_SUPER.y));
    rectanguloSuper.setFillColor(COLOR_BARRA_SUPER);

    contadorVidaAtrasado = MAX_PUNTOS_DE_VIDA;
    retrasoContadorVidaAtrasado = 0;

    spritePortrait.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+personaje.nombre+"/portrait.png"));

    spriteNombre.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+personaje.nombre+"/nombre.png"));

    if(parteIzquierda){
        rectanguloVidaReal.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_VIDA_IZQUIERDA);
        
        rectanguloVidaAtrasada.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_VIDA_IZQUIERDA);

        rectanguloSuper.setPosition(POSICION_GUI_IZQUIERDA+POSICION_BARRA_SUPER_IZQUIERDA);

        spritePortrait.setPosition(POSICION_GUI_IZQUIERDA+POSICION_PORTRAIT_IZQUIERDA);

        spriteNombre.setPosition(POSICION_GUI_IZQUIERDA+POSICION_NOMBRE_IZQUIERDA);

        spritePrincipalBase.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/base-izquierda-0.png"));
        spritePrincipalFrente.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/frente-izquierda.png"));
        spritePrincipalBase.setPosition(POSICION_GUI_IZQUIERDA);
        spritePrincipalFrente.setPosition(POSICION_GUI_IZQUIERDA);
    } else {
        sf::Vector2f posicionBarraVida(POSICION_GUI_IZQUIERDA+POSICION_BARRA_VIDA_IZQUIERDA);
        posicionBarraVida.x = VENTANA_ANCHURA-posicionBarraVida.x-rectanguloVidaReal.getSize().x;
        rectanguloVidaReal.setPosition(posicionBarraVida);
        rectanguloVidaAtrasada.setPosition(posicionBarraVida);

        sf::Vector2f posicionBarraSuper(POSICION_GUI_IZQUIERDA+POSICION_BARRA_SUPER_IZQUIERDA);
        posicionBarraSuper.x = VENTANA_ANCHURA-posicionBarraSuper.x-rectanguloSuper.getSize().x;
        rectanguloSuper.setPosition(posicionBarraSuper);

        sf::Vector2f posicionPortrait(POSICION_GUI_IZQUIERDA+POSICION_PORTRAIT_IZQUIERDA);
        posicionPortrait.x = VENTANA_ANCHURA-posicionPortrait.x-spritePortrait.getTextureRect().width;
        spritePortrait.setPosition(posicionPortrait);

        sf::Vector2f posicionNombre(POSICION_GUI_IZQUIERDA+POSICION_NOMBRE_IZQUIERDA);
        posicionNombre.x = VENTANA_ANCHURA-posicionNombre.x-spriteNombre.getTextureRect().width;
        spriteNombre.setPosition(posicionNombre);

        spritePrincipalBase.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/base-derecha-0.png"));
        spritePrincipalFrente.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/frente-derecha.png"));
        
        sf::Vector2f posicionGUI(POSICION_GUI_IZQUIERDA);
        posicionGUI.x = VENTANA_ANCHURA-posicionGUI.x-spritePrincipalBase.getTextureRect().width;
        spritePrincipalBase.setPosition(posicionGUI);
        spritePrincipalFrente.setPosition(posicionGUI);
    }
}

void GUIPersonaje::actualizar(){
    if(parteIzquierda){
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
    } else {
        
    }
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