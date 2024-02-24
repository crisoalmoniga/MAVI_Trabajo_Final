#pragma once
#include <SFML/Graphics.hpp>

class MisilEnemigo
{

	int velocidadX;
	int velocidadY;
	void setearTextura();
	sf::Texture textura;

public:
	MisilEnemigo(int _x, int _y);

	void movimiento();
	sf::Sprite sprite;
	int x;
	int y;

};