#include "Bomba.h"

Bomba::Bomba(float xInicial, float yInicial, float vXInicial, float vYInicial)
    : x(xInicial), y(yInicial), velocidadX(vXInicial), velocidadY(vYInicial), gravedad(0.2f), modoMRUA(false) {
    cargarTextura();
    sprite.setScale(0.5f, 0.5f);
    sprite.setPosition(x, y);
}

void Bomba::cargarTextura() {
    if (!textura.loadFromFile("assets/bomba.png")) {
        std::cerr << "Falta textura de bomba" << std::endl;
    }
    sprite.setTexture(textura);
}

void Bomba::movimiento() {
    if (!modoMRUA && velocidadX <= 1.0f) {
        modoMRUA = true;
    }

    if (modoMRUA) {
        velocidadX = 0;
    }

    velocidadY += gravedad;
    x += velocidadX;
    y += velocidadY;

    sprite.setPosition(x, y);
}


void Bomba::draw(sf::RenderWindow& ventana) {
    ventana.draw(sprite);
}

sf::Vector2f Bomba::getPosicion() const {
    return sprite.getPosition();
}

void Bomba::cambiarPosicion(float newX, float newY) {
    x = newX;
    y = newY;
    velocidadX = 4.0f;
    velocidadY = -6.0f;
    modoMRUA = false;
    sprite.setPosition(x, y);
}
