#include "VentanaPrincipal.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::CircleShape shape(100.f);
    shape.setOrigin(100.f, 100.f);
    shape.setPosition(150,100);
    shape.setFillColor(sf::Color::Green);

    while (VentanaPrincipal::unicaInstancia()->isOpen())
    {
        sf::Event event;
        while (VentanaPrincipal::unicaInstancia()->pollEvent(event))
        {
            if (event.type == sf::Event::Closed){
                VentanaPrincipal::unicaInstancia()->close();
                return 0;
            }
            else if(event.type == sf::Event::KeyPressed){
                switch(event.key.code){
                case sf::Keyboard::Key::A:
                    VentanaPrincipal::aumentarZoom();
                    break;
                case sf::Keyboard::Key::B:
                    VentanaPrincipal::disminuirZoom();
                    break;
                case sf::Keyboard::Key::Right:
                    shape.move(1,0);
                    break;
                case sf::Keyboard::Key::Left:
                    shape.move(-1,0);
                    break;
                case sf::Keyboard::Key::Up:
                    shape.move(0,-1);
                    break;
                case sf::Keyboard::Key::Down:
                    shape.move(0,1);
                    break;
                default:
                    break;
                }
            }
        }

        VentanaPrincipal::unicaInstancia()->clear();
        VentanaPrincipal::unicaInstancia()->draw(shape);
        VentanaPrincipal::unicaInstancia()->display();
    }

    return 0;
}
