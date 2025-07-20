#include "Combate.hpp"
#include "VentanaPrincipal.hpp"
#include "ContenedorDePersonajes.hpp"

// Al usar initializer lists o como se diga en españolo me evito que se creen los
// personajes usando el constructor vacío para nada (porque se queja el g++ más que nada)
Combate::Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario) :
    personajeJugador1(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ1)),
    personajeJugador2(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ2)){
    //escenario = ContenedorDeEscenarios::unicaInstancia()->obtener(idEscenario);
}

void Combate::comenzar(){

    // Sacamos la ventana principal para que el nombre no sea tan largo
    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();
}
