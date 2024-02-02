#include "Juego.h"
#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <ctime>
#include "MisilEnemigo.h"
#include "Inicio.h"
#include "Gameplay.h"
#include "Final.h"
#include "Mira.h"
#include <iostream>

Juego::Juego() {
}

Juego::~Juego() {
}

void Juego::Go() {
    // Creacion de ventana principal del juego
    sf::RenderWindow App(sf::VideoMode(1280, 720), "La cupula de Hierro");

    // Carga de la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("gameplay.png")) {
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return; // Si no se pudo cargar la textura, termina la función
    }

    sf::Sprite gameplaySprite(gameplayTexture);

    // Bucle principal del juego
    while (App.isOpen())
    {
        sf::Event evt;
        while (App.pollEvent(evt)) {
            /////Procesar eventos//////
            switch (evt.type)
            {
                /////Si se cerro la ventana//////
            case sf::Event::Closed:
                App.close();
                break;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                App.close();
        }
        App.clear();
        App.draw(gameplaySprite);
        App.display();
    }
}