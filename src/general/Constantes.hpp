#pragma once

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

// Color para las hitboxes que hacen daño
constexpr sf::Color HITBOX_ATAQUE_COLOR = sf::Color::Red;

// Color para las hitboxes que no hacen daño
constexpr sf::Color HITBOX_NO_ATAQUE_COLOR = sf::Color::Blue;

/*
    CONSTANTES PARA LA BITÁCORA
*/

const std::string BITACORA_RUTA = "ActaVecinal.log";

constexpr int MAXIMA_LONGITUD_TEXTURA = 1024;

/*
    CONSTANTES PARA LA VENTANA
*/

// Anchura y altura de la ventana principal
constexpr int VENTANA_ANCHURA = 300;
constexpr int VENTANA_ALTURA = 200;

// Numero de fotogramas por segundo que se establece por defecto
constexpr int NUMERO_FPS_INICIAL = 60;

// Nombre de la ventana principal
const std::string VENTANA_NOMBRE = "Erase un combate";

// Estilo de la ventana principal
constexpr int VENTANA_ESTILO = sf::Style::Close;

// Vibración de la ventana para un ataque mediano
constexpr int VIBRACION_ATAQUE_MEDIO = 7;

// Vibración de la ventana para un ataque súper
constexpr int VIBRACION_ATAQUE_SUPER = 30;

// Cada cuántos fotogramas se actualiza la vibración de la ventana principal para que el efecto no
// sea tan violento a los ojos
constexpr int VIBRACION_RETRASO = 1;

/*
    CONSTANTES PARA LOS CONTROLES
*/

// Número total de controles posibles (dos partes del teclado y ocho mandos)
constexpr int NUMERO_CONTROLES = 10;

// El movimiento mínimo que se tiene que hacer con un joystick para considerar la
// entrada válida (esto evita que con mover el joystick 0.00001 milimetros ya está
// moviéndose el personaje). Hay que tener en cuenta que el máximo al que puede llegar
// un joystick sin drift ni defectos es 100
constexpr double UMBRAL_JOYSTICK = 50;

// Código asignado al botón de mando usado para atacar
constexpr unsigned int MANDO_BOTON_ATACAR = 0;

// Código asignado al botón de mando usado para saltar
constexpr unsigned int MANDO_BOTON_SALTAR = 2;

// Tecla para salir del juego
constexpr sf::Keyboard::Scancode TECLA_SALIDA = sf::Keyboard::Scancode::Escape;

// Fotogramas que te da el juego desde que haces un input de un ataque especial hasta
// que haces el siguiente como máximo
constexpr int COOLDOWN_ATAQUE_ESPECIAL = 30;

/*
    CONSTANTES PARA EL SONIDO Y LA MÚSICA
*/

// Volumen máximo del reproductor de música
constexpr double VOLUMEN_MAXIMO_MUSICA = 100.0f;

// Volumen máximo del reproductor de efectos de sonido
constexpr double VOLUMEN_MAXIMO_SONIDOS = 100.0f;

/*
    CONSTANTES PARA LOS FICHEROS
*/

// Secuencia de caracteres que delimita los distintos elementos de un fichero
const std::string SECUENCIA_DELIMITADORA_FICHERO = "----------------------------------------";

// Secuencia de caracteres que indica el fin de un fichero
const std::string SECUENCIA_FIN_FICHERO = "####";

/*
    CONSTANTES PARA LAS ANIMACIONES
*/

// Valor máximo que debería tener el contador de parpadeo para hacer que una animación
// con gravedad se dé por terminada
constexpr int MAX_CONTADOR_PARPADEO = 40;

// Cada cuántos fotogramas las animaciones con gravedad pasan a ser visibles o invisibles para
// el efecto de parpadeo
constexpr int DURACION_PARPADEO = 2;

// Máxima velocidad de giro de una partícula en cualquier dirección
constexpr double MAX_VELOCIDAD_GIRO_PART = 10;

// Máxima velocidad en cualquier eje de una partícula pequeña
constexpr int MAX_VELOCIDAD_PARTICULA_PEQUE = 3;

// Máxima velocidad en cualquier eje de una partícula mediana
constexpr int MAX_VELOCIDAD_PARTICULA_MEDIA = 6;

// Máxima velocidad en cualquier eje de una partícula súper
constexpr int MAX_VELOCIDAD_PARTICULA_SUPER = 8;

// Cómo de desplazada está la animación del polvo en el eje X con respecto al centro del personaje
constexpr int OFFSET_POLVO = 15;

