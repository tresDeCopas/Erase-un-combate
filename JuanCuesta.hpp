#ifndef __JUAN_CUESTA_HPP__
#define __JUAN_CUESTA_HPP__

#include "Personaje.hpp"

/*
    Clase que define a Juan Cuesta, presidente de esta, nuestra Comunidad
*/
class JuanCuesta : public Personaje {
    private:



    public:

        using Personaje::Personaje;

        virtual void actualizar(sf::Vector2u posicionEnemigo);

        virtual void comprobarColisiones(std::list<Animacion*> &animaciones);

        virtual Personaje * clonar();
};

#endif // __JUAN_CUESTA_HPP__
