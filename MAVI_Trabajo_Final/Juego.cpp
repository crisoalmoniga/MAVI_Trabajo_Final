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
    App.setMouseCursorVisible(false);  // Ocultar el cursor del rat�n en la ventana

    // Restablecer la variable para el pr�ximo ciclo
    bool vidaRestada = false;

    // Crear tres objetos MisilEnemigo en posiciones espec�ficas
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

    // Crear fuentes de texto para mostrar los puntos y Vidas
    sf::Font font;
    if (!font.loadFromFile("military_font_7.ttf")) {
        std::cerr << "Error al cargar la fuente de texto" << std::endl;
        return;
    }

    sf::Font fontVidas;
    if (!fontVidas.loadFromFile("military_font_7.ttf")) {
        std::cerr << "Error al cargar la fuente de texto para las vidas" << std::endl;
        return;
    }

    // Crear objeto de texto para mostrar los puntos
    sf::Text puntosText;
    puntosText.setFont(font);
    puntosText.setCharacterSize(29);
    puntosText.setFillColor(sf::Color::Green);
    puntosText.setPosition(10, 10); // Posici�n en la esquina superior izquierda

    // Crear objeto de texto para mostrar "Vidas"
    sf::Text vidasText;
    vidasText.setFont(fontVidas);
    vidasText.setCharacterSize(29);
    vidasText.setFillColor(sf::Color::Red);
    vidasText.setPosition(10, 50); // Posici�n debajo del texto de los puntos

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
    while (App.isOpen()) {  // Mientras la ventana est� abierta
        sf::Event evt;
        while (App.pollEvent(evt)) {  // Manejar eventos de la ventana
            // Procesar eventos
            switch (evt.type) {
                // Si se cerr� la ventana
            case sf::Event::Closed:
                App.close();
                break;
                // Si se movi� el mouse
            case sf::Event::MouseMoved:
                mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);  // Actualizar la posici�n de la mira con la posici�n del rat�n
                break;
            }

            // Restar una vida si un misil alcanza la posici�n 500 y no se ha restado ya una vida en este ciclo
            if ((misil_1.y >= 500 || misil_2.y >= 500 || misil_3.y >= 500) && !vidaRestada) {
                // Restar una vida
                vitalidad--;
                // Marcar que se ha restado una vida en este ciclo
                vidaRestada = true;
            }
        }

        if (evt.mouseButton.button == sf::Mouse::Left) {
            // Verificar si se hizo clic izquierdo sobre misil_1
            if (misil_1.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                puntos += 10;
                // Generar coordenadas aleatorias fuera del rango de la ventana
                // Obtener la nueva posici�n X
                int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                // Obtener la nueva posici�n Y
                int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                // Llamar al m�todo cambiarPosicion() para actualizar la posici�n del misil
                misil_1.cambiarPosicion(nuevaX, nuevaY);
            }
            else if (misil_2.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                puntos += 10;
                // Generar coordenadas aleatorias fuera del rango de la ventana
                // Obtener la nueva posici�n X
                int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                // Obtener la nueva posici�n Y
                int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                // Llamar al m�todo cambiarPosicion() para actualizar la posici�n del misil
                misil_2.cambiarPosicion(nuevaX, nuevaY);
            }
            else if (misil_3.sprite.getGlobalBounds().contains(sf::Vector2f(evt.mouseButton.x, evt.mouseButton.y))) {
                puntos += 10;
                // Generar coordenadas aleatorias fuera del rango de la ventana
                // Obtener la nueva posici�n X
                int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                // Obtener la nueva posici�n Y
                int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                // Llamar al m�todo cambiarPosicion() para actualizar la posici�n del misil
                misil_3.cambiarPosicion(nuevaX, nuevaY);
            }
        }

        // Si se presion� la tecla Escape, cerrar la ventana
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            App.close();

        // Actualizar la posici�n de los misiles enemigos
        misil_1.movimiento();
        misil_2.movimiento();
        misil_3.movimiento();

        // Verificar si un misil ha llegado a la posici�n 500
        if (misil_1.y >= 500 || misil_2.y >= 500 || misil_3.y >= 500) {
            // Restar una vida
            vitalidad--;
        }

        // Si un misil sale de la pantalla, se genera una nueva posici�n aleatoria
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

        // Actualizar el texto de las vidas
        vidasText.setString("Vitalidad: " + std::to_string(vitalidad) + "%");

        if (vitalidad <= 0 || puntos >= 1000) {
            // Cerrar la ventana
            App.close();
            // Salir del bucle
            break;
        }
        // Dibujar sprites en la ventana
        App.draw(gameplaySprite);
        App.draw(misil_1.sprite);
        App.draw(misil_2.sprite);
        App.draw(misil_3.sprite);
        mira.draw(App);
        App.draw(puntosText);
        App.draw(vidasText);

        // Mostrar la ventana
        App.display();

    }
}