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

    // Inicializar variables de juego
    int puntos = 0;
    int vitalidad = 100;

    // Crear tres objetos MisilEnemigo en posiciones específicas
    MisilEnemigo misil_1(1300, -300);
    MisilEnemigo misil_2(1300, -200);
    MisilEnemigo misil_3(1400, -500);

    // Limitar la tasa de fotogramas a 60 FPS
    App.setFramerateLimit(60);

    // Cargar la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("assets/gameplay.png")) {  // Cargar la textura desde el archivo gameplay.png
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return;
    }
    sf::Sprite gameplaySprite(gameplayTexture);  // Crear un sprite con la textura cargada

    // Cargar la pantalla de menú (menu.png)
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("assets/menu.png")) {  // Cargar la textura desde el archivo menu.png
        std::cerr << "Error al cargar la pantalla de menú (menu.png)" << std::endl;
        return;
    }
    sf::Sprite menuSprite(menuTexture);  // Crear un sprite con la textura cargada

    // Cargar la pantalla de "Perdiste" (perdiste.png)
    sf::Texture perdisteTexture;
    if (!perdisteTexture.loadFromFile("assets/perdiste.png")) {  // Cargar la textura desde el archivo perdiste.png
        std::cerr << "Error al cargar la pantalla de 'Perdiste' (perdiste.png)" << std::endl;
        return;
    }
    sf::Sprite perdisteSprite(perdisteTexture);  // Crear un sprite con la textura cargada

    // Cargar la pantalla de "Ganaste" (ganaste.png)
    sf::Texture ganasteTexture;
    if (!ganasteTexture.loadFromFile("assets/ganaste.png")) {  // Cargar la textura desde el archivo ganaste.png
        std::cerr << "Error al cargar la pantalla de 'Ganaste' (ganaste.png)" << std::endl;
        return;
    }
    sf::Sprite ganasteSprite(ganasteTexture);  // Crear un sprite con la textura cargada

    // Ajustar los sprites a la proporción de la pantalla
    sf::Vector2u windowSize = App.getSize();
    sf::Vector2u textureSize = menuTexture.getSize();

    float scaleX = static_cast<float>(windowSize.x) / textureSize.x;
    float scaleY = static_cast<float>(windowSize.y) / textureSize.y;

    menuSprite.setScale(scaleX, scaleY);
    perdisteSprite.setScale(scaleX, scaleY);
    ganasteSprite.setScale(scaleX, scaleY);

    // Cargar la textura de la explosión
    sf::Texture explosionTexture;
    if (!explosionTexture.loadFromFile("assets/explosion.png")) {
        std::cerr << "Error al cargar la textura de la explosión (explosion.png)" << std::endl;
        return;
    }
    sf::Sprite explosionSprite(explosionTexture);  // Crear un sprite con la textura cargada
    explosionSprite.setScale(0.5f, 0.5f);  // Ajustar el tamaño del sprite de la explosión

    // Crear fuentes de texto para mostrar los puntos y Vidas
    sf::Font font;
    if (!font.loadFromFile("assets/military_font_7.ttf")) {
        std::cerr << "Error al cargar la fuente de texto" << std::endl;
        return;
    }

    sf::Font fontVidas;
    if (!fontVidas.loadFromFile("assets/military_font_7.ttf")) {
        std::cerr << "Error al cargar la fuente de texto para las vidas" << std::endl;
        return;
    }

    // Crear objeto de texto para mostrar los puntos
    sf::Text puntosText;
    puntosText.setFont(font);
    puntosText.setCharacterSize(29);
    puntosText.setFillColor(sf::Color::Green);
    puntosText.setPosition(10, 10); // Posición en la esquina superior izquierda

    // Crear objeto de texto para mostrar "Vidas"
    sf::Text vidasText;
    vidasText.setFont(fontVidas);
    vidasText.setCharacterSize(29);
    vidasText.setFillColor(sf::Color::Red);
    vidasText.setPosition(10, 50); // Posición debajo del texto de los puntos

    // Crear objeto Mira y cargar su textura (mira.png)
    sf::Texture miraTexture;
    if (!miraTexture.loadFromFile("assets/mira.png")) {  // Cargar la textura de la mira desde el archivo mira.png
        std::cerr << "Error al cargar la textura de la mira (mira.png)" << std::endl;
        return;
    }
    Mira mira(miraTexture);  // Crear un objeto Mira con la textura cargada

    // Variables de control del juego
    bool juegoTerminado = false;
    bool explosionVisible = false;  // Para controlar la visibilidad de la explosión
    sf::Clock explosionClock;  // Reloj para controlar la duración de la explosión

    // Estado del juego
    enum EstadoJuego { MENU, JUGANDO, PERDISTE, GANASTE };
    EstadoJuego estado = MENU;

    // Bucle principal del juego
    while (App.isOpen()) {  // Mientras la ventana esté abierta
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
                if (estado == JUGANDO) {
                    mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);  // Actualizar la posición de la mira con la posición del ratón
                }
                break;
                // Si se hizo clic con el mouse
            case sf::Event::MouseButtonPressed:
                if (estado == MENU) {
                    estado = JUGANDO;
                }
                else if (estado == JUGANDO && evt.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(evt.mouseButton.x, evt.mouseButton.y);
                    if (misil_1.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 10;
                        explosionSprite.setPosition(misil_1.sprite.getPosition());
                        explosionVisible = true;
                        explosionClock.restart();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_1.cambiarPosicion(nuevaX, nuevaY);
                    }
                    else if (misil_2.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 10;
                        explosionSprite.setPosition(misil_2.sprite.getPosition());
                        explosionVisible = true;
                        explosionClock.restart();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_2.cambiarPosicion(nuevaX, nuevaY);
                    }
                    else if (misil_3.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 10;
                        explosionSprite.setPosition(misil_3.sprite.getPosition());
                        explosionVisible = true;
                        explosionClock.restart();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_3.cambiarPosicion(nuevaX, nuevaY);
                    }
                }
                else if (estado == PERDISTE || estado == GANASTE) {
                    // Reiniciar el juego al hacer clic
                    puntos = 0;
                    vitalidad = 100;
                    misil_1.cambiarPosicion(1300, -300);
                    misil_2.cambiarPosicion(1300, -200);
                    misil_3.cambiarPosicion(1400, -500);
                    estado = JUGANDO;
                }
                break;
                // Si se presiona una tecla
            case sf::Event::KeyPressed:
                if (estado == PERDISTE || estado == GANASTE) {
                    if (evt.key.code == sf::Keyboard::R) {
                        // Reiniciar el juego
                        puntos = 0;
                        vitalidad = 100;
                        misil_1.cambiarPosicion(1300, -300);
                        misil_2.cambiarPosicion(1300, -200);
                        misil_3.cambiarPosicion(1400, -500);
                        estado = JUGANDO;
                    }
                }
                break;
            }
        }

        if (estado == JUGANDO) {
            // Actualizar la posición de los misiles enemigos
            misil_1.movimiento();
            misil_2.movimiento();
            misil_3.movimiento();

            // Restar una vida si un misil alcanza la posición 500
            if (misil_1.y >= 500) {
                vitalidad--;
                explosionSprite.setPosition(misil_1.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                int salidamisil = rand() % 500 + 900;
                misil_1.x = salidamisil;
                misil_1.y = -300;
                std::cout << "Misil 1 ha explotado. Vitalidad: " << vitalidad << std::endl;
            }
            if (misil_2.y >= 500) {
                vitalidad--;
                explosionSprite.setPosition(misil_2.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                int salidamisil = rand() % 500 + 900;
                misil_2.x = salidamisil;
                misil_2.y = -300;
                std::cout << "Misil 2 ha  explotado. Vitalidad: " << vitalidad << std::endl;
            }
            if (misil_3.y >= 500) {
                vitalidad--;
                explosionSprite.setPosition(misil_3.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                int salidamisil = rand() % 500 + 900;
                misil_3.x = salidamisil;
                misil_3.y = -300;
                std::cout << "Misil 3 ha  explotado. Vitalidad: " << vitalidad << std::endl;
            }

            // Actualizar el texto de los puntos
            puntosText.setString("Puntos: " + std::to_string(puntos));

            // Actualizar el texto de las vidas
            vidasText.setString("Vitalidad: " + std::to_string(vitalidad) + "%");

            if (vitalidad <= 0) {
                estado = PERDISTE;
            }
            if (puntos >= 1000) {
                estado = GANASTE;
            }
        }

        // Si se presionó la tecla Escape, cerrar la ventana
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            App.close();

        // Dibujar sprites en la ventana
        App.clear();

        if (estado == MENU) {
            App.draw(menuSprite);
        }
        else if (estado == JUGANDO) {
            App.draw(gameplaySprite);
            App.draw(misil_1.sprite);
            App.draw(misil_2.sprite);
            App.draw(misil_3.sprite);
            if (explosionVisible && explosionClock.getElapsedTime().asSeconds() < 0.5f) {
                App.draw(explosionSprite);
            }
            else {
                explosionVisible = false;
            }
            mira.draw(App);
            App.draw(puntosText);
            App.draw(vidasText);
        }
        else if (estado == PERDISTE) {
            App.draw(perdisteSprite);
        }
        else if (estado == GANASTE) {
            App.draw(ganasteSprite);
        }

        // Mostrar la ventana
        App.display();
    }
}
