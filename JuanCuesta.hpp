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

        virtual void actualizar();

        virtual void comprobarColisiones(std::list<Animacion*> &animaciones);

        virtual Personaje * clonar();

        virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif // __JUAN_CUESTA_HPP__
