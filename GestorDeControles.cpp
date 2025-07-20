#include "GestorDeControles.hpp"
#include "Constantes.hpp"

// La instancia es nula al principio
GestorDeControles * GestorDeControles::gestorDeControles = nullptr;

GestorDeControles * GestorDeControles::unicaInstancia()
{
    if(gestorDeControles == nullptr)
        gestorDeControles = new GestorDeControles;
    return gestorDeControles;
}

GestorDeControles::GestorDeControles()
{
    // Teclas, controles y acciones para la parte izquierda del teclado
    teclaAControlYAccion[sf::Keyboard::S] = std::pair<Control,Accion>(Control::TECLADO_IZQUIERDA,Accion::ABAJO);
    teclaAControlYAccion[sf::Keyboard::W] = std::pair<Control,Accion>(Control::TECLADO_IZQUIERDA,Accion::ARRIBA);
    teclaAControlYAccion[sf::Keyboard::A] = std::pair<Control,Accion>(Control::TECLADO_IZQUIERDA,Accion::IZQUIERDA);
    teclaAControlYAccion[sf::Keyboard::D] = std::pair<Control,Accion>(Control::TECLADO_IZQUIERDA,Accion::DERECHA);
    teclaAControlYAccion[sf::Keyboard::LShift] = std::pair<Control,Accion>(Control::TECLADO_IZQUIERDA,Accion::ATACAR);

    // Teclas, controles y acciones para la parte izquierda del teclado
    teclaAControlYAccion[sf::Keyboard::K] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ABAJO);
    teclaAControlYAccion[sf::Keyboard::I] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ARRIBA);
    teclaAControlYAccion[sf::Keyboard::J] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::IZQUIERDA);
    teclaAControlYAccion[sf::Keyboard::L] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::DERECHA);
    teclaAControlYAccion[sf::Keyboard::Space] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ATACAR);

    // Al principio los controles no est�n asociados a nadie
    for(int i=0;i<NUMERO_CONTROLES;i++){
        controlAJugador[static_cast<Control>(i)] = Jugador::NADIE;
    }

    // Bueno s�, hay dos que s� est�n asociados al principio
    controlAJugador[Control::TECLADO_IZQUIERDA] = Jugador::JUGADOR1;
    controlAJugador[Control::TECLADO_DERECHA] = Jugador::JUGADOR2;
}

bool GestorDeControles::estaLibre(Control c){
    return controlAJugador[c] == Jugador::NADIE;
}

bool GestorDeControles::conectarMando(Jugador j, Control c){

    // Si no es un mando, nos vamos directamente
    if(c == Control::TECLADO_DERECHA || c == Control::TECLADO_IZQUIERDA)
        return false;

    // Si ya est� pillado, tambi�n
    if(!estaLibre(c)) return false;

    // Buscamos el control que sea que est� usando el jugador y lo deshabilitamos
    // (Gracias a las maravillas de C y C++ puedo evitar usar llaves aqu�)
    for(int i=0;i<NUMERO_CONTROLES;i++)
        if(controlAJugador[static_cast<Control>(i)] == j)
            controlAJugador[static_cast<Control>(i)] = Jugador::NADIE;

    // Por �ltimo, asignamos el control y ya est�
    controlAJugador[c] = j;

    return true;
}

std::pair<Jugador,Accion> GestorDeControles::comprobarEvento(sf::Event evento)
{
    // Este es el par que va a ser devuelto (empieza vac�o)
    std::pair<Jugador,Accion> pair(Jugador::NADIE,Accion::NADA);

    if(evento.type == sf::Event::JoystickButtonPressed || evento.type == sf::Event::JoystickButtonReleased){
        // Alguien ha pulsado un bot�n de mando (el bot�n da igual, todos
        // hacen lo mismo). Se le suma 2 al numerito del control porque los dos
        // primeros controles son la parte izquierda del teclado y la parte derecha,
        // por lo que el control 3 es el mando 0 y as� sucesivamente
        Control control = static_cast<Control>(evento.joystickButton.joystickId+2);

        // Si el control es de alguien, se actualiza el par
        pair.first = controlAJugador[control];
        if(pair.first != Jugador::NADIE)
            pair.second = Accion::ATACAR;

    } else if (evento.type == sf::Event::JoystickMoved){
        // Alguien ha movido un joystick

        Control control = static_cast<Control>(evento.joystickMove.joystickId+2);

        // Se saca el jugador correspondiente al mando. Si hay jugador,
        // se hacen cosas
        pair.first = controlAJugador[control];
        if(pair.first != Jugador::NADIE){
            // Dependiendo del eje, se decide hacia d�nde se mueve
            switch(evento.joystickMove.axis){
                // PovX, X y R son los ejes X de tres posibles entradas
                // PovX es la cruceta, X es el joystick izquierdo y R el joystick derecho
                case sf::Joystick::Axis::PovX:
                case sf::Joystick::Axis::X:
                case sf::Joystick::Axis::R:
                    if(evento.joystickMove.position > UMBRAL_JOYSTICK)
                        pair.second = Accion::DERECHA;
                    else if(evento.joystickMove.position < -UMBRAL_JOYSTICK)
                        pair.second = Accion::IZQUIERDA;
                    break;

                // PovY, Y y U son los ejes Y de tres posibles entradas
                // PovY es la cruceta, Y es el joystick izquierdo y U el joystick derecho
                case sf::Joystick::Axis::PovY:
                case sf::Joystick::Axis::Y:
                case sf::Joystick::Axis::U:
                    if(evento.joystickMove.position > UMBRAL_JOYSTICK)
                        pair.second = Accion::ARRIBA;
                    else if(evento.joystickMove.position < -UMBRAL_JOYSTICK)
                        pair.second = Accion::ABAJO;
                    break;
                default:
                    break;
            }
        }
    } else if (evento.type == sf::Event::KeyPressed || evento.type == sf::Event::KeyReleased){
        // Alguien ha pulsado una tecla

        // Si es la tecla de salida tiene soluci�n f�cil
        if(evento.key.code == TECLA_SALIDA)
            pair.second = Accion::ESCAPE;
        else {
            // Si es otra tecla, hay que ver si es una de las que nos interesa
            if(teclaAControlYAccion.count(evento.key.code)){
                // Si es una tecla que tenemos registrada, se comprueba su control y su acci�n
                Control c = teclaAControlYAccion[evento.key.code].first;
                Accion a = teclaAControlYAccion[evento.key.code].second;

                // Se asigna el personaje y la acci�n
                pair.first = controlAJugador[c];
                pair.second = a;
                // Si el personaje es NADIE es porque nadie tiene ese control, as�
                // que todo lo que hemos hecho ha sido perder el tiempo
                if(pair.first == Jugador::NADIE){
                    pair.second = Accion::NADA;
                }
            }
        }
    }

    // Despu�s de este pifostio devolvemos el par
    return pair;
}
