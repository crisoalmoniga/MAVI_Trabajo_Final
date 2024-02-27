#pragma once
#include <SFML/Graphics.hpp>
#include <iostream> // Agregado para el uso de std::cerr

class MisilEnemigo {
private:
    int velocidadX;
    int velocidadY;
    sf::Texture textura;

    void setearTextura();

public:
    MisilEnemigo(int _x, int _y);

    void movimiento();
    void cambiarPosicion(int newX, int newY);

    sf::Sprite sprite;
    int x;
    int y;
};