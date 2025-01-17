#ifndef __TIEMPO_DELTA_HPP__
#define __TIEMPO_DELTA_HPP__

#include <SFML/System.hpp>

/*
    Clase Singleton que se encarga de llevar la cuenta de cuánto tiempo pasa entre cada frame del juego,
    pudiendo así que el juego vaya fluido incluso en ordenadores patateros (aunque puede que
    gaste mucha CPU, eso hay que verlo)
*/
class TiempoDelta
{
    private:
        TiempoDelta(){}

        static TiempoDelta * tiempoDelta;

        // Reloj que permite calcular cuánto tiempo ha pasado desde el último frame
        sf::Clock relojDelta;

        // Fracción de frame ha pasado desde la última llamada a resetearDelta (por ejemplo,
        // con 60 FPS tienen que pasar más o menos 0.0167 segundos
        // para que un frame se considere completo, así que si han pasado 0.01 segundos
        // pues devuelve 0.01/0.167 = 0.599)
        float fraccionDelta;

    public:
        
        // Obtiene el valor de la variable fraccionDelta
        float getFraccionDelta();

        // Pone el relojDelta a cero y guarda el tiempo pasado en fraccionDelta
        void resetearDelta();

        // NUNCA SE COPIA UN SINGLETON
        TiempoDelta(TiempoDelta &otro) = delete;

        // NUNCA SE ASIGNA UN SINGLETON
        void operator=(const TiempoDelta &) = delete;

        // Devuelve la única instancia
        static TiempoDelta * unicaInstancia();

};

#endif // __TIEMPO_DELTA_HPP__