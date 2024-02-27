#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

    class MisilEnemigo {
    public:
        MisilEnemigo(int _x, int _y);
        int x;
        int y;
        void movimiento();
        void cambiarPosicion(int newX, int newY);
        void setAceleracion(float nuevaAceleracionX, float nuevaAceleracionY);

        sf::Sprite sprite;

    private:
        float velocidadX;
        float velocidadY;
        float aceleracionX;
        float aceleracionY;
        sf::Texture textura;

        void setearTextura();
};