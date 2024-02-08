#include "mira.h"

// Constructor
Mira::Mira(sf::Texture& texture) {
    sprite.setTexture(texture);  // Establecer la textura de la mira
    sprite.setScale(0.4f, 0.4f);  // Tamaño de la mira, setear a gusto
    sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2);  // Establecer el origen en el centro
}


Mira::~Mira() {
}

// Eestablecer la posición
void Mira::setPosition(float x, float y) {
    sprite.setPosition(x, y);
}

// Obtener la posición actual de la mira
sf::Vector2f Mira::getPosition() const {
    return sprite.getPosition();
}

// Dibujar la mira en la ventana
void Mira::draw(sf::RenderWindow& App) {
    App.draw(sprite);
}