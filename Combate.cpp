#include "Combate.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "ContenedorDePersonajes.hpp"
#include <iostream>
#include <list>

// Al usar initializer lists o como se diga en españolo me evito que se creen los
// personajes usando el constructor vacío para nada (porque se queja el g++ más que nada)
Combate::Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario) :
    personajeJugador1(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ1)),
    personajeJugador2(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ2)),
    GUIJugador1(personajeJugador1,true),
    GUIJugador2(personajeJugador2,false){

    personajeJugador1.setPosicion(VENTANA_ANCHURA/3,ALTURA_SUELO);
    personajeJugador2.setPosicion(2*VENTANA_ANCHURA/3,ALTURA_SUELO);
    //escenario = ContenedorDeEscenarios::unicaInstancia()->obtener(idEscenario);
}

void Combate::comenzar(){

    // Sacamos la ventana principal para que el nombre no sea tan largo
    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();

    // En esta lista hay efectos como objetos voladores o efectos de golpe
    std::list<std::shared_ptr<Animacion>> efectos;

    // El bucle principal realiza acciones en un orden muy específico para evitar problemas

    while(true){
        
        // Este es un momento especial en el que al menos uno de los personajes está preparando su súper
        // ataque, por lo que todo se pone oscuro y el tiempo se para por un momento
        if(personajeJugador1.getEstado() == EstadoPersonaje::PREPARANDO_SUPER || personajeJugador2.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){

            // Se actualizan solo los personajes preparando súper

            if(personajeJugador1.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){
                std::list<std::shared_ptr<Animacion>> nuevosEfectos;

                personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);

                for(const auto &efecto : nuevosEfectos){
                    efectos.push_back(efecto);
                }
            }

            if(personajeJugador2.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){
                std::list<std::shared_ptr<Animacion>> nuevosEfectos;

                personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);

                for(const auto &efecto : nuevosEfectos){
                    efectos.push_back(efecto);
                }
            }

            VentanaPrincipal::actualizar();

            ventana->clear(sf::Color(100,100,100));

            // Se dibuja todo como de costumbre (menos los personajes que están preparando súper)
            // ventana->draw(escenario);
            if(personajeJugador1.getEstado() != EstadoPersonaje::PREPARANDO_SUPER)
                ventana->draw(personajeJugador1);
            if(personajeJugador2.getEstado() != EstadoPersonaje::PREPARANDO_SUPER)
                ventana->draw(personajeJugador2);
            
            for(auto iter = efectos.begin(); iter != efectos.end(); iter++){
                ventana->draw(**iter);
            }

            // Se dibuja un rectángulo oscuro encima
            sf::RectangleShape rectanguloOscuro(sf::Vector2f(VENTANA_ANCHURA,VENTANA_ALTURA));
            rectanguloOscuro.setPosition(0,0);
            rectanguloOscuro.setFillColor(sf::Color(0,0,0,100));
            ventana->draw(rectanguloOscuro);

            // Se dibujan los personajes preparando súper
            if(personajeJugador1.getEstado() == EstadoPersonaje::PREPARANDO_SUPER)
                ventana->draw(personajeJugador1);
            if(personajeJugador2.getEstado() == EstadoPersonaje::PREPARANDO_SUPER)
                ventana->draw(personajeJugador2);

            ventana->display();
        } else {

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

            // SEGUNDO PASO: ACTUALIZAR PERSONAJES Y EFECTOS

            std::list<std::shared_ptr<Animacion>> nuevosEfectos;

            personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);
            personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);

            for(auto iter = efectos.begin(); iter != efectos.end();){
                if((*iter)->haTerminado()){
                    iter = efectos.erase(iter);
                } else {
                    // No hace falta actualizar el movimiento de los efectos así que esto se queda
                    // aquí de momento hasta que no se me ocurra algo mejor
                    sf::Vector2f movimiento;
                    (*iter)->actualizar(nuevosEfectos,movimiento);
                    iter++;
                }
            }

            GUIJugador1.actualizar();
            GUIJugador2.actualizar();

            VentanaPrincipal::actualizar();

            // TERCER PASO: COMPROBAR COLISIONES.

            efectos.push_back(personajeJugador2.getAnimaciones()[personajeJugador2.getEstado()]);

            personajeJugador1.comprobarColisiones(efectos,nuevosEfectos);

            efectos.pop_back();
            efectos.push_back(personajeJugador1.getAnimaciones()[personajeJugador1.getEstado()]);
            personajeJugador2.comprobarColisiones(efectos,nuevosEfectos);

            efectos.pop_back();

            for(auto iter = nuevosEfectos.begin(); iter != nuevosEfectos.end();iter++){
                efectos.push_back(*iter);
            }

            // CUARTO PASO: DIBUJAR EL ESCENARIO, LOS PERSONAJES Y LAS ANIMACIONES

            ventana->clear(sf::Color(100,100,100));
            // ventana->draw(escenario);
            ventana->draw(personajeJugador1);
            ventana->draw(personajeJugador2);

            for(auto iter = efectos.begin(); iter != efectos.end(); iter++){
                ventana->draw(**iter);
            }

            ventana->draw(GUIJugador1);
            ventana->draw(GUIJugador2);
            
            ventana->display();
        }
    }
}
