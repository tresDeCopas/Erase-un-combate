#include "VentanaPrincipal.hpp"
#include "Constantes.hpp"

sf::RenderWindow * VentanaPrincipal::ventanaPrincipal = nullptr;
int VentanaPrincipal::zoom = 1;

sf::RenderWindow * VentanaPrincipal::unicaInstancia()
{
    if(ventanaPrincipal==nullptr){
        ventanaPrincipal = new sf::RenderWindow(sf::VideoMode(VENTANA_ANCHURA, VENTANA_ALTURA), VENTANA_NOMBRE, VENTANA_ESTILO);
        ventanaPrincipal->setFramerateLimit(VENTANA_FPS);
    }
    return ventanaPrincipal;
}

void VentanaPrincipal::aumentarZoom(){
    zoom++;
    ventanaPrincipal->setSize(sf::Vector2u(VENTANA_ANCHURA * zoom,VENTANA_ALTURA * zoom));
}

void VentanaPrincipal::disminuirZoom(){
    if(zoom == 1) return;
    zoom--;
    ventanaPrincipal->setSize(sf::Vector2u(VENTANA_ANCHURA * zoom,VENTANA_ALTURA * zoom));
}
