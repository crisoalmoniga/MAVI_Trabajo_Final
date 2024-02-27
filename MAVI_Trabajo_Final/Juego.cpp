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
    MisilEnemigo misil_1(1300, -300);
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

    // Crear fuente de texto para mostrar los puntos
    sf::Font font;
    if (!font.loadFromFile("military_font_7.ttf")) {
        std::cerr << "Error al cargar la fuente de texto" << std::endl;
        return;
    }

    // Crear objeto de texto para mostrar los puntos
    sf::Text puntosText;
    puntosText.setFont(font);
    puntosText.setCharacterSize(29);
    puntosText.setFillColor(sf::Color::Green);
    puntosText.setPosition(10, 10); // Posición en la esquina superior izquierda


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
                    // Obtener la nueva posición X
                    int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                    // Obtener la nueva posición Y
                    int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                    // Llamar al método cambiarPosicion() para actualizar la posición del misil
                    misil_1.cambiarPosicion(nuevaX, nuevaY);
                }

            }
            if (evt.mouseButton.button == sf::Mouse::Left) {
                // Verificar si se hizo clic izquierdo sobre misil_1
                if (misil_2.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    puntos += 10;
                    // Generar coordenadas aleatorias fuera del rango de la ventana
                    // Obtener la nueva posición X
                    int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                    // Obtener la nueva posición Y
                    int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                    // Llamar al método cambiarPosicion() para actualizar la posición del misil
                    misil_2.cambiarPosicion(nuevaX, nuevaY);
                }

            }
            if (evt.mouseButton.button == sf::Mouse::Left) {
                // Verificar si se hizo clic izquierdo sobre misil_1
                if (misil_3.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                    puntos += 10;
                    // Generar coordenadas aleatorias fuera del rango de la ventana
                    // Obtener la nueva posición X
                    int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                    // Obtener la nueva posición Y
                    int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                    // Llamar al método cambiarPosicion() para actualizar la posición del misil
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

        // Actualizar el texto de los puntos
        puntosText.setString("Puntos: " + std::to_string(puntos));

        // Limpiar la ventana
        App.clear();

        // Dibujar sprites en la ventana
        App.draw(gameplaySprite);
        App.draw(misil_1.sprite);
        App.draw(misil_2.sprite);
        App.draw(misil_3.sprite);
        mira.draw(App);
        App.draw(puntosText);

        // Mostrar la ventana
        App.display();
    }
}