#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Bomba {
public:
    Bomba(float xInicial, float yInicial, float vXInicial, float vYInicial);
    void movimiento();
    void draw(sf::RenderWindow& ventana);
    void cambiarPosicion(float newX, float newY);


    sf::Vector2f getPosicion() const;

    sf::Sprite sprite;

private:
    float x, y;
    float velocidadX, velocidadY;
    float gravedad;
    sf::Texture textura;
    bool modoMRUA;

    void cargarTextura();
};