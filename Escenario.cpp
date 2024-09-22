#include "Escenario.hpp"
#include "Constantes.hpp"

Escenario::Escenario(sf::Texture& texturaFondo, sf::Texture& texturaFrente){
    spriteFondo.setTexture(texturaFondo);
    spriteFrente.setTexture(texturaFrente);

    // Se saca justo la mitad de la anchura de los sprites y se coloca el origen en esa X
    // (la Y da igual porque el escenario no se puede mover hacia arriba o abajo)
    spriteFondo.setOrigin(spriteFondo.getTextureRect().getSize().x/2,0);
    spriteFrente.setOrigin(spriteFrente.getTextureRect().getSize().x/2,0);

    // Los sprites se mueven al centro
    spriteFondo.setPosition(VENTANA_ANCHURA/2,0);
    spriteFrente.setPosition(VENTANA_ANCHURA/2,0);
}

void Escenario::actualizar(Personaje& personaje1, Personaje& personaje2, std::list<std::shared_ptr<Animacion>>& efectos){

    // Se sacan valores al principio para que sea más sencillo de hacer
    sf::Vector2f posicion1(personaje1.getPosicion());
    sf::Vector2f posicion2(personaje2.getPosicion());
    int umbral_izquierda = ESCENARIO_UMBRAL_MOVIMIENTO;
    int umbral_derecha = VENTANA_ANCHURA-1 - ESCENARIO_UMBRAL_MOVIMIENTO;

    // Se calculan cosas para no hacer que las condiciones de los ifs sean de 352 km

    // Hay un personaje en el borde izquierdo
    bool personajeEnLadoIzquierdo = posicion1.x <= umbral_izquierda || posicion2.x <= umbral_izquierda;

    // Hay un personaje en el borde derecho
    bool personajeEnLadoDerecho = posicion1.x >= umbral_derecha || posicion2.x >= umbral_derecha;

    // El escenario ha alcanzado el tope del lado izquierdo y ya no puede seguir más hacia ese lado
    bool escenarioTopeIzquierda = (VENTANA_ANCHURA-(spriteFondo.getPosition().x-1)) > spriteFondo.getTextureRect().width/2;

    // El escenario ha alcanzado el tope del lado derecho y ya no puede seguir más hacia ese lado
    bool escenarioTopeDerecha = spriteFondo.getPosition().x+1 > spriteFondo.getTextureRect().width/2;

    // Si hay un personaje yendose mucho a la izquierda, el otro está lejos del otro borde, y el escenario
    // aún puede ir más a la derecha, se mueve todo a la derecha
    if(personajeEnLadoIzquierdo && !personajeEnLadoDerecho && !escenarioTopeDerecha){
        spriteFondo.move(1,0);
        spriteFrente.move(1,0);
        personaje1.mover(1,0);
        personaje2.mover(1,0);

        for(std::shared_ptr<Animacion>& efecto : efectos){
            efecto->mover(1,0);
        }

    } else
    // Si un personaje se va mucho a la derecha, se mueve todo a la izquierda
    if(personajeEnLadoDerecho && !personajeEnLadoIzquierdo && !escenarioTopeIzquierda){
        spriteFondo.move(-1,0);
        spriteFrente.move(-1,0);
        personaje1.mover(-1,0);
        personaje2.mover(-1,0);

        for(std::shared_ptr<Animacion>& efecto : efectos){
            efecto->mover(-1,0);
        }
    }
}

void Escenario::dibujarFondo(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(spriteFondo,states);
}

void Escenario::dibujarFrente(sf::RenderTarget& target, sf::RenderStates states) const{
    target.draw(spriteFrente,states);
}