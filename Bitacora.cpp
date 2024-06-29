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
    // Abre la bit�cora para a�adir informaci�n al final (append, como se dice en ingl�s)
    ficheroBitacora.open(BITACORA_RUTA,std::ios_base::app);

    // Se registra el d�a de hoy en la bit�cora para situarnos
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
    ficheroBitacora << "Juan Cuesta: Primer punto del d�a: comprobaci�n rutinaria de la tarjeta gr�fica." << std::endl;
    ficheroBitacora << "Emilio: Se�or Juan, he estado mirando y la tarjeta gr�fica soporta texturas de hasta " << sf::Texture::getMaximumSize() << " p�xeles." << std::endl;
    if(sf::Texture::getMaximumSize() < MAXIMA_LONGITUD_TEXTURA){
        ficheroBitacora << "Juan Cuesta: ��C�mo?! Pero bueno, esto es... no doy cr�dito..." << std::endl;
        ficheroBitacora << "Paloma: Ay Juan, �tranquil�zate, hombre ya! �Recuerda la �lcera!" << std::endl;
        ficheroBitacora << "Juan Cuesta: Si es que no puede ser... este juego tiene texturas de hasta " << MAXIMA_LONGITUD_TEXTURA << " p�xeles, esta tarjeta gr�fica no va a poder aguantarlo..." << std::endl;
        ficheroBitacora << "Concha: �V�yase se�or Cuesta! ��V�YASE!!" << std::endl;
        ficheroBitacora << "Marisa: La has cagao macho, esto no tira ni de puta co�a." << std::endl;
        ficheroBitacora << "Juan Cuesta: A ver, las ultras, que se tranquilicen." << std::endl << std::endl;
    } else {
        ficheroBitacora << "Juan Cuesta: Perfecto, una buena cifra. Prosigamos." << std::endl;
    }
}
