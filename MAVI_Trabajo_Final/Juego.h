#pragma once
#include <SFML/Graphics.hpp>

class Juego
{
public:

	// Variables de puntos, vidas y enemigos muertos
	int puntos = 0;
	int vidas = 9;
	int misilesenemigosDerribados = 0;

	// Posiciones iniciales de enemigos e inocentes
	sf::Vector2f posiciones[6] = {
		sf::Vector2f(135.0f, 310.0f), //arriba izquierda
		sf::Vector2f(135.0f, 535.0f), //abajo izquierda
		sf::Vector2f(480.0f, 565.0f), //puerta principal
		sf::Vector2f(480.0f, 80.0f), //balcon
		sf::Vector2f(830.0f, 535.0f), //abajo derecha
		sf::Vector2f(830.0f, 310.0f) //arriba derecha
	};

	// Carga de texturas
	sf::Texture textureMisilEnemigo;
	sf::Texture miraTexture;


	bool juegoIniciado = false;

	// Constructor y destructor de la clase
	Juego();
	~Juego();

	// Método principal para ejecutar el juego
	void Go();

private:
	sf::RenderWindow App;
};