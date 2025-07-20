#ifndef __REPRODUCTOR_DE_MUSICA_HPP__
#define __REPRODUCTOR_DE_MUSICA_HPP__

#include <SFML/Audio.hpp>
#include "Constantes.hpp"
#include "Enums.hpp"
#include <string>
#include <map>

/*
    Clase que se encarga de reproducir música para que el
    resto de clases no se tengan que preocupar de eso
*/
class ReproductorDeMusica
{
    private:
        ReproductorDeMusica(){
            volumenActual = VOLUMEN_MAXIMO_MUSICA;
        }

        static ReproductorDeMusica * reproductorDeMusica;

        sf::Music musicaActual;
        std::map<std::string, std::string> rutasDeFicheros;
        float volumenActual;

    public:

        // Reproduce la canción dado su identificador
        void reproducir(std::string cancion);

        // Detiene por completo la reproducción de la canción
        void detener();

        // Devuelve el volumen de la canción actual
        float obtenerVolumen();

        // Establece el nuevo volumen para la canción actual y las siguientes
        void establecerVolumen(float nuevoVolumen);

        // NUNCA SE COPIA UN SINGLETON
        ReproductorDeMusica(ReproductorDeMusica &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const ReproductorDeMusica &) = delete;

        // Devuelve la única instancia
        static ReproductorDeMusica * unicaInstancia();

};

#endif // __REPRODUCTOR_DE_MUSICA_HPP__
