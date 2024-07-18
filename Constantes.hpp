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
const bool DEBUG = true;

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
const int VENTANA_ANCHURA = 300;
const int VENTANA_ALTURA = 200;

// FPS máximos de la ventana principal
const int VENTANA_FPS = 60;

// Nombre de la ventana principal
const std::string VENTANA_NOMBRE = "Érase un combate";

// Estilo de la ventana principal
const int VENTANA_ESTILO = sf::Style::Close;

// Vibración de la ventana para un ataque mediano
const int VIBRACION_ATAQUE_MEDIO = 7;

// Cada cuántos frames se actualiza la vibración de la ventana principal para que el efecto no
// sea tan violento a los ojos
const int VIBRACION_RETRASO = 1;

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

// Volumen máximo del reproductor de música
const float VOLUMEN_MAXIMO_MUSICA = 100.0;

/*
    CONSTANTES PARA LOS FICHEROS
*/

// Secuencia de caracteres que delimita los distintos elementos de un fichero
const std::string SECUENCIA_DELIMITADORA_FICHERO = "----";

// Secuencia de caracteres que indica el fin de un fichero
const std::string SECUENCIA_FIN_FICHERO = "####";

/*
    CONSTANTES PARA LAS ANIMACIONES
*/

// Valor máximo que debería tener el contador de parpadeo para hacer que una animación
// con gravedad se dé por terminada
const int MAX_CONTADOR_PARPADEO = 40;

// Cada cuántos frames las animaciones con gravedad pasan a ser visibles o invisibles para
// el efecto de parpadeo
const int DURACION_PARPADEO = 2;

// Máxima velocidad de giro de una partícula en cualquier dirección
const double MAX_VELOCIDAD_GIRO_PART = 10;

// Máxima velocidad en cualquier eje de una partícula pequeña
const int MAX_VELOCIDAD_PARTICULA_PEQUE = 3;

// Máxima velocidad en cualquier eje de una partícula mediana
const int MAX_VELOCIDAD_PARTICULA_MEDIA = 6;

// Máxima velocidad en cualquier eje de una partícula grande
const int MAX_VELOCIDAD_PARTICULA_GRANDE = 8;

// Cuántas partículas distintas hay de tipo pequeño
const int TIPO_PEQUE_CUANTAS_PARTICULAS = 3;

// Cuántas partículas distintas hay de tipo medio
const int TIPO_MEDIO_CUANTAS_PARTICULAS = 3;

// Cuántas partículas distintas hay de tipo pequeño
const int TIPO_GRANDE_CUANTAS_PARTICULAS = 3;

// El número de partículas que salen cuando te pegan con un ataque pequeño
const int NUM_PARTICULAS_GOLPEADO_PEQUE = 2;

// El número de partículas que salen cuando te pegan con un ataque medio
const int NUM_PARTICULAS_GOLPEADO_MEDIO = 4;

// El número de partículas que salen cuando te pegan con un ataque grande
const int NUM_PARTICULAS_GOLPEADO_GRANDE = 7;

// Cómo de desplazada está la animación del polvo en el eje X con respecto al centro del personaje
const int OFFSET_POLVO = 15;

/*
    CONSTANTES PARA LOS PERSONAJES
*/

// Origen de los personajes (usando la plantilla)
const sf::Vector2f PERSONAJE_PLANTILLA_ORIGEN = sf::Vector2f(64, 100);

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
const float ALTURA_SUELO = VENTANA_ALTURA - 10;

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

#endif // __CONSTANTES_CPP__