// Cuánto se agrandan o disminuyen las animaciones agrandables cada fotograma
constexpr double TASA_CRECIMIENTO_ANIMACION_AGRANDABLE = 0.1;

// Posición de los carteles que aparecen durante los combates (los de "¿Todo listo?" y tal)
constexpr sf::Vector2f POSICION_CARTELES_COMBATE = sf::Vector2f(VENTANA_ANCHURA/2, VENTANA_ALTURA/3);

// El número de partículas lineales que aparecen cuando un personaje es golpeado
// con un ataque peque
constexpr int NUM_PARTICULAS_LINEALES_ATAQUE_PEQUE = 2;

// El número de partículas lineales que aparecen cuando un personaje es golpeado
// con un ataque medio
constexpr int NUM_PARTICULAS_LINEALES_ATAQUE_MEDIO = 3;

// El número de píxeles que se mueven las partículas lineales que aparecen cuando
// un personaje es golpeado por un ataque peque
constexpr int LONGITUD_MOVIMIENTO_PARTICULA_LINEAL_ATAQUE_PEQUE = 15;

// El número de píxeles que se mueven las partículas lineales que aparecen cuando
// un personaje es golpeado por un ataque medio
constexpr int LONGITUD_MOVIMIENTO_PARTICULA_LINEAL_ATAQUE_MEDIO = 25;

// La proporción del recorrido que tiene que hacer una partícula lineal para empezar a menguar
// (la proporción se expresa como un número entre 0 y 1, donde 0 significa que todavía no ha
// empezado a moverse, y 1 significa que ya ha terminado)
constexpr float PROPORCION_RECORRIDO_MENGUAR_PARTICULA_LINEAL = 0.9;

/*
    CONSTANTES PARA EL MENÚ PRINCIPAL
*/

// Posición del centro del cartel de título de ÉRASE UN COMBATE
constexpr sf::Vector2f POSICION_TITULO = sf::Vector2f(VENTANA_ANCHURA/4,VENTANA_ALTURA/6);

// Posición en el eje X de los selectores de opción
constexpr float POSICION_X_SELECTOR = VENTANA_ANCHURA/4.f;

// Posición inicial en el eje Y de los selectores de opción
constexpr float POSICION_INICIAL_Y_SELECTOR = 12*VENTANA_ALTURA/20.f;

// Diferencia en la posición en el eje Y entre dos selectores adyacentes
constexpr float DIFERENCIA_POSICION_Y_SELECTOR = VENTANA_ALTURA/6.f;

// Diferencia en la posición en el eje Y entre dos fondos distintos usados
// por los selectores del menú principal
constexpr float DIFERENCIA_POSICION_Y_FONDO_SELECTOR = VENTANA_ALTURA/20.f;

// Diferencia en las escalas de dos selectores adyacentes
constexpr float DIFERENCIA_ESCALA_SELECTOR = 0.4f;

// Color para el selector que estamos seleccionando actualmente
constexpr sf::Color COLOR_SELECTOR_POSICION_RELATIVA_0 = sf::Color(255,255,255,255);

// Diferencia de transparencia de un selector que está una posición
// más arriba o abajo del selector actual
constexpr int DIFERENCIA_TRANSPARENCIA_SELECTOR = 100;

// Color para los selectores que están más de una posición alejados
// del selector actual
constexpr sf::Color COLOR_SELECTOR_POSICION_RELATIVA_MAYOR_QUE_1 = sf::Color(255,255,255,0);

// Color del fondo correspondiente a selectores sin seleccionar
constexpr sf::Color COLOR_FONDO_SELECTOR_SIN_SELECCIONAR = sf::Color(255,255,255,0);

// Color del fondo correspondiente al selector seleccionado
constexpr sf::Color COLOR_FONDO_SELECTOR_SELECCIONADO = sf::Color(255,255,255,255);

/*
    CONSTANTES PARA EL SELECTOR DE MANDOS
*/

// Color inicial del rectángulo que cubre el fondo en el menú de selección de jugador para el mando
constexpr sf::Color COLOR_INICIAL_RECTANGULO_OSCURO_SELECTOR_MANDOS = sf::Color(0,0,0,0);

// Color final del rectángulo que cubre el fondo en el menú de selección de jugador para el mando
constexpr sf::Color COLOR_FINAL_RECTANGULO_OSCURO_SELECTOR_MANDOS = sf::Color(0,0,0,125);

/*
    CONSTANTES PARA LOS PERSONAJES
*/

// Origen de los personajes (usando la plantilla)
constexpr sf::Vector2f PERSONAJE_PLANTILLA_ORIGEN = sf::Vector2f(64, 100);

