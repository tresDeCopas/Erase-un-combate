#ifndef __CONSTANTES_HPP__
#define __CONSTANTES_HPP__

#include <string>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

/*
    Este fichero contiene todas las constantes del programa, como su
    propio nombre indica vamos
*/

/*
    CONSTANTES PARA EL DEBUG
*/

// Indica si se quieren mostrar las hitboxes
const bool HITBOX_MOSTRAR = true;

// Color para las hitboxes que hacen daño
const sf::Color HITBOX_ATAQUE_COLOR = sf::Color::Red;

// Color para las hitboxes que no hacen daño
const sf::Color HITBOX_NO_ATAQUE_COLOR = sf::Color::Blue;

/*
    CONSTANTES PARA LA BITÁCORA
*/

const std::string BITACORA_RUTA = "ActaVecinal.log";

const int MAXIMA_LONGITUD_TEXTURA = 1024;

/*
    CONSTANTES PARA LA VENTANA
*/

// Anchura y altura de la ventana principal
const int VENTANA_ANCHURA = 300;
const int VENTANA_ALTURA = 200;

// FPS máximos de la ventana principal
const int VENTANA_FPS = 60;

// Nombre de la ventana principal
const std::string VENTANA_NOMBRE = "Érase un combate";

// Estilo de la ventana principal
const int VENTANA_ESTILO = sf::Style::Close;

/*
    CONSTANTES PARA LOS CONTROLES
*/

// Número total de controles posibles (dos partes del teclado y ocho mandos)
const int NUMERO_CONTROLES = 10;

// El movimiento mínimo que se tiene que hacer con un joystick para considerar la
// entrada válida (esto evita que con mover el joystick 0.00001 milimetros ya esté
// moviéndose el personaje)
const double UMBRAL_JOYSTICK = 0.3;

// Tecla para salir del juego
const sf::Keyboard::Key TECLA_SALIDA = sf::Keyboard::Key::Escape;

/*
    CONSTANTES PARA EL SONIDO
*/

// Volumen máximo del reproductor de música
const float VOLUMEN_MAXIMO_MUSICA = 100.0;

#endif // __CONSTANTES_HPP__
