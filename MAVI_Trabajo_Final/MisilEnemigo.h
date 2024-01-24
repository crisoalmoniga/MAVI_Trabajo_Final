#pragma once
#include <SFML/Graphics.hpp>

class MisilEnemigo
{
public:
    // Constructor de la clase
    MisilEnemigo(sf::Texture& textureMisilEnemigo, sf::Vector2f posiciones[]);

    // Método para cambiar la posición
    void cambiarPosicion();

    // Método para obtener el sprite del misil enemigo
    sf::Sprite getSprite() const;

private:
    sf::Sprite sprite;
    sf::Vector2f* posiciones;
    sf::Texture& textureMisilEnemigo;
};

