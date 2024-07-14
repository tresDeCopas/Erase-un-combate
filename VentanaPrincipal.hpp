#ifndef __VENTANA_PRINCIPAL_HPP__
#define __VENTANA_PRINCIPAL_HPP__

#include <SFML/Graphics.hpp>

/*
    Clase "Singleton" para tener una ventana global. En vez de ser un Singleton de la propia clase, lo es
    de una ventana sf::RenderWindow, que es un poco más raro pero bueno, funciona bien que es lo que importa
*/
class VentanaPrincipal {
    private:
        // Constructor por defecto vac�o
        VentanaPrincipal();

        // Única instancia
        static sf::RenderWindow * ventanaPrincipal;

        // Zoom aplicado
        static int zoom;

        // Potencia de vibración
        static int potenciaVibracion;

        // Contador que, al llegar a cero, indica que se puede actualizar la vibración otra vez
        static int contadorVibracion;

    public:
        // Devuelve la �nica instancia
        static sf::RenderWindow * unicaInstancia();

        // Aumenta el zoom en 100% con respecto al zoom actual (de 100% a 200%, luego 300%...)
        static void aumentarZoom();

        // Disminuye el zoom en 100% con respecto al zoom actual (de 300% a 200%, luego 100% y ya no baja más)
        static void disminuirZoom();

        // Dada una potencia de vibración, la pantalla se pone a vibrar hacia arriba y hacia abajo
        static void vibrar(int potenciaVibracion);

        // Actualiza la ventana si tiene que vibrar
        static void actualizar();

        // NUNCA SE COPIA UN SINGLETON
        VentanaPrincipal(VentanaPrincipal &otra) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const VentanaPrincipal &) = delete;
};

#endif // __VENTANA_PRINCIPAL_HPP__
