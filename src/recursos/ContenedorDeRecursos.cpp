#include <assert.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include "Bitacora.hpp"
#include "ContenedorDeRecursos.hpp"

// Las variables estáticas para implementar Singleton se inicializan nulas
template <class Recurso, class Identificador>
ContenedorDeTexturas * ContenedorDeRecursos<Recurso,Identificador>::contenedorDeTexturas = nullptr;

template <class Recurso, class Identificador>
ContenedorDeSonidos * ContenedorDeRecursos<Recurso,Identificador>::contenedorDeSonidos = nullptr;

template <class Recurso, class Identificador>
ContenedorDeFuentes * ContenedorDeRecursos<Recurso,Identificador>::contenedorDeFuentes = nullptr;

template <>
ContenedorDeTexturas * ContenedorDeTexturas::unicaInstancia()
{
    if(contenedorDeTexturas == nullptr)
        contenedorDeTexturas = new ContenedorDeTexturas();
    return contenedorDeTexturas;
}

template <>
ContenedorDeSonidos * ContenedorDeSonidos::unicaInstancia()
{
    if(contenedorDeSonidos == nullptr)
        contenedorDeSonidos = new ContenedorDeSonidos();
    return contenedorDeSonidos;
}

template <>
ContenedorDeFuentes * ContenedorDeFuentes::unicaInstancia()
{
    if(contenedorDeFuentes == nullptr)
        contenedorDeFuentes = new ContenedorDeFuentes();
    return contenedorDeFuentes;
}

template <>
void ContenedorDeFuentes::cargar(std::string id, const std::string& rutaFichero){
    // Los punteros únicos son mejores que los normales porque se borran solos cuando
    // se salen del scope este como le llaman (cuando se acaba la funcion o el if{} ya me entiendes)
    std::unique_ptr<sf::Font> recurso = std::make_unique<sf::Font>(rutaFichero);

    // Se intenta cargar el recurso. Si no es posible, se escribe en la bitácora y se va todo a la mi3rda
    if(!recurso){
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Emilio, ¿has podido cargar el fichero " + rutaFichero + " como te pedí?");
        Bitacora::unicaInstancia()->escribir("Emilio: Lo siento señor Juan pero no está por aquí, y yo de portería para fuera cobro un suplemento.");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Qué follon... Se suspende la junta.");
        exit(EXIT_FAILURE);
    }

    // Si todo ha ido bien, creamos un par (Identificador,std::unique_ptr<Recurso>) y lo metemos en el mapa
    // Es importante utilizar std::move() para que el recurso pase a los dominios del mapa y deje
    // de existir en estos dominios, esa es la gracia de los unique_ptr
    mapaDeRecursos.insert(std::make_pair(id,std::move(recurso)));
}

template <>
void ContenedorDeTexturas::cargar(std::string id, const std::string& rutaFichero){
    // Los punteros únicos son mejores que los normales porque se borran solos cuando
    // se salen del scope este como le llaman (cuando se acaba la funcion o el if{} ya me entiendes)
    std::unique_ptr<sf::Texture> recurso = std::make_unique<sf::Texture>();

    // Se intenta cargar el recurso. Si no es posible, se escribe en la bitácora y se va todo a la mi3rda
    if(!recurso->loadFromFile(rutaFichero)){
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Emilio, ¿has podido cargar el fichero " + rutaFichero + " como te pedí?");
        Bitacora::unicaInstancia()->escribir("Emilio: Lo siento señor Juan pero no está por aquí, y yo de portería para fuera cobro un suplemento.");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Qué follon... Se suspende la junta.");
        exit(EXIT_FAILURE);
    }

    // Si todo ha ido bien, creamos un par (Identificador,std::unique_ptr<Recurso>) y lo metemos en el mapa
    // Es importante utilizar std::move() para que el recurso pase a los dominios del mapa y deje
    // de existir en estos dominios, esa es la gracia de los unique_ptr
    mapaDeRecursos.insert(std::make_pair(id,std::move(recurso)));
}

template <>
void ContenedorDeSonidos::cargar(std::string id, const std::string& rutaFichero){
    // Los punteros únicos son mejores que los normales porque se borran solos cuando
    // se salen del scope este como le llaman (cuando se acaba la funcion o el if{} ya me entiendes)
    std::unique_ptr<sf::SoundBuffer> recurso = std::make_unique<sf::SoundBuffer>();

    // Se intenta cargar el recurso. Si no es posible, se escribe en la bitácora y se va todo a la mi3rda
    if(!recurso->loadFromFile(rutaFichero)){
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Emilio, ¿has podido cargar el fichero " + rutaFichero + " como te pedí?");
        Bitacora::unicaInstancia()->escribir("Emilio: Lo siento señor Juan pero no está por aquí, y yo de portería para fuera cobro un suplemento.");
        Bitacora::unicaInstancia()->escribir("Juan Cuesta: Qué follon... Se suspende la junta.");
        exit(EXIT_FAILURE);
    }

    // Si todo ha ido bien, creamos un par (Identificador,std::unique_ptr<Recurso>) y lo metemos en el mapa
    // Es importante utilizar std::move() para que el recurso pase a los dominios del mapa y deje
    // de existir en estos dominios, esa es la gracia de los unique_ptr
    mapaDeRecursos.insert(std::make_pair(id,std::move(recurso)));
}