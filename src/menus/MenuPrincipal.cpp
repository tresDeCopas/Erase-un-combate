#include "MenuPrincipal.hpp"
#include "ContenedorDeEfectos.hpp"
#include "ContenedorDeRecursos.hpp"
#include "Constantes.hpp"
#include "VentanaPrincipal.hpp"
#include "GestorDeControles.hpp"
#include "ReproductorDeMusica.hpp"
#include "ReproductorDeSonidos.hpp"
#include "Configuracion.hpp"
#include "Utilidades.hpp"
#include <algorithm>

SelectorMenuPrincipal::SelectorMenuPrincipal(sf::Texture& texturaSelector, sf::Texture& texturaFondo, TipoSelectorMenuPrincipal tipoSelector) :
spriteSelector(texturaSelector), spriteFondo(texturaFondo), tipoSelector(tipoSelector), posicionRelativa(static_cast<int>(tipoSelector))
{
    // Se pone el origen en el centro a la izquierda del todo porque mola más
    spriteSelector.setOrigin(sf::Vector2f(spriteSelector.getTextureRect().size)/2.f);
    resetear();
}

void SelectorMenuPrincipal::resetear()
{
    // Se establece la posición relativa en base al tipo de selector (se asume que
    // al resetear los selectores, en el menú principal se pasará a seleccionar
    // el selector 0)
    posicionRelativa = static_cast<int>(tipoSelector);
    
    // Se pone el selector y el fondo en las posiciones correctas
    spriteSelector.setPosition({POSICION_X_SELECTOR, POSICION_INICIAL_Y_SELECTOR + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR});
    spriteFondo.setPosition({0.f, posicionRelativa*DIFERENCIA_POSICION_Y_FONDO_SELECTOR});

    // Se pone el color correcto para el selector y su fondo
    sf::Color colorSelector = COLOR_SELECTOR_POSICION_RELATIVA_0;
    colorSelector.a = std::clamp(colorSelector.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);
    spriteSelector.setColor(colorSelector);

    // Se pone la escala correcta para el sprite
    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;
    spriteSelector.setScale({escalaDeseadaSprite,escalaDeseadaSprite});

    if(posicionRelativa == 0)
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_SELECCIONADO);
    else
        spriteFondo.setColor(COLOR_FONDO_SELECTOR_SIN_SELECCIONAR);
}

void SelectorMenuPrincipal::actualizar()
{
    sf::Vector2f posicionDeseadaSprite;
    sf::Color colorDeseadoSprite = COLOR_SELECTOR_POSICION_RELATIVA_0;
    sf::Vector2f posicionDeseadaFondo;
    sf::Color colorDeseadoFondo;

    float escalaDeseadaSprite = 1.f - std::abs(posicionRelativa)*DIFERENCIA_ESCALA_SELECTOR;
    if(escalaDeseadaSprite < 0.f) escalaDeseadaSprite = 0.f;

    posicionDeseadaSprite.x = POSICION_X_SELECTOR;

    colorDeseadoSprite.a = std::clamp(colorDeseadoSprite.a-std::abs(posicionRelativa)*DIFERENCIA_TRANSPARENCIA_SELECTOR,0,255);

    if(posicionRelativa == 0)
    {
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_SELECCIONADO;
        escalaDeseadaSprite = 1.f;
    }
    else
    {
        colorDeseadoFondo = COLOR_FONDO_SELECTOR_SIN_SELECCIONAR;
    }

    posicionDeseadaSprite.y = POSICION_INICIAL_Y_SELECTOR + posicionRelativa*DIFERENCIA_POSICION_Y_SELECTOR*escalaDeseadaSprite;
    posicionDeseadaFondo.x = 0;
    posicionDeseadaFondo.y = posicionRelativa * DIFERENCIA_POSICION_Y_FONDO_SELECTOR;

    spriteSelector.setPosition(util::aproximarVector2f(spriteSelector.getPosition(),posicionDeseadaSprite,0.8f));
    spriteSelector.setColor(util::aproximarColor(spriteSelector.getColor(),colorDeseadoSprite,0.8f));
    spriteFondo.setPosition(util::aproximarVector2f(spriteFondo.getPosition(),posicionDeseadaFondo,0.8f));
    spriteFondo.setColor(util::aproximarColor(spriteFondo.getColor(),colorDeseadoFondo,0.8f));
    spriteSelector.setScale(util::aproximarVector2f(spriteSelector.getScale(),{escalaDeseadaSprite,escalaDeseadaSprite},0.8f));
}

