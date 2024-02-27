#include "MisilEnemigo.h"

MisilEnemigo::MisilEnemigo(int _x, int _y) {
    x = _x;
    y = _y;
    velocidadX = -4;
    velocidadY = 4;
    setearTextura();
    sprite.setScale(0.8f, 0.8f); // Corregido: Usar sprite.setScale en lugar de sprite.scale
}

void MisilEnemigo::setearTextura() {
    if (!textura.loadFromFile("misilenemigo.png")) // Corregido: Comprobar si la carga de la textura falla
        std::cerr << "Falta textura misil" << std::endl; // Corregido: Mostrar un mensaje de error en la salida estándar de error
    sprite.setTexture(textura);
}

void MisilEnemigo::movimiento() {
    x += velocidadX;
    y += velocidadY;
    sprite.setPosition(x, y);
}

void MisilEnemigo::cambiarPosicion(int newX, int newY) {
    x = newX;
    y = newY;
    sprite.setPosition(x, y);
}