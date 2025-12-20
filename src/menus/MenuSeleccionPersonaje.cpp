#include "MenuSeleccionPersonaje.hpp"
#include "Constantes.hpp"
#include "ReproductorDeMusica.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "Configuracion.hpp"
#include "Utilidades.hpp"
#include "ContenedorDePersonajes.hpp"

#include <algorithm>

// La instancia es nula al principio
MenuSeleccionPersonaje * MenuSeleccionPersonaje::menuSeleccionPersonaje = nullptr;

MenuSeleccionPersonaje * MenuSeleccionPersonaje::unicaInstancia()
{
    if(menuSeleccionPersonaje == nullptr)
        menuSeleccionPersonaje = new MenuSeleccionPersonaje();
    return menuSeleccionPersonaje;
}

MenuSeleccionPersonaje::~MenuSeleccionPersonaje(){
    if(menuSeleccionPersonaje != nullptr) delete menuSeleccionPersonaje;
}

MenuSeleccionPersonaje::MenuSeleccionPersonaje() :
indiceJugador1(0), indiceJugador2(1), personajeElegidoJugador1(false), personajeElegidoJugador2(false),
spriteMarco(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/eleccion-personaje/marco.png")),
rectanguloNegro({VENTANA_ANCHURA,VENTANA_ALTURA})
{
    rectanguloNegro.setFillColor(sf::Color::Black);

    // A la hora de colocar los selectores de personaje, la posición relativa
    // del primero para el jugador 1 será 0, y la posición relativa del primero
    // para el jugador 2 será -1. Luego se irán aumentando en 1 las posiciones
    // relativas por cada personaje introducido
    int posicionRelativaJugador1 = -indiceJugador1;
    int posicionRelativaJugador2 = -indiceJugador2;

    for(const std::string& nombrePersonaje : ContenedorDePersonajes::unicaInstancia()->obtenerNombresPersonajes())
    {
        sf::Texture& texturaPortraitPersonaje = ContenedorDeTexturas::unicaInstancia()->obtener("sprites/personajes/"+nombrePersonaje+"/portrait.png");

        selectoresPersonajeJugador1.emplace_back(texturaPortraitPersonaje, nombrePersonaje, Jugador::JUGADOR1, posicionRelativaJugador1);
        selectoresPersonajeJugador2.emplace_back(texturaPortraitPersonaje, nombrePersonaje, Jugador::JUGADOR2, posicionRelativaJugador2);
                                        
        posicionRelativaJugador1++;
        posicionRelativaJugador2++;
    }

    resetear();
}

void MenuSeleccionPersonaje::resetear()
{
    indiceJugador1 = 0;
    indiceJugador2 = 1;
    personajeElegidoJugador1 = false;
    personajeElegidoJugador2 = false;

    for(int i=0;i<selectoresPersonajeJugador1.size();i++)
    {
        selectoresPersonajeJugador1[i].resetear(i-indiceJugador1);
        selectoresPersonajeJugador2[i].resetear(i-indiceJugador2);
    }
}

std::unordered_map<Jugador,std::string> MenuSeleccionPersonaje::comenzarEleccionDoble()
{
    // Se resetea todo antes de empezar por si acaso
    resetear();

    ReproductorDeMusica::unicaInstancia()->reproducir("musica/menu-eleccion-personaje.ogg");

    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();

    // Esta variable indica si se está saliendo del menú de selección de personaje, ya sea
    // porque se ha cancelado la selección y se ha vuelto hacia atrás, o porque se han
    // elegido a los personajes y va a comenzar el combate
    bool saliendo = false;

    // El mapa que se va a devolver, con el personaje que ha elegido cada jugador
    std::unordered_map<Jugador,std::string> personajesElegidos;

    while(!(saliendo && rectanguloNegro.getFillColor().a == 255)){
        // Se prepara un reloj para ver cuánto tiempo pasa entre fotogramas
        sf::Clock reloj;

        while(const std::optional evento = ventana->pollEvent())
        {
            if(evento->is<sf::Event::Closed>()){
                exit(EXIT_SUCCESS);
            }

            InfoEvento infoEvento(GestorDeControles::unicaInstancia()->comprobarEvento(evento));

            if(infoEvento.accion == Accion::ESCAPE && infoEvento.realizada)
            {
                saliendo = true;
                ReproductorDeMusica::unicaInstancia()->detener();
            }
            else if(infoEvento.accion == Accion::DERECHA && infoEvento.realizada)
            {
                if(infoEvento.jugador == Jugador::JUGADOR1 && indiceJugador1 < selectoresPersonajeJugador1.size()-1)
                    indiceJugador1++;
                else if(infoEvento.jugador == Jugador::JUGADOR2 && indiceJugador2 < selectoresPersonajeJugador2.size()-1)
                    indiceJugador2++;
            }
            else if(infoEvento.accion == Accion::IZQUIERDA && infoEvento.realizada)
            {
                if(infoEvento.jugador == Jugador::JUGADOR1 && indiceJugador1 > 0)
                    indiceJugador1--;
                else if(infoEvento.jugador == Jugador::JUGADOR2 && indiceJugador2 > 0)
                    indiceJugador2--;
            }
        }

        // Asumimos que selectoresPersonajeJugador1 tiene la misma longitud
        // que selectoresPersonajeJugador2 porque se supone que ambos jugadores
        // tienen acceso a los mismos personajes
        for(int i=0; i<selectoresPersonajeJugador1.size(); i++)
        {
            selectoresPersonajeJugador1[i].setPosicionRelativa(i-indiceJugador1);
            selectoresPersonajeJugador2[i].setPosicionRelativa(i-indiceJugador2);

            selectoresPersonajeJugador1[i].actualizar();
            selectoresPersonajeJugador2[i].actualizar();
        }

        // Se cambia la opacidad del rectángulo negro según sea necesario
        if(rectanguloNegro.getFillColor().a > 0 && !saliendo)
        {
            rectanguloNegro.setFillColor(sf::Color(rectanguloNegro.getFillColor().r, rectanguloNegro.getFillColor().g, rectanguloNegro.getFillColor().b, rectanguloNegro.getFillColor().a-5));
        }
        else if (saliendo && rectanguloNegro.getFillColor().a < 255)
        {
            rectanguloNegro.setFillColor(sf::Color(rectanguloNegro.getFillColor().r, rectanguloNegro.getFillColor().g, rectanguloNegro.getFillColor().b, rectanguloNegro.getFillColor().a+5));
        }

        ventana->clear(sf::Color(0,0,0));

        ventana->draw(spriteMarco);

        for(int i=0;i<selectoresPersonajeJugador1.size();i++)
        {
            ventana->draw(selectoresPersonajeJugador1[i]);
            ventana->draw(selectoresPersonajeJugador2[i]);
        }

        ventana->draw(rectanguloNegro);
        
        ventana->display();

        sf::sleep(sf::seconds(1.f / Configuracion::unicaInstancia()->getFPS()) - reloj.reset());
    }

    return personajesElegidos;
}