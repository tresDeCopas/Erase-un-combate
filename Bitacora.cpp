#include "Bitacora.hpp"
#include "Constantes.hpp"
#include <iostream>

Bitacora * Bitacora::bitacora = nullptr;

Bitacora * Bitacora::unicaInstancia()
{
    if(bitacora==nullptr)
        bitacora = new Bitacora();
    return bitacora;
}

Bitacora::Bitacora(){
    // Abre la bitácora para añadir información al final (append, como se dice en inglés)
    ficheroBitacora.open(BITACORA_RUTA,std::ios_base::app);

    // Se registra el día de hoy en la bitácora para situarnos
    time_t tt;
    struct tm* ti;
    time(&tt);
    ti = localtime(&tt);

    ficheroBitacora << "----------------------------------------------" << std::endl;
    ficheroBitacora << "Juan Cuesta: Queridos convecinos, gracias por asistir a esta junta. Hoy estamos a: " << asctime(ti) << std::endl << std::endl;

    comprobarGrafica();
}

Bitacora::~Bitacora(){
    ficheroBitacora.close();
}

void Bitacora::escribir(std::string cosillas)
{
    ficheroBitacora << cosillas << std::endl;
    if(DEBUG)
        std::cerr << cosillas << std::endl;
}

void Bitacora::comprobarGrafica(){
    ficheroBitacora << "Juan Cuesta: Primer punto del día: comprobación rutinaria de la tarjeta gráfica." << std::endl;
    ficheroBitacora << "Emilio: Señor Juan, he estado mirando y la tarjeta gráfica soporta texturas de hasta " << sf::Texture::getMaximumSize() << " píxeles." << std::endl;
    if(sf::Texture::getMaximumSize() < MAXIMA_LONGITUD_TEXTURA){
        ficheroBitacora << "Juan Cuesta: ¡¿Cómo?! Pero bueno, esto es... no doy crédito..." << std::endl;
        ficheroBitacora << "Paloma: Ay Juan, ¡tranquilízate, hombre ya! ¡Recuerda la úlcera!" << std::endl;
        ficheroBitacora << "Juan Cuesta: Si es que no puede ser... este juego tiene texturas de hasta " << MAXIMA_LONGITUD_TEXTURA << " píxeles, esta tarjeta gráfica no va a poder aguantarlo..." << std::endl;
        ficheroBitacora << "Concha: ¡Váyase señor Cuesta! ¡¡VÁYASE!!" << std::endl;
        ficheroBitacora << "Marisa: La has cagao macho, esto no tira ni de puta coña." << std::endl;
        ficheroBitacora << "Juan Cuesta: A ver, las ultras, que se tranquilicen." << std::endl << std::endl;
    } else {
        ficheroBitacora << "Juan Cuesta: Perfecto, una buena cifra. Prosigamos." << std::endl;
    }
}
