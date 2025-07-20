#ifndef __VENTANA_PRINCIPAL_HPP__
#define __VENTANA_PRINCIPAL_HPP__

#include <SFML/Graphics.hpp>

/*
    Clase Singleton para tener una ventana global
*/
class VentanaPrincipal {
    private:
        // Constructor por defecto vacío
        VentanaPrincipal();

        // Única instancia
        static sf::RenderWindow * ventanaPrincipal;

        // Zoom aplicado
        static int zoom;

    public:
        // Devuelve la única instancia
        static sf::RenderWindow * unicaInstancia();

        // Aumenta el zoom en 100% con respecto al zoom actual (de 100% a 200%, luego 300%...)
        static void aumentarZoom();

        // Disminuye el zoom en 100% con respecto al zoom actual (de 300% a 200%, luego 100% y ya no baja más)
        static void disminuirZoom();

        // NUNCA SE COPIA UN SINGLETON
        VentanaPrincipal(VentanaPrincipal &otra) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const VentanaPrincipal &) = delete;
};

#endif // __VENTANA_PRINCIPAL_HPP__
