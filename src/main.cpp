#include "ContenedorDePersonajes.hpp"
#include "ContenedorDeEfectos.hpp"
#include "MenuPrincipal.hpp"
#include "Combate.hpp"
#include "MenuSeleccionPersonaje.hpp"

#include "yaml-cpp/yaml.h"
#include <iostream>

#include <unistd.h>

int main(int argc, char* argv[]){

    // Los personajes y efectos son recursos que se tienen que cargar desde un principio.
    // Los recursos más sencillos (efectos de sonido, fuentes, texturas) se pueden cargar al vuelo según se
    // necesite
    ContenedorDePersonajes::unicaInstancia()->cargarTodosLosPersonajes();

    ContenedorDeEfectos::unicaInstancia()->cargarTodosLosEfectos();

    while(true){

        TipoSelectorMenuPrincipal seleccion = MenuPrincipal::unicaInstancia()->comenzar();

        if(seleccion == TipoSelectorMenuPrincipal::BATALLA_VS)
        {
            Combate combate("juan-cuesta-sin-casco", "juan-cuesta-sin-casco", "fachada-erase-unos-estatutos");
            combate.comenzar();
        }
        else if (seleccion == TipoSelectorMenuPrincipal::MODO_HISTORIA)
        {
            std::unordered_map<Jugador,std::string> personajesElegidos = MenuSeleccionPersonaje::unicaInstancia()->comenzarEleccionDoble();
            if(!personajesElegidos.empty())
            {
                // noseque
            }
        }
        else if (seleccion == TipoSelectorMenuPrincipal::OPCIONES)
        {
            execl("EraseUnActualizador.exe","EraseUnActualizador.exe",nullptr);
            perror("No se pudo iniciar el actualizador");
        }
    }
    

    // if(argc == 1){
    //     Combate combate("juan-cuesta-sin-casco", "juan-cuesta-sin-casco", "fachada");
    //     combate.comenzar();
    // } else {
    //     Combate combate("juan-cuesta-sin-casco", "juan-cuesta-con-casco", "fachada", sf::IpAddress(std::atoi(argv[1]),std::atoi(argv[2]),std::atoi(argv[3]),std::atoi(argv[4])), std::stoi(argv[5]));
    //     combate.comenzar();
    // }
}