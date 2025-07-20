#include "Utilidades.hpp"

namespace util{

    std::vector<std::string> separarString(std::string string, char separador){

        std::stringstream stringstream(string);

        std::vector<std::string> vectorParaDevolver;

        std::string datos;

        while(std::getline(stringstream,datos,separador)){
            vectorParaDevolver.push_back(datos);
        }

        return vectorParaDevolver;
    }

    TipoBucle stringATipoBucle(std::string string){
        if(string == "normal")
            return TipoBucle::NORMAL;
        if(string == "al-reves")
            return TipoBucle::AL_REVES;
        if(string == "ping-pong")
            return TipoBucle::PING_PONG;

        return TipoBucle::SIN_BUCLE;
    }

    EstadoPersonaje stringAEstadoPersonaje(std::string string){
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
        if(string == "golpeado-subiendo")
            return EstadoPersonaje::GOLPEADO_SUBIENDO;
        if(string == "golpeado-bajando")
            return EstadoPersonaje::GOLPEADO_BAJANDO;
        if(string == "saltando-subiendo")
            return EstadoPersonaje::SALTANDO_SUBIENDO;
        if(string == "saltando-bajando")
            return EstadoPersonaje::SALTANDO_BAJANDO;
        if(string == "tocando-suelo")
            return EstadoPersonaje::TOCANDO_SUELO;
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
        if(string == "tumbado")
            return EstadoPersonaje::TUMBADO;
        if(string == "levantandose")
            return EstadoPersonaje::LEVANTANDOSE;
        if(string == "celebrando")
            return EstadoPersonaje::CELEBRANDO;

        return EstadoPersonaje::QUIETO;
    }

    sf::Vector2f centroDeInterseccion(sf::IntRect r1, sf::IntRect r2){
        
        int izquierda = std::max(r1.left, r2.left);
        int arriba = std::max(r1.top, r2.top);

        int derecha = std::min(r1.left+r1.width, r2.left+r2.width);
        int abajo = std::min(r1.top+r1.height, r2.top+r2.height);

        return sf::Vector2f(izquierda + (derecha - izquierda)/2, arriba + (abajo-arriba)/2);
    }

    double realAleatorio(){
        return ((double)rand()) / RAND_MAX;
    }
}
