#ifndef __BITACORA_HPP__
#define __BITACORA_HPP__

#include <fstream>
#include <string>

/*
    Esta clase gestiona una bit�cora que informa de cosas
    importantes que pasan en la ejecuci�n del programa
*/

class Bitacora
{
private:
    // El propio fichero de bit�cora
    std::ofstream ficheroBitacora;

    Bitacora();
    ~Bitacora();

    // �nica instancia
    static Bitacora *bitacora;

public:
    // Se escriben cosas en el fichero de bitácora terminando con un fin de línea
    void escribir(std::string cosillas);

    // Se comprueba si la tarjeta gr�fica tiene lo que hay que tener
    void comprobarGrafica();

    // NUNCA SE COPIA UN SINGLETON
    Bitacora(Bitacora &otra) = delete;

    // NUNCA SE ASIGNA UN SINGLETON
    void operator=(const Bitacora &) = delete;

    // Devuelve la �nica instancia de la bit�cora
    static Bitacora *unicaInstancia();
};

#endif // __BITACORA_HPP__
