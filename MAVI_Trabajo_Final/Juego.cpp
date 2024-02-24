#include "Final.h"
#include "Gameplay.h"
#include "Inicio.h"
#include "Juego.h"
#include "Mira.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>

Juego::Juego() {
}

Juego::~Juego() {
}

void Juego::Go() {
    // Crear ventana principal del juego
    sf::RenderWindow App(sf::VideoMode(1280, 720), "La cupula de Hierro");
    App.setMouseCursorVisible(false);

    MisilEnemigo misil_1(1200,-300);
    MisilEnemigo misil_2(1300, -200);
    MisilEnemigo misil_3(1400, -500);

    // Limitar la tasa de fotogramas a 60 FPS
    App.setFramerateLimit(60);

    // Cargar la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("gameplay.png")) {
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return;
    }
    sf::Sprite gameplaySprite(gameplayTexture);

    // Crear objeto Mira
    sf::Texture miraTexture;
    if (!miraTexture.loadFromFile("mira.png")) {
        std::cerr << "Error al cargar la textura de la mira (mira.png)" << std::endl;
        return;
    }
    Mira mira(miraTexture);

    // Variables de control del juego
    bool juegoTerminado = false;

    // Bucle principal del juego
    while (App.isOpen())
    {
    sf::Event evt;
    while (App.pollEvent(evt)) {
        // Procesar eventos
        switch (evt.type)
        {
            // Si se cerró la ventana
        case sf::Event::Closed:
            App.close();
            break;
            // Si se movió el mouse
        case sf::Event::MouseMoved:
            mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);
            break;
        }
        // Si se presionó la tecla Escape, cerrar la ventana
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            App.close();
        }

    misil_1.movimiento();
    misil_2.movimiento();
    misil_3.movimiento();

    if (misil_1.y >500)
    {
        int salidamisil = rand() % 500 + 900;
        misil_1.x = salidamisil;
        misil_1.y = -300;
    }

    if (misil_2.y > 500)
    {
        int salidamisil = rand() % 500 + 900;
        misil_2.x = salidamisil;
        misil_2.y = -300;
    }

    if (misil_3.y > 500)
    {
        int salidamisil = rand() % 500 + 900;
        misil_3.x = salidamisil;
        misil_3.y = -300;
    }

    // Limpiar la ventana
    App.clear();

    // Dibujar la pantalla de juego y la mira
    App.draw(gameplaySprite);
    App.draw(misil_1.sprite);
    App.draw(misil_2.sprite);
    App.draw(misil_3.sprite);
    mira.draw(App);

    // Mostrar la ventana
    App.display();
    }
 }