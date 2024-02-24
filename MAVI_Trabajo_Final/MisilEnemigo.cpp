#include "MisilEnemigo.h"

MisilEnemigo::MisilEnemigo(int _x, int _y) {
	x = _x;
	y = _y;
	velocidadX = -4;
	velocidadY = 4;
	setearTextura();
	sprite.scale(0.8, 0.8);
}

void MisilEnemigo::setearTextura() {
	if (!textura.loadFromFile("misilenemigo.png"))
		printf("Falta textura misil");
	sprite.setTexture(textura);
}

void MisilEnemigo::movimiento() {
	x += velocidadX;
	y += velocidadY;
	sprite.setPosition(x, y);
}