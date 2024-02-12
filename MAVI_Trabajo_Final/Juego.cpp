#include "Final.h"
#include "Gameplay.h"
#include "Inicio.h"
#include "Juego.h"
#include "Mira.h"
#include "MisilEnemigo.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

Juego::Juego() {
}

Juego::~Juego() {
}

void Juego::Go() {
    // Creacion de ventana principal del juego
    sf::RenderWindow App(sf::VideoMode(1280, 720), "La cupula de Hierro");

    /////Ocultamos el cursor del sistema/////
    App.setMouseCursorVisible(false);

    // Carga de la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("gameplay.png")) {
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return; // Si no se pudo cargar la textura, termina la función
    }

    sf::Sprite gameplaySprite(gameplayTexture);

    // Crear objeto Mira
    sf::Texture miraTexture;
    if (!miraTexture.loadFromFile("mira.png")) {
        std::cerr << "Error al cargar la textura de la mira (mira.png)" << std::endl;
        return;
    }
    Mira mira(miraTexture);

    sf::Font fuente;
    if (!fuente.loadFromFile("GAME_glm.ttf")) {
        std::cerr << "Error al cargar la fuente" << std::endl;
        return;
    }

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
            case sf::Event::MouseMoved:
                /////Actualizamos la posición del sprite con/////
                /////la informacion del evento del mouse/////
                mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) //Es evento unbuffered
                App.close();
        }
        App.clear();
        App.draw(gameplaySprite);
        mira.draw(App);
        App.display();
    }
    App.setFramerateLimit(60);
}