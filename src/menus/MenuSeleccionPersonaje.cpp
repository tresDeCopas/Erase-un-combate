#include "MenuSeleccionPersonaje.hpp"
#include "Constantes.hpp"
#include "ReproductorDeMusica.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "Configuracion.hpp"

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
}

void MenuSeleccionPersonaje::resetear()
{
    indiceJugador1 = 0;
    indiceJugador2 = 1;
    personajeElegidoJugador1 = false;
    personajeElegidoJugador2 = false;
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

        ventana->draw(rectanguloNegro);
        
        ventana->display();

        sf::sleep(sf::seconds(1.f / Configuracion::unicaInstancia()->getFPS()) - reloj.reset());
    }

    return personajesElegidos;
}