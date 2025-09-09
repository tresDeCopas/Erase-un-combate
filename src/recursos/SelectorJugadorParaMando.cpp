#include "SelectorJugadorParaMando.hpp"
#include "Constantes.hpp"
#include "VentanaPrincipal.hpp"
#include "ContenedorDeRecursos.hpp"
#include "ReproductorDeMusica.hpp"
#include "Utilidades.hpp"
#include "Configuracion.hpp"

// La instancia es nula al principio
SelectorJugadorParaMando *SelectorJugadorParaMando::selectorJugadorParaMando = nullptr;

SelectorJugadorParaMando *SelectorJugadorParaMando::unicaInstancia()
{
    if (selectorJugadorParaMando == nullptr)
        selectorJugadorParaMando = new SelectorJugadorParaMando();
    return selectorJugadorParaMando;
}

SelectorJugadorParaMando::~SelectorJugadorParaMando()
{
    if (selectorJugadorParaMando != nullptr)
        delete selectorJugadorParaMando;
}

SelectorJugadorParaMando::SelectorJugadorParaMando() : spriteJugador1(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/selector-mando/jugador1.png")),
                                                       spriteJugador2(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/selector-mando/jugador2.png")),
                                                       sonidoAparecer(ContenedorDeSonidos::unicaInstancia()->obtener("sonidos/seleccionar-mando/aparece-ventana.ogg")),
                                                       sonidoCambiarSeleccion(ContenedorDeSonidos::unicaInstancia()->obtener("sonidos/seleccionar-mando/cambiar-seleccion.ogg")),
                                                       sonidoDesaparecer(ContenedorDeSonidos::unicaInstancia()->obtener("sonidos/seleccionar-mando/desaparece-ventana.ogg"))
{
}

Jugador SelectorJugadorParaMando::decidirJugador(Control c)
{
    // Se guarda la canción que se estaba reproduciendo antes y se pausa
    std::string cancionAnterior = ReproductorDeMusica::unicaInstancia()->getCancionActual();
    ReproductorDeMusica::unicaInstancia()->pausar();

    // Se saca el tamaño de la ventana y se crea la textura con ese tamaño
    sf::Vector2u tamanoVentana = VentanaPrincipal::unicaInstancia()->getSize();
    sf::Texture texturaFondo({tamanoVentana.x, tamanoVentana.y});

    // Una vez se tiene la textura, se copia el contenido de la ventana
    texturaFondo.update(*VentanaPrincipal::unicaInstancia());

    // Se asigna la textura al sprite y se escala según el zoom para que el tamaño sea correcto
    sf::Sprite spriteFondo(texturaFondo);
    spriteFondo.scale(sf::Vector2f(1.0 / VentanaPrincipal::getZoom(), 1.0 / VentanaPrincipal::getZoom()));
    spriteFondo.setPosition({0, 0});

    // Se crea un rectángulo negro del tamaño de la ventana para poder oscurecer el fondo
    sf::RectangleShape rectanguloOscuro(sf::Vector2f(VENTANA_ANCHURA,VENTANA_ALTURA));
    rectanguloOscuro.setFillColor(COLOR_INICIAL_RECTANGULO_OSCURO_SELECTOR_MANDOS);

    sf::RenderWindow *ventana = VentanaPrincipal::unicaInstancia();

    Jugador jugadorSeleccionado = Jugador::JUGADOR1;

    bool jugadorDecidido = false;

    bool joystickMovido = false;

    sonidoAparecer.play();
    ReproductorDeMusica::unicaInstancia()->reproducir("musica/selector-mando.ogg");

    // while(rectanguloOscuro.getFillColor() != COLOR_FINAL_RECTANGULO_OSCURO_SELECTOR_MANDOS){

    //     // Se prepara un reloj para ver cuánto tiempo pasa entre fotogramas
    //     sf::Clock reloj;

    //     // Se comprueba solo el evento de cerrar la ventana
    //     while (const std::optional evento = ventana->pollEvent())
    //     {
    //         if (evento->is<sf::Event::Closed>())
    //         {
    //             exit(EXIT_SUCCESS);
    //         }
    //     }

    //     // Se aproxima el color del rectángulo del fondo al color final
    //     rectanguloOscuro.setFillColor(util::aproximarColor(rectanguloOscuro.getFillColor(),COLOR_FINAL_RECTANGULO_OSCURO_SELECTOR_MANDOS,0.8));

    //     // Se dibujan las cosas
    //     ventana->clear();
    //     ventana->draw(spriteFondo);
    //     ventana->draw(rectanguloOscuro);
    //     ventana->display();

    //     // El juego se duerme hasta que dé tiempo a dibujar el siguiente fotograma, teniendo en cuenta
    //     // que se deben dibujar 60 fotogramas por segundo y que cada fotograma además necesita un tiempo
    //     // previo de preparación para actualizar y dibujar y tal
    //     sf::sleep(sf::seconds(1.f / NUMERO_FPS) - reloj.reset());
    // }

    // Los sprites usados para mostrar qué jugador se ha seleccionado
    // se van haciendo más opacos con el tiempo
    spriteJugador1.setColor(sf::Color(255,255,255,0));
    spriteJugador2.setColor(sf::Color(255,255,255,0));

    while (!jugadorDecidido && ventana->isOpen())
    {
        // Se prepara un reloj para ver cuánto tiempo pasa entre fotogramas
        sf::Clock reloj;

        // Se comprueban los eventos como de costumbre
        while (const std::optional evento = ventana->pollEvent())
        {
            if (evento->is<sf::Event::Closed>())
            {
                exit(EXIT_SUCCESS);
            }
            else if (evento->is<sf::Event::JoystickButtonPressed>())
            {
                jugadorDecidido = true;
            }
            else if (evento->is<sf::Event::JoystickMoved>() &&
                     (evento->getIf<sf::Event::JoystickMoved>()->axis == sf::Joystick::Axis::PovX ||
                      evento->getIf<sf::Event::JoystickMoved>()->axis == sf::Joystick::Axis::X ||
                      evento->getIf<sf::Event::JoystickMoved>()->axis == sf::Joystick::Axis::R))
            {

                if (!joystickMovido && std::abs(evento->getIf<sf::Event::JoystickMoved>()->position) > UMBRAL_JOYSTICK)
                {
                    joystickMovido = true;
                    jugadorSeleccionado = (jugadorSeleccionado == Jugador::JUGADOR1 ? Jugador::JUGADOR2 : Jugador::JUGADOR1);
                    sonidoCambiarSeleccion.play();
                }
                else if (joystickMovido && std::abs(evento->getIf<sf::Event::JoystickMoved>()->position) < UMBRAL_JOYSTICK)
                {
                    joystickMovido = false;
                }
            }
        }

        // Se pone más claro el sprite de selección de jugador
        spriteJugador1.setColor(util::aproximarColor(spriteJugador1.getColor(),sf::Color::White,0.8));
        spriteJugador2.setColor(util::aproximarColor(spriteJugador2.getColor(),sf::Color::White,0.8));

        // Se dibujan las cosas
        ventana->clear();
        ventana->draw(spriteFondo);
        //ventana->draw(rectanguloOscuro);
        ventana->draw(jugadorSeleccionado == Jugador::JUGADOR1 ? spriteJugador1 : spriteJugador2);
        ventana->display();

        // El juego se duerme hasta que dé tiempo a dibujar el siguiente fotograma, teniendo en cuenta
        // que se deben dibujar 60 fotogramas por segundo y que cada fotograma además necesita un tiempo
        // previo de preparación para actualizar y dibujar y tal
        sf::sleep(sf::seconds(1.f / Configuracion::unicaInstancia()->getFPS()) - reloj.reset());
    }

    sonidoDesaparecer.play();

    // Se vuelve a reproducir la canción anterior
    ReproductorDeMusica::unicaInstancia()->detener();
    ReproductorDeMusica::unicaInstancia()->reproducir(cancionAnterior);

    return jugadorSeleccionado;
}