// Gravedad del escenario
constexpr float GRAVEDAD = 0.4;

// Valor máximo del medidor de súper de un personaje
constexpr int MAX_MEDIDOR_SUPER = 50;

// Retraso entre movimientos de píxel y píxel del medidor de vida atrasado
// de un personaje, para evitar que vaya muy rápido
constexpr int MAX_RETRASO_MEDIDOR_VIDA_ATRASADO = 3;

// Aumento de velocidad cada fotograma al andar
constexpr float VELOCIDAD_ANDAR_AUMENTO = 0.3;

// Cuando un personaje GOLPEADO_BAJANDO choca el suelo con una velocidad menor a esta, pasa
// a estar TIRADO
constexpr float VELOCIDAD_PASAR_A_TIRADO = 4;

// Posición en el eje Y del suelo
constexpr float ALTURA_SUELO = VENTANA_ALTURA - 10;

// Impulso inicial en el eje X al recibir un golpe pequeño
constexpr float IMPULSO_GOLPE_PEQUE = 1;

// Impulso inicial en el eje X al recibir un golpe mediano
constexpr float IMPULSO_GOLPE_MEDIO = 3;

// Impulso inicial en los ejes X e Y al recibir un golpe súper
constexpr float IMPULSO_X_GOLPE_SUPER = 7;
constexpr float IMPULSO_Y_GOLPE_SUPER = -10;

// Impulso inicial en el eje Y al recibir un golpe bajo mediano
constexpr float IMPULSO_GOLPE_BAJO_MEDIO = -5;

// Máximo daño que puede hacer un ataque pequeño
constexpr int MAX_ATAQUE_PEQUE = 3;

// Máximo daño que puede hacer un ataque medio
constexpr int MAX_ATAQUE_MEDIO = 6;

// Valor que tiene que alcanzar contadorTumbado para que se levante un personaje
constexpr int MAX_CONTADOR_TUMBADO = 10;

// Valor inicial del contador de celebración. Al llegar a 0, el personaje que acaba de ganar celebra
constexpr int MAX_CONTADOR_CELEBRACION = NUMERO_FPS_INICIAL*2;

// Máximo de fotogramas que tienen que pasar desde que se empiece a caminar al revés del rival para poder
// hacerle parry a un ataque súper
constexpr int MAX_CONTADOR_ESQUIVE_SUPER = 4;

// La posición en la que aparece el destello
constexpr sf::Vector2f POSICION_DESTELLO_SUPER_CARGADA_J1 = {108.f,21.f};
constexpr sf::Vector2f POSICION_DESTELLO_SUPER_CARGADA_J2 = {34.f,21.f};

/*
    CONSTANTES PARA EL ESCENARIO
*/

// Si un personaje está a esta distancia o menos de un borde, el escenario se moverá para alejar a ese
// personaje del borde (siempre y cuando el otro personaje no esté también en el umbral)
constexpr int ESCENARIO_UMBRAL_MOVIMIENTO = 20;

// Altura en píxeles de las sombras
constexpr int ALTURA_SOMBRA = 4;

// Escala de la altura de la sombra de un sprite de un personaje durante un combate
constexpr float ESCALA_ALTURA_SOMBRA_PERSONAJE = -0.1;

/*
    CONSTANTES PARA LA GUI DE PERSONAJE
*/

// Posición de la GUI del personaje izquierdo (esquina superior izquierda (la
// posición del personaje derecho es igual pero en espejo))
constexpr sf::Vector2f POSICION_GUI_IZQUIERDA(4,4);

// Posición de las barras de vida de la GUI izquierda (real y atrasada) (relativa a la esquina superior
// izquierda del sprite de la GUI)
constexpr sf::Vector2f POSICION_BARRA_VIDA_IZQUIERDA(40,3);

// Tamaño de la barra de vida
constexpr sf::Vector2f TAMANO_BARRA_VIDA(70,8);

// Posición de la barra de súper de la GUI izquierda  (relativa a la esquina superior
// izquierda del sprite de la GUI)
constexpr sf::Vector2f POSICION_BARRA_SUPER_IZQUIERDA(40,19);

// Tamaño de la barra de súper
constexpr sf::Vector2f TAMANO_BARRA_SUPER(50,6);

// Posición del "portrait" del personaje de la GUI izquierda  (relativa a la esquina superior
// izquierda del sprite de la GUI)
constexpr sf::Vector2f POSICION_PORTRAIT_IZQUIERDA(3,3);

