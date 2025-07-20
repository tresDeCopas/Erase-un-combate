#include "Combate.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeEfectos.hpp"
#include "ReproductorDeMusica.hpp"
#include <iostream>
#include <list>

// Al usar initializer lists o como se diga en españolo me evito que se creen los
// personajes usando el constructor vacío para nada (porque se queja el g++ más que nada)
Combate::Combate(std::string nombrePersonajeJ1, std::string nombrePersonajeJ2, std::string nombreEscenario) :
    personajeJugador1(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ1)),
    personajeJugador2(ContenedorDePersonajes::unicaInstancia()->obtenerPersonaje(nombrePersonajeJ2)),
    GUIJugador1(personajeJugador1,true), GUIJugador2(personajeJugador2,false),
    escenario(ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/escenarios/"+nombreEscenario+"/fondo.png"),ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/escenarios/"+nombreEscenario+"/frente.png")),
    cartelTodoListo(ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("cartel-todo-listo")),
    cartelAPelear(ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("cartel-a-pelear")){

    rectanguloOscuro.setPosition(0,0);
    rectanguloOscuro.setSize(sf::Vector2f(VENTANA_ANCHURA,VENTANA_ALTURA));
    rectanguloOscuro.setOutlineThickness(0);
    rectanguloOscuro.setFillColor(sf::Color::Black);

    personajeJugador1.setPosicion(VENTANA_ANCHURA/3,ALTURA_SUELO);
    personajeJugador2.setPosicion(2*VENTANA_ANCHURA/3,ALTURA_SUELO);

    cartelTodoListo->setPosicion(POSICION_CARTELES);
    cartelAPelear->setPosicion(POSICION_CARTELES);
}

void Combate::resetear(){
    // Los carteles se resetean
    cartelTodoListo->resetear();
    cartelAPelear->resetear();

    // Los personajes vuelven a su posición
    personajeJugador1.setPosicion(VENTANA_ANCHURA/3,ALTURA_SUELO);
    personajeJugador2.setPosicion(2*VENTANA_ANCHURA/3,ALTURA_SUELO);

    // Los personajes se curan y se vacía su medidor se súper
    personajeJugador1.setPuntosDeVida(MAX_PUNTOS_DE_VIDA);
    personajeJugador1.setMedidorSuper(0);
    personajeJugador2.setPuntosDeVida(MAX_PUNTOS_DE_VIDA);
    personajeJugador2.setMedidorSuper(0);

    // Los personajes pasan al estado quieto
    personajeJugador1.cambiarEstado(EstadoPersonaje::QUIETO);
    personajeJugador2.cambiarEstado(EstadoPersonaje::QUIETO);

    // Se coloca el escenario en el centro
    escenario.resetear();
}

