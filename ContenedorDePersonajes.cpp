#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeRecursos.hpp"
#include "Bitacora.hpp"
#include "Utilidades.hpp"
#include <SFML/Audio.hpp>
#include <fstream>
#include <iostream>
#include <memory>

ContenedorDePersonajes * ContenedorDePersonajes::contenedorDePersonajes = nullptr;

ContenedorDePersonajes * ContenedorDePersonajes::unicaInstancia()
{
    if(contenedorDePersonajes==nullptr)
        contenedorDePersonajes = new ContenedorDePersonajes();
    return contenedorDePersonajes;
}

Personaje ContenedorDePersonajes::obtenerPersonaje(std::string nombre){
    Personaje p = personajes.at(nombre);

    // Es importante copiar las animaciones apuntadas por los punteros para no repetir animaciones
    std::map<EstadoPersonaje,Animacion*> nuevasAnimaciones;

    for(auto &par : p.getAnimaciones()){
        nuevasAnimaciones[par.first] = par.second->clonar();
    }

    p.setAnimaciones(nuevasAnimaciones);

    return p;
}

void ContenedorDePersonajes::cargarTodosLosPersonajes()
{
    Bitacora::unicaInstancia()->escribir("Juan Cuesta: Siguiente punto del día: registro de personajes en el listado oficial. Emilio, apunta, voy a dictarte los personajes en orden descendente de aparición.");

    // En esta variable se van a poner datos del fichero línea a línea
    std::string linea;

    // En esta variable se van a meter elementos separados en base a un string dado
    std::vector<std::string> elementosSeparados;

    // En esta variable se guarda el nombre del personaje actual
    std::string nombrePersonaje;

    // En esta variable se guarda el nombre del estado actual
    std::string nombreEstado;

    // En esta variable se guarda el nombre del tipo de bucle usado para la animación actual
    std::string nombreBucle;

    // En esta variable se guarda el número de rectángulos de la animación actual
    int numeroRectangulos;

    // En esta variable se guarda el sonido que se reproducirá en cada animación
    sf::Sound sonido;

    // Se abre el fichero con información de los personajes
    std::ifstream fichero("ficheros/personajes.txt");

    if(!fichero.is_open()){
        Bitacora::unicaInstancia()->escribir("Emilio: ... pero señor Juan, es para hoy.");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Es que creo que he perdido el fichero ficheros/personajes.txt...");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Qué follon... se suspende la junta.");
        exit(EXIT_FAILURE);
    } else {
        Bitacora::unicaInstancia()->escribir("Emilio: Listo señor Juan.");
    }

    std::getline(fichero,linea);

    while(linea != SECUENCIA_FIN_FICHERO){

        // En esta variable se guarda el mapa que mapea estados a animaciones
        std::map<EstadoPersonaje,Animacion*> animaciones;

        // Se saca el nombre del personaje
        nombrePersonaje = util::separarString(linea,':')[1];
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: registrando personaje " + nombrePersonaje + ".");

        // Se salta una línea en blanco y se empiezan a leer estados
        std::getline(fichero,linea);
        std::getline(fichero,linea);

        while(linea != SECUENCIA_DELIMITADORA_FICHERO){

            // Se obtiene el nombre del estado
            nombreEstado = util::separarString(linea,':')[1];

            Bitacora::unicaInstancia()->escribir("Juan Cuesta: estado " + nombreEstado + ".");

            // Se obtiene el tipo de bucle
            std::getline(fichero,linea);
            nombreBucle = util::separarString(linea,':')[1];

            // Se salta una línea en blanco y se empiezan a sacar rectángulos
            numeroRectangulos = 0;
            std::getline(fichero,linea);
            std::getline(fichero,linea);

            // En esta variable se guarda el mapa que mapea números de rectángulo a hitboxes
            std::map<int,std::list<Hitbox>> hitboxes;

            while(util::separarString(linea,':')[0] == "Rectangulo"){

                Bitacora::unicaInstancia()->escribir("Juan Cuesta: rectángulo " + std::to_string(numeroRectangulos) + ".");

                // Lista de hitboxes para este rectángulo
                std::list<Hitbox> listaHitboxes;

                // Se salta la línea que dice "Hitboxes" y empezamos a contar hitboxes
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
                    Hitbox h(sf::IntRect(enteros[0],enteros[1],enteros[2],enteros[3]),enteros[4],nombreEstado == "ataque-agachado" && enteros[4] > 0);

                    listaHitboxes.push_back(h);

                    std::getline(fichero,linea);
                }

                hitboxes[numeroRectangulos] = listaHitboxes;

                std::getline(fichero,linea);
                numeroRectangulos++;
            }

            Bitacora::unicaInstancia()->escribir("Juan Cuesta: finalmente, se apuntan los frames.");

            // Ahora sacamos la correspondencia de frames y rectángulos
            std::getline(fichero,linea);

            int contadorFrame = 0;

            // En esta variable se guarda el mapa que mapea números de frame a números de rectángulo
            std::map<int,int> frameARectangulo;

            for(std::string rectanguloString : util::separarString(linea,',')){

                frameARectangulo[contadorFrame] = std::stoi(rectanguloString);

                contadorFrame++;
            }

            // Nos saltamos dos líneas, y ahora puede haber información sobre los sonidos o no
            std::getline(fichero,linea);
            std::getline(fichero,linea);

            Animacion * anim;

            if(util::separarString(linea,':')[0] == "Sonido"){

                bool repetirSonido = util::separarString(linea,':')[1] == "Repetir";

                sonido.setBuffer(ContenedorDeSonidos::unicaInstanciaSonidos()->obtener("sonidos/"+nombrePersonaje+"/"+nombreEstado+".wav"));

                // Avanzamos de línea para conseguir la lista de frames
                std::getline(fichero,linea);

                std::set<int> framesConSonido;

                for(std::string s : util::separarString(linea,',')){
                    framesConSonido.insert(std::stoi(s));
                }

                anim = new AnimacionPorFrames(0,0,PERSONAJE_PLANTILLA_ORIGEN.x,PERSONAJE_PLANTILLA_ORIGEN.y,numeroRectangulos,
                                              ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+nombrePersonaje+"/"+nombreEstado+".png"),
                                              util::stringATipoBucle(nombreBucle),0,hitboxes,frameARectangulo,sonido,framesConSonido,repetirSonido);

                // Nos saltamos dos líneas otra vez para salir de este estado
                std::getline(fichero,linea);
                std::getline(fichero,linea);

            } else {
                anim = new AnimacionPorFrames(0,0,PERSONAJE_PLANTILLA_ORIGEN.x,PERSONAJE_PLANTILLA_ORIGEN.y,numeroRectangulos,
                                              ContenedorDeTexturas::unicaInstanciaTexturas()->obtener("sprites/"+nombrePersonaje+"/"+nombreEstado+".png"),
                                              util::stringATipoBucle(nombreBucle),0,hitboxes,frameARectangulo);
            }

            animaciones.insert(std::pair<EstadoPersonaje,Animacion*>(util::stringAEstadoPersonaje(nombreEstado),anim));

            Bitacora::unicaInstancia()->escribir("Juan Cuesta: se terminó de cargar la animación para el estado " + nombreEstado + ".\n");
        }

        Personaje p(animaciones);
        personajes.insert(std::pair<std::string,Personaje>(nombrePersonaje,p));

        std::getline(fichero,linea);

        Bitacora::unicaInstancia()->escribir("Juan Cuesta: concluye la inserción del personaje " + nombrePersonaje + ".\n");
    }
}