// Posición del nombre del personaje de la GUI izquierda  (relativa a la esquina superior
// izquierda del sprite de la GUI)
constexpr sf::Vector2f POSICION_NOMBRE_IZQUIERDA(40,28);

// Color de la barra de vida en tiempo real
constexpr sf::Color COLOR_BARRA_VIDA_REAL(106,206,64);

// Color de la barra de vida atrasada
constexpr sf::Color COLOR_BARRA_VIDA_ATRASADA(204,65,65);

// Color de la barra de súper
constexpr sf::Color COLOR_BARRA_SUPER(89,114,255);

// Cada cuántos fotogramas se actualiza la vibración
constexpr int CONTADOR_VIBRACION_MAX = 2;

/*
    CONSTANTES PARA LOS COMBOS
*/

// Cuántos fotogramas tiene un jugador para poder continuar un combo
constexpr int FRAMES_RESTANTES_COMBO = NUMERO_FPS_INICIAL;

// Durante cuántos fotogramas se mostrará la información del combo que
// acaba de terminar antes de desaparecer para siempre
constexpr int FRAMES_MOSTRAR_COMBO_TERMINADO = NUMERO_FPS_INICIAL*2;

// El color para los números y el texto que indican los golpes y
// el daño causado durante el combo para el jugador 1
constexpr sf::Color COLOR_INFO_COMBO_J1 = sf::Color(100,100,150);

// El color para los números y el texto que indican los golpes y
// el daño causado durante el combo para el jugador 2
constexpr sf::Color COLOR_INFO_COMBO_J2 = sf::Color(150,100,100);

// El número de píxeles que tiene que haber entre la información
// que sale con los golpes y del daño causado durante un combo y
// el borde más cercano. Para el jugador 1, es el margen con el borde
// izquierdo. Para el jugador 2, es el margen con el borde derecho
// (teniendo en cuenta en este caso los sprites de números que haya a
// la derecha del texto)
constexpr float MARGEN_HORIZONTAL_INFO_COMBO = 10.f;

// Posición en el eje Y de la información de los combos realizados
constexpr float POSICION_Y_INFO_COMBO = VENTANA_ALTURA/3.f;

// El número mínimo de golpes que tiene que tener un combo para
// que se muestre en pantalla
constexpr int MIN_GOLPES_MOSTRAR_COMBO = 3;

// La anchura de cada uno de los dígitos usados para contar
// los golpes y el daño causado durante los combos
constexpr int ANCHURA_DIGITO_COMBO = 10;

// En la información del combo, cómo de bajo o alto están los
// números que indican los golpes del combo, con respecto a la
// posición del texto del combo
constexpr int ALTURA_RELATIVA_NUMEROS_GOLPES_COMBO = 0;

// En la información del combo, cómo de bajo o alto están los
// números que indican el ataque del combo, con respecto a la
// posición del texto del combo
constexpr int ALTURA_RELATIVA_NUMEROS_ATAQUE_COMBO = 15;

// Cuando se continúa un combo suena un sonidito cada vez más agudo. Este
// es el tono máximo al que se debe reproducir ese sonido
constexpr float MAX_TONO_SONIDO_CONTINUAR_COMBO = 2.f;

// El color de la info del combo cuando el combo termina
constexpr sf::Color COLOR_COMBO_TERMINADO = sf::Color(100.f,100.f,100.f);

// El movimiento que hace la info del combo cada vez que el combo se continúa
constexpr sf::Vector2f MOVIMIENTO_INFO_COMBO_CONTINUAR = {0.f,-5.f};

/*
    CONSTANTES PARA EL ONLINE
*/

// El puerto utilizado por el líder para aceptar conexiones de invitados
constexpr unsigned short NUMERO_PUERTO = 21107;

// Bit que indica que el otro jugador se ha movido a la izquierda
constexpr uint8_t BIT_IZQUIERDA = 1;

// Bit que indica que el otro jugador se ha movido a la derecha
constexpr uint8_t BIT_DERECHA = 2;

// Bit que indica que el otro jugador se ha movido a la arriba
constexpr uint8_t BIT_ARRIBA = 4;

// Bit que indica que el otro jugador se ha movido a la abajo
constexpr uint8_t BIT_ABAJO = 8;

// Bit que indica que el otro jugador ha atacado
constexpr uint8_t BIT_ATAQUE = 16;

/*
    CONSTANTES AUXILIARES PARA COSAS DE C++
*/

// Si dos floats se diferencian en menos que este número, se consideran iguales
constexpr float UMBRAL_FLOAT = 0.001;

