#include "MenuSeleccionPersonaje.hpp"
#include "Constantes.hpp"
#include "ReproductorDeMusica.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "Configuracion.hpp"
#include "Utilidades.hpp"

#include <algorithm>

SelectorPersonaje::SelectorPersonaje(const sf::Texture& texturaSelector, const std::string& nombrePersonaje, Jugador jugador) :
spriteSelector(texturaSelector), nombrePersonaje(nombrePersonaje), posicionRelativa(0), jugador(jugador)
{
    // Se pone el origen en el centro a la izquierda del todo porque mola más
    spriteSelector.setOrigin(sf::Vector2f(spriteSelector.getTextureRect().size)/2.f);
    resetear();
}

void SelectorPersonaje::resetear()
{
    // Se pone el selector y el fondo en las posiciones correctas
    float posicionX = jugador == Jugador::JUGADOR1 ?
                      POSICION_X_SELECTOR_PERSONAJE_J1 :
                      POSICION_X_SELECTOR_PERSONAJE_J2;
    
    spriteSelector.setPosition({posicionX + posicionRelativa*DIFERENCIA_POSICION_X_SELECTOR_PERSONAJE, POSICION_Y_SELECTOR_PERSONAJE});

    // Se pone el color correcto para el selector y su fondo
    sf::Color colorSelector = COLOR_SELECTOR_POSICION_RELATIVA_0;
    colorSelector.a = std::clamp(colorSelector.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);
    spriteSelector.setColor(colorSelector);

    // Se pone la escala correcta para el sprite
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;
    spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});
}

void SelectorPersonaje::actualizar()
{
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_POSICION_RELATIVA_0;
    sf::Vector2f posicionDeseadaFondo;
    sf::Color colorDeseadoFondo;

    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    posicionDeseadaSprite.x = jugador == Jugador::JUGADOR1 ?
                              POSICION_X_SELECTOR_PERSONAJE_J1 :
                              POSICION_X_SELECTOR_PERSONAJE_J2;
    posicionDeseadaSprite.x += posicionRelativa*DIFERENCIA_POSICION_X_SELECTOR_PERSONAJE*escalaDeseadaSprite;
    posicionDeseadaSprite.y = POSICION_Y_SELECTOR_PERSONAJE;

    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);

    spriteSelector.setPosition(util::aproximarVector2f(spriteSelector.getPosition(),posicionDeseadaSprite,0.8f));
    spriteSelector.setColor(util::aproximarColor(spriteSelector.getColor(),colorDeseadoSprite,0.8f));
    spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{escalaDeseadaSprite,escalaDeseadaSprite},0.8f));
}

void SelectorPersonaje::seleccionar()
{
    spriteSelector.setScale(spriteSelector.getScale()/2.f);
}


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