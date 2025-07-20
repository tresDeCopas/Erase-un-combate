#include "Combate.hpp"
#include "VentanaPrincipal.hpp"
#include "ContenedorDePersonajes.hpp"

Combate::Combate(IDPersonaje idPersonajeJ1, IDPersonaje idPersonajeJ2, IDEscenario idEscenario){
    personajeJugador1 = ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(idPersonajeJ1);
    personajeJugador2 = ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(idPersonajeJ2);
    //escenario = ContenedorDeEscenarios::unicaInstancia()->obtener(idEscenario);
}

Combate::~Combate(){
    delete personajeJugador1;
    delete personajeJugador2;
}

void Combate::comenzar(){

    sf::RenderWindow * ventanaPrincipal = VentanaPrincipal::unicaInstancia();
}