void SelectorMenuPrincipal::seleccionar()
{
    spriteSelector.setScale(spriteSelector.getScale()/2.f);
}


// La instancia es nula al principio
MenuPrincipal * MenuPrincipal::menuPrincipal = nullptr;

MenuPrincipal * MenuPrincipal::unicaInstancia()
{
    if(menuPrincipal == nullptr)
        menuPrincipal = new MenuPrincipal();
    return menuPrincipal;
}

MenuPrincipal::~MenuPrincipal(){
    if(menuPrincipal != nullptr) delete menuPrincipal;
}

MenuPrincipal::MenuPrincipal() : seleccionActual(0),
                                 cartelTitulo(ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("titulo")),
                                 dientesSierraArriba(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/dientes-sierra.png")),
                                 dientesSierraAbajo(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/dientes-sierra.png")),
                                 brilloSelector(0.f), selectorPulsado(false), rectanguloNegro({VENTANA_ANCHURA,VENTANA_ALTURA}){
    // Se coloca todo en su posición inicial
    resetear();
    
    selectores.emplace_back(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/selector-modo-historia.png"),
                            ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/captura-modo-historia.png"),
                            TipoSelectorMenuPrincipal::MODO_HISTORIA);
    
    selectores.emplace_back(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/selector-batalla-vs.png"),
                            ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/captura-batalla-vs.png"),
                            TipoSelectorMenuPrincipal::BATALLA_VS);

    selectores.emplace_back(ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/selector-opciones.png"),
                            ContenedorDeTexturas::unicaInstancia()->obtener("sprites/menu-principal/captura-opciones.png"),
                            TipoSelectorMenuPrincipal::OPCIONES);
    

    shaderDestello = std::make_shared<sf::Shader>();
    if(!shaderDestello->loadFromFile("shaders/blendColor.frag",sf::Shader::Type::Fragment)){
        Bitacora::unicaInstancia()->escribir("ERROR: no se pudo cargar el shader");
        exit(EXIT_FAILURE);
    }

    rectanguloNegro.setFillColor(sf::Color::Black);
}

void MenuPrincipal::resetear() {
    cartelTitulo->setPosicion(POSICION_TITULO);
    dientesSierraArriba.setPosition({0,0});
    dientesSierraAbajo.setPosition({0,-58});

    for(SelectorMenuPrincipal& selector : selectores)
    {
        selector.resetear();
    }
}

void MenuPrincipal::cambiarPosicionRelativa()
{
    for(int i=0;i<selectores.size();i++)
    {
        selectores[i].setPosicionRelativa(i-seleccionActual);
    }
}

TipoSelectorMenuPrincipal MenuPrincipal::comenzar(){

    resetear();

    ReproductorDeMusica::unicaInstancia()->reproducir("musica/menu-principal.ogg");

    sf::RenderWindow * ventana = VentanaPrincipal::unicaInstancia();

    std::list<std::shared_ptr<Animacion>> animaciones;

    animaciones.push_back(cartelTitulo);

    selectorPulsado = false;

    seleccionActual = 0;

    while(!(selectorPulsado && rectanguloNegro.getFillColor().a == 255)){
        // Se prepara un reloj para ver cuánto tiempo pasa entre fotogramas
        sf::Clock reloj;

        while(const std::optional evento = ventana->pollEvent()){
            if(evento->is<sf::Event::Closed>()){
                exit(EXIT_SUCCESS);
            } else if(!selectorPulsado) {
                InfoEvento infoEvento = GestorDeControles::unicaInstancia()->comprobarEvento(evento);
                if(infoEvento.realizada){
                    if(infoEvento.accion == Accion::ARRIBA && seleccionActual > 0)
                    {
                        ReproductorDeSonidos::unicaInstancia()->reproducir("sonidos/menu-principal/cambiar-seleccion.ogg");
                        seleccionActual--;
                        cambiarPosicionRelativa();
                    }
                    else if (infoEvento.accion == Accion::ABAJO && seleccionActual < selectores.size()-1)
                    {
                        ReproductorDeSonidos::unicaInstancia()->reproducir("sonidos/menu-principal/cambiar-seleccion.ogg");
                        seleccionActual++;
                        cambiarPosicionRelativa();
                    }
                    else if (infoEvento.accion == Accion::ATACAR)
                    {
                        ReproductorDeMusica::unicaInstancia()->detener();
                        ReproductorDeSonidos::unicaInstancia()->reproducir("sonidos/menu-principal/seleccionar.ogg");
                        
                        std::shared_ptr<Animacion> anim;
                        shaderDestello->setUniform("amount",1.f);
                        brilloSelector = 1.f;
                        selectorPulsado = true;
                        switch(selectores[seleccionActual].getTipoSelector()){
                            case TipoSelectorMenuPrincipal::MODO_HISTORIA:
                                anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-modo-historia-destello");
                                break;
                            case TipoSelectorMenuPrincipal::BATALLA_VS:
                                anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-batalla-vs-destello");
                                break;
                            case TipoSelectorMenuPrincipal::OPCIONES:
                                anim = ContenedorDeEfectos::unicaInstancia()->obtenerEfecto("selector-opciones-destello");
                                break;
                        }
                        
                        sf::Vector2f posicionEfecto = selectores[seleccionActual].getSprite().getPosition();

                        anim->setPosicion(posicionEfecto);
                        animaciones.push_back(anim);
                        
                        selectores[seleccionActual].seleccionar();
                    }
                }
            }
        }

        std::list<std::shared_ptr<Animacion>> nuevasAnimaciones;

        for(std::shared_ptr<Animacion> &a : animaciones){
            a->actualizar(nuevasAnimaciones);
        }

        // Se cambia la opacidad del rectángulo negro según sea necesario
        if(rectanguloNegro.getFillColor().a > 0 && (!selectorPulsado || (selectorPulsado && brilloSelector >= 0.1f))){
            rectanguloNegro.setFillColor(sf::Color(rectanguloNegro.getFillColor().r, rectanguloNegro.getFillColor().g, rectanguloNegro.getFillColor().b, rectanguloNegro.getFillColor().a-5));
        } else if (selectorPulsado && brilloSelector < 0.1f && rectanguloNegro.getFillColor().a < 255){
            rectanguloNegro.setFillColor(sf::Color(rectanguloNegro.getFillColor().r, rectanguloNegro.getFillColor().g, rectanguloNegro.getFillColor().b, rectanguloNegro.getFillColor().a+5));
        }

        dientesSierraArriba.move({0,-0.2});

        if(dientesSierraArriba.getPosition().y <= -58) dientesSierraArriba.setPosition({0,0});

        dientesSierraAbajo.move({0,0.2});

        if(dientesSierraAbajo.getPosition().y >= 0) dientesSierraAbajo.setPosition({0,-58});

        for(std::shared_ptr<Animacion> &nA : nuevasAnimaciones){
            animaciones.push_back(nA);
        }

        // Se actualiza el brillo del shader
        brilloSelector = util::aproximarFloat(brilloSelector, 0.f, 0.95f);
        shaderDestello->setUniform("amount",brilloSelector);

        for(SelectorMenuPrincipal& selector : selectores)
        {
            selector.actualizar();
        }

        ventana->clear(sf::Color(0,0,0));

        for(SelectorMenuPrincipal& selector : selectores)
        {
            ventana->draw(selector.getFondo());
        }

        ventana->draw(dientesSierraArriba);
        ventana->draw(dientesSierraAbajo);

        sf::RenderStates states;

        if(selectorPulsado){
            states.shader = shaderDestello.get();
        }

        for(int i=0;i<selectores.size();i++)
        {
            if(i == seleccionActual)
                ventana->draw(selectores[i].getSprite(),states);
            else
                ventana->draw(selectores[i].getSprite());
        }

        for(std::shared_ptr<Animacion> &a : animaciones){
            ventana->draw(*a);
        }

        ventana->draw(rectanguloNegro);
        
        ventana->display();

        sf::sleep(sf::seconds(1.f / Configuracion::unicaInstancia()->getFPS()) - reloj.reset());
    }

    return static_cast<TipoSelectorMenuPrincipal>(seleccionActual);
}