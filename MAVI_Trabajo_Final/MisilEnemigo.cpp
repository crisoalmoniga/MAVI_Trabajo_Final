#include "MisilEnemigo.h"
#include <random>

MisilEnemigo::MisilEnemigo(sf::Texture& textureMisilEnemigo, const std::vector<sf::Vector2f>& posiciones)
    : textureMisilEnemigo(textureMisilEnemigo), posiciones(posiciones) {
    // Configurar la textura del MisilEnemigo
    sprite.setTexture(textureMisilEnemigo);

    // Asegurarse de que el vector de posiciones no esté vacío
    if (!posiciones.empty()) {
        // Establecer la posición inicial aleatoria entre las posiciones disponibles
        sprite.setPosition(posiciones[std::rand() % posiciones.size()]);
    }
}

void MisilEnemigo::cambiarPosicion() {
    // Cambiar a una nueva posición aleatoria
    if (!posiciones.empty()) {
        sprite.setPosition(posiciones[std::rand() % posiciones.size()]);
    }
}  // Añadida la llave de cierre para la función cambiarPosicion()

sf::Sprite MisilEnemigo::getSprite() const {
    return sprite;
}