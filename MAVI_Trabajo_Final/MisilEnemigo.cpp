#include "MisilEnemigo.h"
#include <random>

MisilEnemigo::MisilEnemigo(sf::Texture& textureMisilEnemigo, const std::vector<sf::Vector2f>& posiciones)
    : textureMisilEnemigo(textureMisilEnemigo), posiciones(posiciones) {
    // Configurar la textura del MisilEnemigo
    sprite.setTexture(textureMisilEnemigo);

    // Asegurarse de que el vector de posiciones no est� vac�o
    if (!posiciones.empty()) {
        // Establecer la posici�n inicial aleatoria entre las posiciones disponibles
        sprite.setPosition(posiciones[std::rand() % posiciones.size()]);
    }
}

void MisilEnemigo::cambiarPosicion() {
    // Cambiar a una nueva posici�n aleatoria
    if (!posiciones.empty()) {
        sprite.setPosition(posiciones[std::rand() % posiciones.size()]);
    }
}  // A�adida la llave de cierre para la funci�n cambiarPosicion()

sf::Sprite MisilEnemigo::getSprite() const {
    return sprite;
}