#include "Final.h"
#include "Gameplay.h"
#include "Inicio.h"
#include "Juego.h"
#include "Mira.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <random>

Juego::Juego() {
}

Juego::~Juego() {
}

void Juego::Go() {
    // Crear ventana principal del juego
    sf::RenderWindow App(sf::VideoMode(1280, 720), "La cupula de Hierro");
    App.setMouseCursorVisible(false);  // Ocultar el cursor del ratón en la ventana

    // Crear tres objetos MisilEnemigo en posiciones específicas
    MisilEnemigo misil_1(1200, -300);
    MisilEnemigo misil_2(1300, -200);
    MisilEnemigo misil_3(1400, -500);

    // Limitar la tasa de fotogramas a 60 FPS
    App.setFramerateLimit(60);

    // Cargar la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("gameplay.png")) {  // Cargar la textura desde el archivo gameplay.png
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return;
    }
    sf::Sprite gameplaySprite(gameplayTexture);  // Crear un sprite con la textura cargada

    // Crear objeto Mira y cargar su textura (mira.png)
    sf::Texture miraTexture;
    if (!miraTexture.loadFromFile("mira.png")) {  // Cargar la textura de la mira desde el archivo mira.png
        std::cerr << "Error al cargar la textura de la mira (mira.png)" << std::endl;
        return;
    }
    Mira mira(miraTexture);  // Crear un objeto Mira con la textura cargada

    // Variables de control del juego
    bool juegoTerminado = false;

    // Bucle principal del juego
    while (App.isOpen())  // Mientras la ventana esté abierta
    {
        sf::Event evt;
        while (App.pollEvent(evt)) {  // Manejar eventos de la ventana
            // Procesar eventos
            switch (evt.type) {
                // Si se cerró la ventana
            case sf::Event::Closed:
                App.close();
                break;
                // Si se movió el mouse
            case sf::Event::MouseMoved:
                mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);  // Actualizar la posición de la mira con la posición del ratón
                break;
            }
            if (evt.mouseButton.button == sf::Mouse::Left) {
                // Verificar si se hizo clic izquierdo sobre misil_1
                if (misil_1.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    puntos += 10;
                    // Generar coordenadas aleatorias fuera del rango de la ventana
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distribucionX(App.getSize().x, App.getSize().x + 200);
                    std::uniform_int_distribution<int> distribucionY(App.getSize().y, App.getSize().y + 200);
                    int nuevaX = distribucionX(gen);
                    int nuevaY = distribucionY(gen);
                    misil_1.cambiarPosicion(nuevaX, nuevaY);
                }
            }
            if (evt.mouseButton.button == sf::Mouse::Left) {
                // Verificar si se hizo clic izquierdo sobre misil_1
                if (misil_2.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    puntos += 10;
                    // Generar coordenadas aleatorias fuera del rango de la ventana
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distribucionX(App.getSize().x, App.getSize().x + 200);
                    std::uniform_int_distribution<int> distribucionY(App.getSize().y, App.getSize().y + 200);
                    int nuevaX = distribucionX(gen);
                    int nuevaY = distribucionY(gen);
                    misil_2.cambiarPosicion(nuevaX, nuevaY);
                }

            }
            if (evt.mouseButton.button == sf::Mouse::Left) {
                // Verificar si se hizo clic izquierdo sobre misil_1
                if (misil_3.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    puntos += 10;
                    // Generar coordenadas aleatorias fuera del rango de la ventana
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distribucionX(App.getSize().x, App.getSize().x + 200);
                    std::uniform_int_distribution<int> distribucionY(App.getSize().y, App.getSize().y + 200);
                    int nuevaX = distribucionX(gen);
                    int nuevaY = distribucionY(gen);
                    misil_3.cambiarPosicion(nuevaX, nuevaY);
                }
 
            }

            // Si se presionó la tecla Escape, cerrar la ventana
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                App.close();
        }

        // Actualizar la posición de los misiles enemigos
        misil_1.movimiento();
        misil_2.movimiento();
        misil_3.movimiento();

        // Si un misil sale de la pantalla, se genera una nueva posición aleatoria
        if (misil_1.y > 500) {
            int salidamisil = rand() % 500 + 900;
            misil_1.x = salidamisil;
            misil_1.y = -300;
        }

        if (misil_2.y > 500) {
            int salidamisil = rand() % 500 + 900;
            misil_2.x = salidamisil;
            misil_2.y = -300;
        }

        if (misil_3.y > 500) {
            int salidamisil = rand() % 500 + 900;
            misil_3.x = salidamisil;
            misil_3.y = -300;
        }

        // Limpiar la ventana
        App.clear();

        // Dibujar sprites en la ventana
        App.draw(gameplaySprite);
        App.draw(misil_1.sprite);
        App.draw(misil_2.sprite);
        App.draw(misil_3.sprite);
        mira.draw(App);

        // Mostrar la ventana
        App.display();
    }
}