#include "GUIPersonaje.hpp"
#include "Constantes.hpp"
#include "ContenedorDeRecursos.hpp"

GUIPersonaje::GUIPersonaje(Personaje &personaje) : personaje(personaje){
    spritePrincipalBase.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/base-izquierda-0.png"));
    spritePrincipalFrente.setTexture(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/gui/frente-izquierda.png"));
    spritePrincipalBase.setPosition(POSICION_X_GUI_IZQUIERDA,POSICION_Y_GUI_IZQUIERDA);
    spritePrincipalFrente.setPosition(POSICION_X_GUI_IZQUIERDA,POSICION_Y_GUI_IZQUIERDA);
}

void GUIPersonaje::actualizar(){

}

void GUIPersonaje::draw(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(spritePrincipalBase,states);
    target.draw(spritePrincipalFrente,states);
}