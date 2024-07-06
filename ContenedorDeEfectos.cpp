#include "ContenedorDeEfectos.hpp"
#include "ContenedorDeRecursos.hpp"
#include "Bitacora.hpp"
#include "AnimacionPorFrames.hpp"
#include "Utilidades.hpp"
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <filesystem>

ContenedorDeEfectos * ContenedorDeEfectos::contenedorDeEfectos = nullptr;

ContenedorDeEfectos * ContenedorDeEfectos::unicaInstancia()
{
    if(contenedorDeEfectos==nullptr)
        contenedorDeEfectos = new ContenedorDeEfectos();
    return contenedorDeEfectos;
}

Animacion* ContenedorDeEfectos::obtenerEfecto(std::string nombre){
    // Es importante copiar la animación al trabajar con punteros
    return animaciones.at(nombre)->clonar();
}

void ContenedorDeEfectos::cargarTodosLosEfectos()
{
    Bitacora::unicaInstancia()->escribir("Juan Cuesta: Bien, sigamos... siguiente punto del día: registro de efectos especiales. Emilio, apunta, voy a dictarte los efectos en orden descendente de aparición.");

    // En esta variable se van a poner datos del fichero l�nea a l�nea
    std::string linea;

    // En esta variable se van a meter elementos separados en base a un string dado
    std::vector<std::string> elementosSeparados;

    // En esta variable se guarda el nombre del efecto
    std::string nombreEfecto;

    // En esta variable se guarda el tipo de animación del efecto
    std::string tipoAnimacion;

    // En esta variable se guarda el nombre del tipo de bucle usado para la animaci�n actual
    std::string nombreBucle;

    // En esta variable se guarda el n�mero de rect�ngulos de la animaci�n actual
    int numeroRectangulos;

    // En esta variable se guarda el sonido que se reproducir� en cada animaci�n
    sf::Sound sonido;

    // Abrimos cada fichero del directorio
    for(const auto & entrada : std::filesystem::directory_iterator("ficheros/efectos")){

        // Se abre el fichero con informaci�n del personaje actual
        std::ifstream fichero(entrada.path());

        // Aprovechando que tenemos la ruta del fichero podemos sacar el nombre del efecto
        nombreEfecto = entrada.path().stem().string();

        if(!fichero.is_open()){
            Bitacora::unicaInstancia()->escribir("Emilio: ... pero señor Juan, es para hoy.");
            Bitacora::unicaInstancia()->escribir("Juan Cuesta: Creo... creo que he extraviado el fichero ficheros/efectos.txt...");
            Bitacora::unicaInstancia()->escribir("Juan Cuesta: Qué follon... se suspende la junta.");
            exit(EXIT_FAILURE);
        } else {
            Bitacora::unicaInstancia()->escribir("Emilio: Listo señor Juan.");
            Bitacora::unicaInstancia()->escribir("Juan Cuesta: registrando efecto " + nombreEfecto + ".");
        }

        std::getline(fichero,linea);

        // Se obtiene el tipo de animación
        tipoAnimacion = util::separarString(linea,':')[1];

        Bitacora::unicaInstancia()->escribir("Juan Cuesta: animación de tipo " + tipoAnimacion + ".");

        // Se obtiene el tipo de bucle
        std::getline(fichero,linea);
        nombreBucle = util::separarString(linea,':')[1];

        // Se salta una l�nea en blanco y se empiezan a sacar rect�ngulos
        numeroRectangulos = 0;
        std::getline(fichero,linea);
        std::getline(fichero,linea);

        // En esta variable se guarda el mapa que mapea n�meros de rect�ngulo a hitboxes
        std::map<int,std::list<Hitbox>> hitboxes;

        while(util::separarString(linea,':')[0] == "Rectangulo"){

            Bitacora::unicaInstancia()->escribir("Juan Cuesta: rect�ngulo " + std::to_string(numeroRectangulos) + ".");

            // Lista de hitboxes para este rect�ngulo
            std::list<Hitbox> listaHitboxes;

            // Se salta la l�nea que dice "Hitboxes" y empezamos a contar hitboxes
            std::getline(fichero,linea);
            std::getline(fichero,linea);

            while(linea != ""){
                // Se sacan los enteros (pero son strings)
                std::vector<std::string> enterosPeroSonStrings = util::separarString(linea,',');

                // Se sacan los enteros de verdad
                std::vector<int> enteros;
                for(std::string string : enterosPeroSonStrings){
                    enteros.push_back(std::stoi(string));
                }

                // Se crea la hitbox en base a muchas cosas
                Hitbox h(sf::IntRect(enteros[0],enteros[1],enteros[2],enteros[3]),enteros[4],false);

                listaHitboxes.push_back(h);

                std::getline(fichero,linea);
            }

            hitboxes[numeroRectangulos] = listaHitboxes;

            std::getline(fichero,linea);
            numeroRectangulos++;
        }

        Bitacora::unicaInstancia()->escribir("Juan Cuesta: finalmente, se apuntan los frames.");

        // Ahora sacamos la correspondencia de frames y rect�ngulos
        std::getline(fichero,linea);

        int contadorFrame = 0;

        // En esta variable se guarda el mapa que mapea n�meros de frame a n�meros de rect�ngulo
        std::map<int,int> frameARectangulo;

        for(std::string rectanguloString : util::separarString(linea,',')){

            frameARectangulo[contadorFrame] = std::stoi(rectanguloString);

            contadorFrame++;
        }

        Bitacora::unicaInstancia()->escribir("Juan Cuesta: número de frames: " + std::to_string(contadorFrame));

        // Nos saltamos dos l�neas, y ahora puede haber informaci�n sobre los sonidos o no
        std::getline(fichero,linea);
        std::getline(fichero,linea);

        Animacion * anim;

        if(util::separarString(linea,':')[0] == "Sonido"){

            bool repetirSonido = util::separarString(linea,':')[1] == "repetir";

            sonido.setBuffer(ContenedorDeSonidos::unicaInstanciaSonidos()->obtener("sonidos/efectos/"+nombreEfecto+".wav"));

            // Avanzamos de l�nea para conseguir la lista de frames
            std::getline(fichero,linea);

            std::set<int> framesConSonido;

            for(std::string s : util::separarString(linea,',')){
                framesConSonido.insert(std::stoi(s));
            }

            sf::Texture& textura = ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/efectos/"+nombreEfecto+".png");

            anim = new AnimacionPorFrames(0,0,textura.getSize().x/numeroRectangulos/2,textura.getSize().y/2,numeroRectangulos, textura,
                                          util::stringATipoBucle(nombreBucle),0,hitboxes,frameARectangulo,sonido,framesConSonido,repetirSonido);

        } else {
            sf::Texture& textura = ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/efectos/"+nombreEfecto+".png");

            anim = new AnimacionPorFrames(0,0,textura.getSize().x/numeroRectangulos/2,textura.getSize().y/2,numeroRectangulos, textura,
                                            util::stringATipoBucle(nombreBucle),0,hitboxes,frameARectangulo);
        }

        animaciones.insert(std::pair<std::string,Animacion*>(nombreEfecto,anim));

        Bitacora::unicaInstancia()->escribir("Juan Cuesta: se termin� de cargar la animación para el efecto " + nombreEfecto + ".\n");
    }
}
