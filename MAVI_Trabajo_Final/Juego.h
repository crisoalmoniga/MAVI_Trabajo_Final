#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "MisilEnemigo.h"

class Juego
{
public:
    int posicion = 500;
    int puntos = 0;
    int vitalidad = 100;
    int misilesenemigosDerribados = 0;
    sf::Vector2f posiciones[6];
    sf::Texture textureMisilEnemigo;
    sf::Texture miraTexture;
    bool juegoIniciado = false;


    Juego();
    ~Juego();
    void Go();

private:
    sf::RenderWindow App;
};