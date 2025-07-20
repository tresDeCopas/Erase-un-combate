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

// Indica si se quiere activar el modo debug (mostrar hitboxes en pantalla y acta vecinal en la consola)
const bool DEBUG = false;

// Color para las hitboxes que hacen da�o
const sf::Color HITBOX_ATAQUE_COLOR = sf::Color::Red;

// Color para las hitboxes que no hacen da�o
const sf::Color HITBOX_NO_ATAQUE_COLOR = sf::Color::Blue;

/*
    CONSTANTES PARA LA BIT�CORA
*/

const std::string BITACORA_RUTA = "ActaVecinal.log";

const int MAXIMA_LONGITUD_TEXTURA = 1024;

/*
    CONSTANTES PARA LA VENTANA
*/

// Anchura y altura de la ventana principal
const int VENTANA_ANCHURA = 400;
const int VENTANA_ALTURA = 300;

// FPS máximos de la ventana principal
const int VENTANA_FPS = 60;

// Nombre de la ventana principal
const std::string VENTANA_NOMBRE = "Érase un combate";

// Estilo de la ventana principal
const int VENTANA_ESTILO = sf::Style::Close;

/*
    CONSTANTES PARA LOS CONTROLES
*/

// N�mero total de controles posibles (dos partes del teclado y ocho mandos)
const int NUMERO_CONTROLES = 10;

// El movimiento mínimo que se tiene que hacer con un joystick para considerar la
// entrada válida (esto evita que con mover el joystick 0.00001 milimetros ya est�
// moviéndose el personaje)
const double UMBRAL_JOYSTICK = 0.3;

// Tecla para salir del juego
const sf::Keyboard::Key TECLA_SALIDA = sf::Keyboard::Key::Escape;

/*
    CONSTANTES PARA EL SONIDO
*/

// Volumen m�ximo del reproductor de m�sica
const float VOLUMEN_MAXIMO_MUSICA = 100.0;

/*
    CONSTANTES PARA LOS FICHEROS
*/

// Secuencia de caracteres que delimita los distintos elementos de un fichero
const std::string SECUENCIA_DELIMITADORA_FICHERO = "----";

// Secuencia de caracteres que indica el fin de un fichero
const std::string SECUENCIA_FIN_FICHERO = "####";

/*
    CONSTANTES PARA LOS PERSONAJES
*/

// Origen de los personajes (usando la plantilla)
const sf::Vector2f PERSONAJE_PLANTILLA_ORIGEN = sf::Vector2f(64,100);

// Gravedad del escenario
const float GRAVEDAD = 0.3;

// Puntos de vida m�ximos de un personaje
const int MAX_PUNTOS_DE_VIDA = 100;

// Velocidad m�xima en el eje X a la que se puede mover un personaje
const float VELOCIDAD_ANDAR_MAX = 2.5;

// Aumento de velocidad cada frame al andar
const float VELOCIDAD_ANDAR_AUMENTO = 0.3;

// Velocidad que se consigue en el eje Y al saltar
const float VELOCIDAD_SALTO = -7;

// Posici�n en el eje Y del suelo
const float ALTURA_SUELO = VENTANA_ALTURA-20;

// Impulso inicial al recibir un golpe pequeño
const float IMPULSO_GOLPE_PEQUE = 1;

// Impulso inicial al recibir un golpe mediano
const float IMPULSO_GOLPE_MEDIO = 5;

// Máximo daño que puede hacer un ataque pequeño
const int MAX_ATAQUE_PEQUE = 3;

// Máximo daño que puede hacer un ataque medio
const int MAX_ATAQUE_MEDIO = 6;

/*
    CONSTANTES AUXILIARES PARA COSAS DE C++
*/

// Si dos floats se diferencian en menos que este n�mero, se consideran iguales
const float UMBRAL_FLOAT = 0.0001;

#endif // __CONSTANTES_HPP__
