#include "Temporizador.hpp"
#include "Constantes.hpp"

Temporizador::Temporizador(const sf::Texture& texturaSprite, const sf::Font& fuenteContador,
                           unsigned int fotogramasPorTick, unsigned int ticksContador) :
spriteFondo(texturaSprite), textoContador(fuenteContador), fotogramasPorTick(fotogramasPorTick), ticksContador(ticksContador)
{
    spriteFondo.setOrigin(sf::Vector2f(spriteFondo.getTextureRect().size) / 2.f);
    spriteFondo.setPosition(POSICION_TEMPORIZADOR);

    // Esto es un poco fumadón pero hace que los numeritos no se vean borrosos
    // (código por cortesía de un guiri de reddit:
    // https://www.reddit.com/r/sfml/comments/ihqij0/how_do_i_use_text_properly_scaling_and_avoiding/)
    sf::Texture& texturaFuente = const_cast<sf::Texture&>(fuenteContador.getTexture(TAMANO_FUENTE_TEMPORIZADOR));
    texturaFuente.setSmooth(false);
    
    textoContador.setFillColor(COLOR_RELLENO_NUMEROS_TEMPORIZADOR);
    textoContador.setCharacterSize(TAMANO_FUENTE_TEMPORIZADOR);
    textoContador.setOutlineColor(COLOR_BORDE_NUMEROS_TEMPORIZADOR);
    textoContador.setOutlineThickness(ANCHURA_BORDE_NUMEROS_TEMPORIZADOR);

    fotogramasRestantes = fotogramasPorTick;
    contadorActual = ticksContador;

    actualizarNumeroContador();
}

void Temporizador::actualizar()
{
    if(contadorActual == 0)
        return;

    fotogramasRestantes--;

    if(fotogramasRestantes == 0)
    {
        fotogramasRestantes = fotogramasPorTick;
        contadorActual--;

        actualizarNumeroContador();
    }
}

void Temporizador::resetear()
{
    fotogramasRestantes = fotogramasPorTick;
    contadorActual = ticksContador;

    actualizarNumeroContador();
}

bool Temporizador::haTerminado()
{
    return contadorActual == 0;
}

void Temporizador::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    target.draw(spriteFondo,states);
    target.draw(textoContador,states);
}

void Temporizador::actualizarNumeroContador()
{
    textoContador.setString(std::to_string(contadorActual));
    // Esto es un poco fumada pero así en resumen estoy pasando el origen del texto y su posición
    // a números enteros porque o si no se raya y se ve borroso y feo
    textoContador.setOrigin(sf::Vector2f(sf::Vector2i(textoContador.getLocalBounds().size / 2.f)));
    textoContador.setPosition(sf::Vector2f(sf::Vector2i(spriteFondo.getPosition() + POSICION_TEXTO_TEMPORIZADOR)));
}