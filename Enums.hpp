#ifndef __ENUMS_HPP__
#define __ENUMS_HPP__

// Este fichero contiene enumerados (enums)

// Enumerado para acciones que se pueden llevar a cabo al pulsar teclas
enum class Accion {
    IZQUIERDA, DERECHA, ARRIBA, ABAJO, ATACAR, ESCAPE
};

// Tipo de bucle en una animación
enum class TipoBucle {
    SIN_BUCLE,      // No hay bucle, cuando la animación termina se deja de actualizar
    NORMAL,         // Cuando termina la animación, vuelve a empezar desde el principio
    PING_PONG       // Cuando termina la animación, empieza desde el final hasta el principio y al revés
};

// Tipo de hitbox
enum class TipoHitbox {
    INVALIDA,       // Para animaciones sin hitbox (nubes de polvo, partículas que saltan...)
    PERSONAJE1,     // Hitbox para el propio personaje 1
    ATAQUE1,        // Hitbox para un ataque realizado por el personaje 1
    PERSONAJE2,     // Hitbox para el propio personaje 2
    ATAQUE2         // Hitbox para un ataque realizado por el personaje 2
};

// Tipo de ataque
enum class TipoAtaque {
    PEQUE, MEDIO, GRANDE, BAJO, AEREO
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
    GOLPEADO_PEQUE,   // Ha sufrido un ataque pequeño
    GOLPEADO_MEDIO,     // Ha sufrido un ataque medio
    GOLPEADO_GRANDE,     // Ha sufrido un ataque grande
    SALTANDO,           // Está en el aire después de saltar
    ANDANDO_IZQUIERDA,  // Está andando hacia la izquierda
    ANDANDO_DERECHA,    // Está andando hacia la derecha
    BLOQUEANDO,         // Está bloqueando un ataque
    PREPARANDO_SUPER,   // Está preparándose para lanzar el super ataque
    ATACANDO_SUPER,     // Está haciendo el super ataque
    LEVANTANDOSE,       // Se está levantando del suelo
    CELEBRANDO          // Está celebrando su victoria
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

// Enumerado para los identificadores de texturas
enum class IDTextura {

};

// Enumerado para los identificadores de sonidos
enum class IDSonido {

};

// Enumerado para los identificadores de fuentes
enum class IDFuente {

};

#endif // __ENUMS_HPP__
