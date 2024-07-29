#ifndef __ANIMACION_CON_GRAVEDAD_HPP__
#define __ANIMACION_CON_GRAVEDAD_HPP__

#include "Animacion.hpp"

/*
    Esta clase representa animaciones que caen con gravedad y rebotan con las paredes
*/
class AnimacionConGravedad : public Animacion
{
private:
    // Hitbox del objeto (como va a girar es bueno que tenga solo una,
    // y que sea lo más cuadrada y centrada posible)
    Hitbox hitbox;

    // Velocidad del objeto volador
    sf::Vector2f velocidad;

    // Velocidad de giro del objeto volador en grados sexagesimales por frame
    double velocidadGiro;

    // Indica si el objeto se ha chocado, por lo que empieza a parpadear y tal
    bool haChocado;

    // Se va sumando 1 por cada frame que pase desde que el objeto se choca contra algo,
    // permitiendo que parpadee y finalmente desaparezca.
    int contadorParpadeo;

public:
    // Constructor que crea una animación con gravedad en base a una textura para el sprite, una posición inicial y una velocidad
    AnimacionConGravedad(sf::Texture &textura, Hitbox hitbox, sf::Vector2f posicion, sf::Vector2f velocidad, double velocidadGiro);

    // Constructor igual al anterior pero también le mete sonido
    AnimacionConGravedad(sf::Texture &textura, Hitbox hitbox, sf::Vector2f posicion, sf::Vector2f velocidad, double velocidadGiro, sf::Sound sonido);

    // Actualiza la animación
    void actualizar(std::list<std::shared_ptr<Animacion>> &nuevasAnimaciones, sf::Vector2f &movimiento);

    // Resetea la animación al estado inicial
    void resetear();

    // Devuelve una lista con las hitboxes
    std::list<Hitbox> getHitboxes();

    // Determina si una animación ha terminado
    bool haTerminado();

    // Establece la velocidad de movimiento de la animación
    void setVelocidad(sf::Vector2f velocidad);

    // Establece la velocidad de giro de la animación
    void setVelocidadGiro(const double &velocidadGiro);

    // Devuelve un clon de la animación
    std::shared_ptr<Animacion> clonar();

    // Indica a la animación que ha chocado con una hitbox
    void chocar(Hitbox hitbox);

    // Dibuja la animación con gravedad, pudiendo no dibujarla a veces para el efecto
    // de parpadeo al chocarse
    void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif