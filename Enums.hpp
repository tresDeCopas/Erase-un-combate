#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

/*
    Este fichero contiene enumerados (enums)
*/

// Enumerado para acciones que se pueden llevar a cabo al pulsar teclas
enum class Accion {
    NADA, IZQUIERDA, DERECHA, ARRIBA, ABAJO, ATACAR, ESCAPE
};

// Tipo de bucle en una animación
enum class TipoBucle {
    SIN_BUCLE,      // No hay bucle, cuando la animación termina se deja de actualizar
    NORMAL,         // Cuando termina la animación, vuelve a empezar desde el principio
    AL_REVES,       // Como el normal, pero desde el final hasta el principio
    PING_PONG       // POR ELIMINAR // Cuando termina la animación, empieza desde el final hasta el principio y al revés
};

// Enumerado para estados en los que se puede encontrar un personaje
enum class EstadoPersonaje {
    QUIETO,             // No hace nada, solo está quieto en el sitio
    AGACHADO,           // Está agachado y quieto
    ATAQUE_AGACHADO,    // Está atacando mientras está agachado
    ATAQUE_NORMAL_1,    // Está atacando de pie (primer ataque)
    ATAQUE_NORMAL_2,    // Está atacando de pie (segundo ataque)
    ATAQUE_NORMAL_3,    // Está atacando de pie (tercer ataque)
    ATAQUE_AEREO,       // Está atacando en el aire
    GOLPEADO_PEQUE,     // Ha sufrido un ataque pequeño
    GOLPEADO_MEDIO,     // Ha sufrido un ataque medio
    GOLPEADO_GRANDE,    // Ha sufrido un ataque grande
    GOLPEADO_BAJO,      // Ha sufrido un ataque bajo
    SALTANDO_SUBIENDO,  // Está en el aire subiendo después de saltar
    SALTANDO_BAJANDO,   // Está en el aire bajando después de saltar y alcanzar la máxima altura
    ANDANDO_ACERCANDOSE,// Está andando hacia el enemigo
    ANDANDO_ALEJANDOSE, // Está andando alejándose del enemigo
    BLOQUEANDO,         // Está bloqueando un ataque
    PREPARANDO_SUPER,   // Está preparándose para lanzar el super ataque
    ATAQUE_SUPER,       // Está haciendo el super ataque
    LEVANTANDOSE,       // Se está levantando del suelo
    CELEBRANDO          // Está celebrando su victoria
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
