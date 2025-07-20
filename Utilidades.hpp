#include "SFML/System.hpp"
#include <string>
#include <sstream>

/*
    Este namespace contiene funciones �tiles
*/

namespace util{

    // Dado un string de entrada y un car�cter separador, corta el string original en substrings y
    // los devuelve en forma de vector (sin incluir el car�cter separador)
    inline std::vector<std::string> separarString(std::string string, char separador){

        std::stringstream stringstream(string);

        std::vector<std::string> vectorParaDevolver;

        std::string datos;

        while(std::getline(stringstream,datos,separador)){
            vectorParaDevolver.push_back(datos);
        }

        return vectorParaDevolver;
    }

    // Dado un string, devuelve el tipo de bucle correspondiente
    inline TipoBucle stringATipoBucle(std::string string){
        if(string == "normal")
            return TipoBucle::NORMAL;
        if(string == "al-reves")
            return TipoBucle::AL_REVES;
        if(string == "ping-pong")
            return TipoBucle::PING_PONG;

        return TipoBucle::SIN_BUCLE;
    }

    // Dado un string, devuelve el estado de personaje correspondiente
    inline EstadoPersonaje stringAEstadoPersonaje(std::string string){
        if(string == "quieto")
            return EstadoPersonaje::QUIETO;
        if(string == "agachado")
            return EstadoPersonaje::AGACHADO;
        if(string == "ataque-agachado")
            return EstadoPersonaje::ATAQUE_AGACHADO;
        if(string == "ataque-normal-1")
            return EstadoPersonaje::ATAQUE_NORMAL_1;
        if(string == "ataque-normal-2")
            return EstadoPersonaje::ATAQUE_NORMAL_2;
        if(string == "ataque-normal-3")
            return EstadoPersonaje::ATAQUE_NORMAL_3;
        if(string == "ataque-aereo")
            return EstadoPersonaje::ATAQUE_AEREO;
        if(string == "golpeado-peque")
            return EstadoPersonaje::GOLPEADO_PEQUE;
        if(string == "golpeado-medio")
            return EstadoPersonaje::GOLPEADO_MEDIO;
        if(string == "golpeado-grande")
            return EstadoPersonaje::GOLPEADO_GRANDE;
        if(string == "golpeado-bajo")
            return EstadoPersonaje::GOLPEADO_BAJO;
        if(string == "saltando-subiendo")
            return EstadoPersonaje::SALTANDO_SUBIENDO;
        if(string == "saltando-bajando")
            return EstadoPersonaje::SALTANDO_BAJANDO;
        if(string == "andando-acercandose")
            return EstadoPersonaje::ANDANDO_ACERCANDOSE;
        if(string == "andando-alejandose")
            return EstadoPersonaje::ANDANDO_ALEJANDOSE;
        if(string == "bloqueando")
            return EstadoPersonaje::BLOQUEANDO;
        if(string == "preparando-super")
            return EstadoPersonaje::PREPARANDO_SUPER;
        if(string == "atacando-super")
            return EstadoPersonaje::ATAQUE_SUPER;
        if(string == "levantandose")
            return EstadoPersonaje::LEVANTANDOSE;
        if(string == "celebrando")
            return EstadoPersonaje::CELEBRANDO;

        return EstadoPersonaje::QUIETO;
    }

    // Dados dos rectángulos, calcula el centro del subrectángulo que resulta de la intersección
    // de ambos rectángulos
    inline sf::Vector2f centroDeInterseccion(sf::IntRect r1, sf::IntRect r2){
        
        int izquierda = std::max(r1.left, r2.left);
        int arriba = std::max(r1.top, r2.top);

        int derecha = std::min(r1.left+r1.width, r2.left+r2.width);
        int abajo = std::min(r1.top+r1.height, r2.top+r2.height);

        return sf::Vector2f(izquierda + (derecha - izquierda)/2, arriba + (abajo-arriba)/2);
    }

    // Devuelve un número real en el rango [0,1)
    inline double realAleatorio(){
        return ((double)rand()) / RAND_MAX;
    }
}
