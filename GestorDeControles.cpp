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
    teclaAControlYAccion[sf::Keyboard::I] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ABAJO);
    teclaAControlYAccion[sf::Keyboard::K] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ARRIBA);
    teclaAControlYAccion[sf::Keyboard::J] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::IZQUIERDA);
    teclaAControlYAccion[sf::Keyboard::L] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::DERECHA);
    teclaAControlYAccion[sf::Keyboard::Space] = std::pair<Control,Accion>(Control::TECLADO_DERECHA,Accion::ATACAR);

    // Al principio los controles no están asociados a nadie
    for(int i=0;i<NUMERO_CONTROLES;i++){
        controlToCharacter[static_cast<Control>(i)] = CharName::NONE;
    }
}

bool GestorDeControles::isAvailable(Control c){
    return controlToCharacter[c] == CharName::NONE;
}

bool GestorDeControles::connectJoystick(CharName character, Control joystick){

    // If a joystick button is pressed when the controls window is showing, then
    // the character will be controlled by the joystick and not the keyboard

    if(!isAvailable(joystick)) return false;

    // Unassign the character to its current control
    if(controlToCharacter[Control::KEYBOARD_LEFT] == character){
        controlToCharacter[Control::KEYBOARD_LEFT] = CharName::NONE;
    } else if(controlToCharacter[Control::KEYBOARD_RIGHT] == character){
        controlToCharacter[Control::KEYBOARD_RIGHT] = CharName::NONE;
    }

    controlToCharacter[joystick] = character;
    return true;
}

std::pair<CharName,Accion> GestorDeControles::checkEvent(sf::Event event)
{
    // This is the pair of CharName and Accion that will be returned
    std::pair<CharName,Accion> pair(CharName::NONE,Accion::NONE);

    if(event.type == sf::Event::JoystickButtonPressed){
        // Someone pressed a key on a joystick, let's find who

        Control control = static_cast<Control>(event.joystickButton.joystickId+2);

        pair.first = controlToCharacter[control];
        if(pair.first != CharName::NONE)
            pair.second = Accion::INTERACT;

    } else if (event.type == sf::Event::JoystickMoved){
        // Someone moved a joystick, let's find who

        Control control = static_cast<Control>(event.joystickMove.joystickId+2);

        pair.first = controlToCharacter[control];
        if(pair.first == CharName::NONE)
            pair.second = Accion::NONE;
        else{
            // Depending on the axis, do something
            switch(event.joystickMove.axis){
                case sf::Joystick::Axis::PovX:
                case sf::Joystick::Axis::X:
                case sf::Joystick::Axis::R:
                    if(event.joystickMove.position > JOYSTICK_AXIS_THRESHOLD)
                        pair.second = Accion::RIGHT;
                    else if(event.joystickMove.position < -JOYSTICK_AXIS_THRESHOLD)
                        pair.second = Accion::LEFT;
                    break;
                case sf::Joystick::Axis::PovY:
                case sf::Joystick::Axis::Y:
                case sf::Joystick::Axis::U:
                    if(event.joystickMove.position > JOYSTICK_AXIS_THRESHOLD)
                        pair.second = Accion::UP;
                    else if(event.joystickMove.position < -JOYSTICK_AXIS_THRESHOLD)
                        pair.second = Accion::DOWN;
                    break;
                default:
                    break;
            }
        }
    } else if (event.type == sf::Event::KeyPressed){
        // Someone pressed a key

        // If it's the exit key, return it immediately
        if(event.key.code == EXIT_KEY)
            pair.second = Accion::EXIT;
        else {
            // If it's another key, first check if it's a valid key
            if(teclaAControlYAccion.count(event.key.code)){
                // If it is, get the control and the action
                Control c = teclaAControlYAccion[event.key.code].first;
                Accion ka = teclaAControlYAccion[event.key.code].second;

                // Now, assign the CharName and the Accion
                pair.first = controlToCharacter[c];
                pair.second = ka;
                // Also check if the character is NONE, in which case the action
                // is also NONE just in case
                if(pair.first == CharName::NONE){
                    pair.second = Accion::NONE;
                }
            }
        }
    }

    return pair;
}

// Returns true if the character has a control assigned by the end of the function (already had one, or didn't
// have un but got a new one). Returns false if the function couldn't assign a control (both parts of the keyboard
// are taken and the player needs to connect a controller)
bool GestorDeControles::assignControl(CharName character)
{
    // Is that character already assigned to a control?
    for(int i=0;i<NUM_CONTROLS;i++){
        if(controlToCharacter[static_cast<Control>(i)] == character)
            return true;
    }

    // If you are still here, let's try to assign the character to a keyboard part
    if(controlToCharacter[Control::KEYBOARD_LEFT] == CharName::NONE){
        controlToCharacter[Control::KEYBOARD_LEFT] = character;
        return true;
    } else if(controlToCharacter[Control::KEYBOARD_RIGHT] == CharName::NONE){
        controlToCharacter[Control::KEYBOARD_RIGHT] = character;
        return true;
    }

    // If you reach this point, you have to connect a controller (sorry heheh)
    return false;
}
