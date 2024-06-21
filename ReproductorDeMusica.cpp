#include "ReproductorDeMusica.hpp"
#include "Bitacora.hpp"

ReproductorDeMusica * ReproductorDeMusica::reproductorDeMusica = nullptr;

ReproductorDeMusica * ReproductorDeMusica::unicaInstancia()
{
    if(reproductorDeMusica==nullptr)
        reproductorDeMusica = new ReproductorDeMusica();
    return reproductorDeMusica;
}

void ReproductorDeMusica::reproducir(std::string cancion)
{
    if(!musicaActual.openFromFile(cancion)){
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Emilio, vamos a animar un poco el ambiente, reproduce la canción " + cancion);
        Bitacora::unicaInstancia()->escribir("Emilio: Ah no, esa se la llevó mi padre y ya no la he vuelto a ver");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Pero... ¿para qué le das a tu padre un bien común de esta, nuestra comunidad?");
        Bitacora::unicaInstancia()->escribir("Emilio: Es que se puso muy pesado, y con tal de que me dejara un rato en paz...");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Voy a encontrar a Mariano inmediatamente. Se suspende la junta.");
        Bitacora::unicaInstancia()->escribir("Emilio: Pero no se enfade con él señor Juan, no es maldad, es que está demente ya.");
        exit(EXIT_FAILURE);
    }

    musicaActual.setLoop(true);
    musicaActual.setVolume(volumenActual);
    musicaActual.play();
}

void ReproductorDeMusica::detener()
{
    musicaActual.stop();
}

float ReproductorDeMusica::obtenerVolumen()
{
    return musicaActual.getVolume();
}

void ReproductorDeMusica::establecerVolumen(float nuevoVolumen)
{
    musicaActual.setVolume(nuevoVolumen > VOLUMEN_MAXIMO_MUSICA ? VOLUMEN_MAXIMO_MUSICA : nuevoVolumen < 0 ? 0 : nuevoVolumen);
}
