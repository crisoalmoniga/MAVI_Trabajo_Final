#include "MisilEnemigo.h"
#include <cstdlib>

// Constructor de la clase MisilEnemigo
MisilEnemigo::MisilEnemigo(sf::Texture& textureMisilEnemigo, sf::Vector2f posiciones[])
	: textureMisilEnemigo(textureMisilEnemigo), posiciones(posiciones) {
	// Configurar la textura del MisilEnemigo
	sprite.setTexture(textureMisilEnemigo);
	// Establecer la posici�n inicial aleatoria entre las posiciones disponibles
	sprite.setPosition(this->posiciones[rand() % 6]);
}

// M�todo para cambiar la posici�n de manera aleatoria
void MisilEnemigo::cambiarPosicion() {
	// Cambiar a una nueva posici�n aleatoria
	sprite.setPosition(posiciones[rand() % 6]);

	// Cambiar a una nueva textura aleatoria
	sprite.setTexture((rand() % 2 == 0) ? textureMisilEnemigo);
}

// M�todo para obtener el sprite del enemigo/inocente
sf::Sprite MisilEnemigo::getSprite() const {
	return sprite;
}