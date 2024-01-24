#pragma once
#include <SFML/Graphics.hpp>

class MisilEnemigo
{
public:
    // Constructor de la clase
    MisilEnemigo(sf::Texture& textureMisilEnemigo, sf::Vector2f posiciones[]);

    // M�todo para cambiar la posici�n
    void cambiarPosicion();

    // M�todo para obtener el sprite del misil enemigo
    sf::Sprite getSprite() const;

private:
    sf::Sprite sprite;
    sf::Vector2f* posiciones;
    sf::Texture& textureMisilEnemigo;
};

