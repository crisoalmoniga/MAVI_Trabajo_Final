#include "MisilEnemigo.h"

MisilEnemigo::MisilEnemigo(int _x, int _y) {
    x = _x;
    y = _y;
    velocidadX = -4;
    velocidadY = 4;
    aceleracionX = 0;
    aceleracionY = 0.001f;
    setearTextura();
    sprite.setScale(0.8f, 0.8f);
}

void MisilEnemigo::setearTextura() {
    if (!textura.loadFromFile("misilenemigo.png")) {
        std::cerr << "Falta textura misil" << std::endl;
    }
    sprite.setTexture(textura);
}

void MisilEnemigo::movimiento() {
    velocidadX += aceleracionX;
    velocidadY += aceleracionY;
    x += velocidadX;
    y += velocidadY;
    sprite.setPosition(x, y);
}

void MisilEnemigo::cambiarPosicion(int newX, int newY) {
    x = newX;
    y = newY;
    sprite.setPosition(x, y);
}

void MisilEnemigo::setAceleracion(float nuevaAceleracionX, float nuevaAceleracionY) {
    aceleracionX = nuevaAceleracionX;
    aceleracionY = nuevaAceleracionY;
}