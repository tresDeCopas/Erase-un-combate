#pragma once

/*
    Esta clase gestiona la configuración del juego,
    pudiendo modificarla en tiempo de ejecución (en vez
    de tener que modificar las constantes de Constantes.hpp
    y volver a compilar que es cutrísimo)
*/

class Configuracion
{
    private:
        // Indica si las hitboxes se ven o no
        bool hitboxesVisibles;

        // Indica el número de FPSs (fotogramas por segundo)
        int fps;

        // Indica si la salida del juego va a la consola o
        // al fichero de bitácora
        bool salidaABitacora;

        // Constructor y destructor (privados para que no se líe)
        Configuracion();
        ~Configuracion();

        // Única instancia
        static Configuracion *configuracion;

    public:
        // Permite activar/desactivar el modo de hitboxes visibles
        void setHitboxesVisibles(bool hitboxesVisibles);

        // Devuelve si las hitboxes se ven
        bool isHitboxesVisibles();

        // Permite cambiar los FPSs
        void setFPS(int fps);

        // Devuelve el número de FPSs
        int getFPS();

        // Permite activar/desactivar si la salida va a la bitácora
        // o a la consola
        void setSalidaABitacora(bool salidaAbitacora);

        // Devuelve si la salida va a bitácora o no
        bool isSalidaABitacora();

        // NUNCA SE COPIA UN SINGLETON
        Configuracion(Configuracion &otra) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const Configuracion &) = delete;

        // Devuelve la única instancia de la configuración
        static Configuracion *unicaInstancia();
};