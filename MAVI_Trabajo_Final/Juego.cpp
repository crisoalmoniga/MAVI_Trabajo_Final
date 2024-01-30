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
    sf::RenderWindow window(sf::VideoMode(1280, 720), "La cupula de Hierro");

    // Carga de la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("gameplay.png")) {
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return; // Si no se pudo cargar la textura, termina la función
    }

    sf::Sprite gameplaySprite(gameplayTexture);

    // Bucle principal del juego
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            // Eventos de la ventana principal
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        window.draw(gameplaySprite);
        window.display();
    }
}