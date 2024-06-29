#include "Combate.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "ContenedorDePersonajes.hpp"
#include <iostream>
#include <list>

// Al usar initializer lists o como se diga en espa�olo me evito que se creen los
// personajes usando el constructor vac�o para nada (porque se queja el g++ m�s que nada)
Combate::Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario) :
    personajeJugador1(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ1)),
    personajeJugador2(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ2)){

    personajeJugador1.setPosicion(VENTANA_ANCHURA/3,ALTURA_SUELO);
    personajeJugador2.setPosicion(2*VENTANA_ANCHURA/3,ALTURA_SUELO);
    //escenario = ContenedorDeEscenarios::unicaInstancia()->obtener(idEscenario);
}

void Combate::comenzar(){

    // Sacamos la ventana principal para que el nombre no sea tan largo
    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();

    // El bucle principal realiza acciones en un orden muy específico para evitar problemas

    while(true){

        // PRIMER PASO: RECIBIR ENTRADA DEL TECLADO O DE LOS MANDOS
        // En este paso se actualizan los valores booleanos de los personajes, que
        // indican si una acción está siendo realizada o no

        sf::Event evento;
        while(ventana->pollEvent(evento)){
            if(evento.type == sf::Event::Closed){
                ventana->close();
                exit(EXIT_SUCCESS);
            } else {
                std::pair<Jugador,Accion> par = GestorDeControles::unicaInstancia()->comprobarEvento(evento);

                if(par.first == Jugador::JUGADOR1){
                    if(evento.type == sf::Event::KeyPressed || evento.type == sf::Event::JoystickButtonPressed){
                        personajeJugador1.realizarAccion(par.second);
                    } else if(evento.type == sf::Event::KeyReleased || evento.type == sf::Event::JoystickButtonReleased){
                        personajeJugador1.detenerAccion(par.second);
                    }
                } else if(par.first == Jugador::JUGADOR2){
                    if(evento.type == sf::Event::KeyPressed ||
                       evento.type == sf::Event::JoystickButtonPressed) personajeJugador2.realizarAccion(par.second);
                    else if(evento.type == sf::Event::KeyReleased ||
                            evento.type == sf::Event::JoystickButtonReleased) personajeJugador2.detenerAccion(par.second);
                }
            }
        }

        // SEGUNDO PASO: ACTUALIZAR PERSONAJES

        personajeJugador1.actualizar(personajeJugador2.getPosicion());
        personajeJugador2.actualizar(personajeJugador1.getPosicion());

        // TERCER PASO: COMPROBAR COLISIONES.

        std::list<Animacion*> animaciones;
        animaciones.push_back(personajeJugador2.getAnimaciones()[personajeJugador2.getEstado()]);

        personajeJugador1.comprobarColisiones(animaciones,animaciones);

        animaciones.pop_back();
        animaciones.push_back(personajeJugador1.getAnimaciones()[personajeJugador1.getEstado()]);
        personajeJugador2.comprobarColisiones(animaciones,animaciones);

        // CUARTO PASO: DIBUJAR PERSONAJES
        // Después de actualizar las animaciones, están listas para ser dibujadas en pantalla

        ventana->clear(sf::Color(100,100,100));
        ventana->draw(personajeJugador1);
        ventana->draw(personajeJugador2);
        // ventana->draw(escenario);
        ventana->display();
    }
}
