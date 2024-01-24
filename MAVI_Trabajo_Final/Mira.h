#pragma once
#include <SFML/Graphics.hpp>

class Mira {
public:

    Mira(sf::Texture& texture);
    ~Mira();

    // Método para establecer la posición de la mira
    void setPosition(float x, float y);

    // Método para obtener la posición actual de la mira
    sf::Vector2f getPosition() const;

    // Método para dibujar la mira en la ventana
    void draw(sf::RenderWindow& window);

private:
    sf::Sprite sprite;  // Objeto sprite para representar la mira en el juego
};