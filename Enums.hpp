#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

/*
    Este fichero contiene enumerados (enums)
*/

// Enumerado para acciones que se pueden llevar a cabo al pulsar teclas
enum class Accion {
    NADA, IZQUIERDA, DERECHA, ARRIBA, ABAJO, ATACAR, ESCAPE
};

// Tipo de bucle en una animaci�n
enum class TipoBucle {
    SIN_BUCLE,      // No hay bucle, cuando la animaci�n termina se deja de actualizar
    NORMAL,         // Cuando termina la animaci�n, vuelve a empezar desde el principio
    AL_REVES,       // Como el normal, pero desde el final hasta el principio
    PING_PONG       // Cuando termina la animaci�n, empieza desde el final hasta el principio y al rev�s
};

// Enumerado para estados en los que se puede encontrar un personaje
enum class EstadoPersonaje {
    QUIETO,             // No hace nada, solo est� quieto en el sitio
    AGACHADO,           // Est� agachado y quieto
    ATAQUE_AGACHADO,    // Est� atacando mientras est� agachado
    ATAQUE_NORMAL_1,    // Est� atacando de pie (primer ataque)
    ATAQUE_NORMAL_2,    // Est� atacando de pie (segundo ataque)
    ATAQUE_NORMAL_3,    // Est� atacando de pie (tercer ataque)
    ATAQUE_AEREO,       // Est� atacando en el aire
    GOLPEADO_PEQUE,     // Ha sufrido un ataque peque�o
    GOLPEADO_MEDIO,     // Ha sufrido un ataque medio
    GOLPEADO_GRANDE,    // Ha sufrido un ataque grande
    GOLPEADO_BAJO,      // Ha sufrido un ataque bajo
    SALTANDO_SUBIENDO,  // Est� en el aire subiendo despu�s de saltar
    SALTANDO_BAJANDO,   // Est� en el aire bajando despu�s de saltar y alcanzar la m�xima altura
    ANDANDO_ACERCANDOSE,// Est� andando hacia el enemigo
    ANDANDO_ALEJANDOSE, // Est� andando alej�ndose del enemigo
    BLOQUEANDO,         // Est� bloqueando un ataque
    PREPARANDO_SUPER,   // Est� prepar�ndose para lanzar el super ataque
    ATAQUE_SUPER,     // Est� haciendo el super ataque
    LEVANTANDOSE,       // Se est� levantando del suelo
    CELEBRANDO          // Est� celebrando su victoria
};

enum class TipoPlantilla {
    PERSONAJE, EFECTO
};

// Enumerado para los jugadores
enum class Jugador {
    NADIE, JUGADOR1, JUGADOR2
};

// Posibles controles que un jugador puede utilizar
enum class Control{
    TECLADO_IZQUIERDA, TECLADO_DERECHA,
    MANDO0, MANDO1, MANDO2, MANDO3,
    MANDO4, MANDO5, MANDO6, MANDO7
};

/*
    ENUMERADOS DE IDENTIFICADORES
*/


#endif // __ENUMS_HPP__