void Combate::comenzar(){

    // Sacamos la ventana principal para que el nombre no sea tan largo
    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();

    // En esta lista hay efectos como objetos voladores o efectos de golpe
    std::list<std::shared_ptr<Animacion>> efectos;

    // Este bucle contiene varias rondas dentro y podría ser más bonito y compacto pero prefiero
    // repetir código porque virgen santisima que por culo sería compactarlo todo
    while(true){
        
        // Se reproduce una canción de combate
        ReproductorDeMusica::unicaInstancia()->reproducirCancionCombate();

        // Se resetean los carteles, los personajes y el escenario
        resetear();

        // El bucle de cada ronda realiza acciones en un orden muy específico para evitar problemas

        while(personajeJugador1.getPuntosDeVida() > 0 && personajeJugador2.getPuntosDeVida() > 0){

            // Se aclara el rectángulo que cubre el combate
            if(rectanguloOscuro.getFillColor().a > 0){
                sf::Color nuevoColor(rectanguloOscuro.getFillColor());
                // Se le baja 10 a la transparencia hasta que sea totalmente transparente
                // (con cuidado para que el contador no se dé la vuelta)
                nuevoColor.a = nuevoColor.a < 10 ? 0 : nuevoColor.a-10;
                rectanguloOscuro.setFillColor(nuevoColor);
            }
            
            // Este es un momento especial en el que al menos uno de los personajes está preparando su súper
            // ataque, por lo que todo se pone oscuro y el tiempo se para por un momento
            if(personajeJugador1.getEstado() == EstadoPersonaje::PREPARANDO_SUPER || personajeJugador2.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){

                // Se actualizan solo los personajes preparando súper

                if(personajeJugador1.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){
                    std::list<std::shared_ptr<Animacion>> nuevosEfectos;

                    personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);

                    for(const std::shared_ptr<Animacion> &efecto : nuevosEfectos){
                        efectos.push_back(efecto);
                    }
                }

                if(personajeJugador2.getEstado() == EstadoPersonaje::PREPARANDO_SUPER){
                    std::list<std::shared_ptr<Animacion>> nuevosEfectos;

                    personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);

                    for(const std::shared_ptr<Animacion> &efecto : nuevosEfectos){
                        efectos.push_back(efecto);
                    }
                }
                
                // No se actualiza el escenario para dar el efecto de que se ha parado el tiempo

                VentanaPrincipal::actualizar();
                GUIJugador1.actualizar();
                GUIJugador2.actualizar();

                ventana->clear(sf::Color(100,100,120));

                // Se dibuja todo como de costumbre (menos los personajes que están preparando súper)
                escenario.dibujarFondo(*ventana,sf::RenderStates::Default);

                if(personajeJugador1.getEstado() != EstadoPersonaje::PREPARANDO_SUPER)
                    ventana->draw(personajeJugador1);
                if(personajeJugador2.getEstado() != EstadoPersonaje::PREPARANDO_SUPER)
                    ventana->draw(personajeJugador2);
                
                for(std::list<std::shared_ptr<Animacion>>::iterator iter = efectos.begin(); iter != efectos.end(); iter++){
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

                escenario.dibujarFrente(*ventana,sf::RenderStates::Default);

                ventana->draw(GUIJugador1);
                ventana->draw(GUIJugador2);

                ventana->display();
            } else {

                // PRIMER PASO: RECIBIR ENTRADA DEL TECLADO O DE LOS MANDOS
                // En este paso se actualizan los valores booleanos de los personajes, que
                // indican si una acción está siendo realizada o no. Se comprueba si se han terminado
                // de mostrar los dos carteles del principio del combate y entonces se puede comenzar a
                // jugar (en realidad el segundo cartel, el de "¡A pelear!" deja de bloquear el movimiento
                // de los personajes cuando se agranda a su máximo tamaño)

                if(!cartelTodoListo->haTerminado()){
                    cartelTodoListo->actualizar(efectos);
                } else if(!cartelAPelear->haTerminado()){
                    cartelAPelear->actualizar(efectos);
                }

                sf::Event evento;
                while(ventana->pollEvent(evento)){
                    if(evento.type == sf::Event::Closed){
                        ventana->close();
                        exit(EXIT_SUCCESS);
                    } else {
                        std::pair<Jugador,Accion> par = GestorDeControles::unicaInstancia()->comprobarEvento(evento);

                        Personaje& personajeElegido = par.first == Jugador::JUGADOR1 ? personajeJugador1 : personajeJugador2;

                        if((dynamic_cast<AnimacionAgrandable*>(cartelAPelear.get()))->haTerminadoDeAgrandarse()){
                            if(evento.type == sf::Event::KeyPressed || evento.type == sf::Event::JoystickButtonPressed || (evento.type == sf::Event::JoystickMoved && std::abs(evento.joystickMove.position) > UMBRAL_JOYSTICK)){
                                personajeElegido.realizarAccion(par.second);
                            } else if(evento.type == sf::Event::KeyReleased || evento.type == sf::Event::JoystickButtonReleased || (evento.type == sf::Event::JoystickMoved && std::abs(evento.joystickMove.position) < UMBRAL_JOYSTICK)){
                                personajeElegido.detenerAccion(par.second);
                            }
                        }

                    }
                }

                // SEGUNDO PASO: ACTUALIZAR PERSONAJES, EFECTOS, GUIS, ESCENARIO Y VENTANA

                std::list<std::shared_ptr<Animacion>> nuevosEfectos;

                if(primerJugadorParaActualizar == Jugador::JUGADOR1){
                    personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);
                    personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);
                } else {
                    personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);
                    personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);
                }

                for(auto iter = efectos.begin(); iter != efectos.end();){
                    if((*iter)->haTerminado()){
                        iter = efectos.erase(iter);
                    } else {
                        (*iter)->actualizar(nuevosEfectos);
                        iter++;
                    }
                }

                GUIJugador1.actualizar();
                GUIJugador2.actualizar();

                escenario.actualizar(personajeJugador1,personajeJugador2,efectos);

                VentanaPrincipal::actualizar();

                // TERCER PASO: COMPROBAR COLISIONES.

                if(primerJugadorParaActualizar == Jugador::JUGADOR1){
                    efectos.push_back(personajeJugador2.getAnimacionSegunEstado(personajeJugador2.getEstado()));

                    personajeJugador1.comprobarColisiones(efectos,nuevosEfectos);

                    efectos.pop_back();

                    efectos.push_back(personajeJugador1.getAnimacionSegunEstado(personajeJugador1.getEstado()));
                    personajeJugador2.comprobarColisiones(efectos,nuevosEfectos);

                    efectos.pop_back();
                } else {
                    efectos.push_back(personajeJugador1.getAnimacionSegunEstado(personajeJugador1.getEstado()));
                    personajeJugador2.comprobarColisiones(efectos,nuevosEfectos);

                    efectos.pop_back();

                    efectos.push_back(personajeJugador2.getAnimacionSegunEstado(personajeJugador2.getEstado()));

                    personajeJugador1.comprobarColisiones(efectos,nuevosEfectos);

                    efectos.pop_back();
                }

                for(auto iter = nuevosEfectos.begin(); iter != nuevosEfectos.end();iter++){
                    efectos.push_back(*iter);
                }

                // CUARTO PASO: DIBUJAR EL ESCENARIO, LOS PERSONAJES Y LAS ANIMACIONES

                ventana->clear(sf::Color(100,100,120));
                escenario.dibujarFondo(*ventana,sf::RenderStates::Default);
                ventana->draw(personajeJugador1);
                ventana->draw(personajeJugador2);

                for(auto iter = efectos.begin(); iter != efectos.end(); iter++){
                    ventana->draw(**iter);
                }

                escenario.dibujarFrente(*ventana,sf::RenderStates::Default);

                ventana->draw(GUIJugador1);
                ventana->draw(GUIJugador2);

                if(!cartelTodoListo->haTerminado()){
                    ventana->draw(*cartelTodoListo);
                } else if (!cartelAPelear->haTerminado()){
                    ventana->draw(*cartelAPelear);
                }

                // Lo último que se dibuja es el rectángulo que cubre el combate
                ventana->draw(rectanguloOscuro);
                
                ventana->display();

                // Ahora que ha terminado el frame le damos la vuelta al jugador que será
                // actualizado primero en el siguiente frame
                if(primerJugadorParaActualizar == Jugador::JUGADOR1){
                    primerJugadorParaActualizar = Jugador::JUGADOR2;
                } else {
                    primerJugadorParaActualizar = Jugador::JUGADOR1;
                }
            }
        }

        // Se termina el bucle de la ronda al ser uno de los luchadores derribado. Se detiene
        // la reproducción de la canción de combate
        ReproductorDeMusica::unicaInstancia()->detener();

        // Se resetean todas las acciones para que los personajes se estén quietos
        personajeJugador1.detenerAccion(Accion::ARRIBA);
        personajeJugador1.detenerAccion(Accion::ABAJO);
        personajeJugador1.detenerAccion(Accion::IZQUIERDA);
        personajeJugador1.detenerAccion(Accion::DERECHA);
        personajeJugador1.detenerAccion(Accion::ATACAR);

        personajeJugador2.detenerAccion(Accion::ARRIBA);
        personajeJugador2.detenerAccion(Accion::ABAJO);
        personajeJugador2.detenerAccion(Accion::IZQUIERDA);
        personajeJugador2.detenerAccion(Accion::DERECHA);
        personajeJugador2.detenerAccion(Accion::ATACAR);

        // Se encuentra al jugador que ha ganado (no sé si puede haber empates)
        Personaje& ganador = personajeJugador1.getPuntosDeVida() > 0 ? personajeJugador1 : personajeJugador2;

        // Este contador disminuye en 1 cada frame y cuando llega a 0 se le indica al ganador que celebre
        int contadorCelebracion = MAX_CONTADOR_CELEBRACION;

        // El bucle termina cuando el rectángulo que cubre la pantalla se oscurezca por completo (esto ocurre después de que el personaje ganador
        // haya celebrado su victoria y se haya terminado de reproducir la canción de fin de ronda)
        while(rectanguloOscuro.getFillColor().a != 255){

            // PRIMER PASO: solo se recibe entrada si se cierra la ventana

            sf::Event evento;
            while(ventana->pollEvent(evento)){
                if(evento.type == sf::Event::Closed){
                    ventana->close();
                    exit(EXIT_SUCCESS);
                }
            }

            // SEGUNDO PASO: ACTUALIZAR PERSONAJES Y EFECTOS

            std::list<std::shared_ptr<Animacion>> nuevosEfectos;

            personajeJugador1.actualizar(personajeJugador2.getPosicion(),nuevosEfectos);
            personajeJugador2.actualizar(personajeJugador1.getPosicion(),nuevosEfectos);

            for(auto iter = nuevosEfectos.begin(); iter != nuevosEfectos.end();iter++){
                efectos.push_back(*iter);
            }

            for(auto iter = efectos.begin(); iter != efectos.end();){
                if((*iter)->haTerminado()){
                    iter = efectos.erase(iter);
                } else {
                    (*iter)->actualizar(nuevosEfectos);
                    iter++;
                }
            }

            GUIJugador1.actualizar();
            GUIJugador2.actualizar();

            escenario.actualizar(personajeJugador1,personajeJugador2,efectos);

            VentanaPrincipal::actualizar();

            // TERCER PASO: no se comprueban colisiones porque se supone que ya se ha terminado esta ronda. En su lugar, se
            // comprueba si el personaje puede celebrar y se le dice que celebre

            // Si el contador de celebración aún no ha llegado a cero, se disminuye
            if(contadorCelebracion > 0){
                contadorCelebracion--;
            } 
            // Si ya ha llegado a cero, se le dice al personaje que celebre y se reproduce la canción de fin de ronda
            else if (ganador.getEstado() != EstadoPersonaje::CELEBRANDO){
                ganador.cambiarEstado(EstadoPersonaje::CELEBRANDO);
                ReproductorDeMusica::unicaInstancia()->reproducirCancionFinRonda();
            }
            // Si ya se le ha dicho que celebre, se oscurece el rectángulo si ha terminado de celebrar
            else if(ganador.getAnimacionSegunEstado(EstadoPersonaje::CELEBRANDO)->haTerminado() && !ReproductorDeMusica::unicaInstancia()->estaReproduciendo()) {
                sf::Color nuevoColor(rectanguloOscuro.getFillColor());
                nuevoColor.a+=5;
                rectanguloOscuro.setFillColor(nuevoColor);
            }

            // CUARTO PASO: DIBUJAR EL ESCENARIO, LOS PERSONAJES Y LAS ANIMACIONES

            ventana->clear(sf::Color(100,100,100));
            escenario.dibujarFondo(*ventana,sf::RenderStates::Default);
            ventana->draw(personajeJugador1);
            ventana->draw(personajeJugador2);

            for(auto iter = efectos.begin(); iter != efectos.end(); iter++){
                ventana->draw(**iter);
            }

            escenario.dibujarFrente(*ventana,sf::RenderStates::Default);

            ventana->draw(GUIJugador1);
            ventana->draw(GUIJugador2);

            ventana->draw(rectanguloOscuro);
            
            ventana->display();
        }
    }
}
