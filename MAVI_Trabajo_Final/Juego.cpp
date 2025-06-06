#include "Final.h"
#include "Gameplay.h"
#include "Inicio.h"
#include "Juego.h"
#include "Mira.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <random>
#include "Bomba.h"


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

    // Todos los proyectiles
    MisilEnemigo misil_1(1300, -300);
    MisilEnemigo misil_2(1300, -200);
    MisilEnemigo misil_3(1400, -500);
    Bomba bomba(100, 0, 4.0f, -6.0f);


    // Limitar la tasa de fotogramas a 60 FPS
    App.setFramerateLimit(60);

    // Cargar la pantalla de juego (gameplay.png)
    sf::Texture gameplayTexture;
    if (!gameplayTexture.loadFromFile("assets/gameplay.png")) {
        std::cerr << "Error al cargar la pantalla de juego (gameplay.png)" << std::endl;
        return;
    }
    sf::Sprite gameplaySprite(gameplayTexture);

    // Cargar la pantalla de menú (menu.png)
    sf::Texture menuTexture;
    if (!menuTexture.loadFromFile("assets/menu.png")) {
        std::cerr << "Error al cargar la pantalla de menú (menu.png)" << std::endl;
        return;
    }
    sf::Sprite menuSprite(menuTexture);

    // Cargar la pantalla de "Perdiste" (perdiste.png)
    sf::Texture perdisteTexture;
    if (!perdisteTexture.loadFromFile("assets/perdiste.png")) {
        std::cerr << "Error al cargar la pantalla de 'Perdiste' (perdiste.png)" << std::endl;
        return;
    }
    sf::Sprite perdisteSprite(perdisteTexture);

    // Cargar la pantalla de "Ganaste" (ganaste.png)
    sf::Texture ganasteTexture;
    if (!ganasteTexture.loadFromFile("assets/ganaste.png")) {
        std::cerr << "Error al cargar la pantalla de 'Ganaste' (ganaste.png)" << std::endl;
        return;
    }
    sf::Sprite ganasteSprite(ganasteTexture);

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
    sf::Sprite explosionSprite(explosionTexture);
    explosionSprite.setScale(0.5f, 0.5f);

    // Cargar la textura de la explosión para clics
    sf::Texture clickExplosionTexture;
    if (!clickExplosionTexture.loadFromFile("assets/click_explosion.png")) {
        std::cerr << "Error al cargar la textura de la explosión para clics (click_explosion.png)" << std::endl;
        return;
    }
    sf::Sprite clickExplosionSprite(clickExplosionTexture);
    clickExplosionSprite.setScale(0.5f, 0.5f);

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
    puntosText.setPosition(10, 10);

    // Crear objeto de texto para mostrar "Vidas"
    sf::Text vidasText;
    vidasText.setFont(fontVidas);
    vidasText.setCharacterSize(29);
    vidasText.setFillColor(sf::Color::Red);
    vidasText.setPosition(10, 50);

    // Crear objeto Mira y cargar su textura (mira.png)
    sf::Texture miraTexture;
    if (!miraTexture.loadFromFile("assets/mira.png")) {
        std::cerr << "Error al cargar la textura de la mira (mira.png)" << std::endl;
        return;
    }
    Mira mira(miraTexture);

    // Cargar y gestionar la música
    sf::Music musicGameplay;
    if (!musicGameplay.openFromFile("assets/mx_gameplay.ogg")) {
        std::cerr << "Error al cargar la música de gameplay (mx_gameplay.ogg)" << std::endl;
        return;
    }

    sf::Music musicMenu;
    if (!musicMenu.openFromFile("assets/mx_menu.ogg")) {
        std::cerr << "Error al cargar la música del menú (mx_menu.ogg)" << std::endl;
        return;
    }

    // Cargar el sonido de la explosión
    sf::SoundBuffer explosionBuffer;
    if (!explosionBuffer.loadFromFile("assets/bomb.ogg")) {
        std::cerr << "Error al cargar el sonido de la explosión (bomb.ogg)" << std::endl;
        return;
    }
    sf::Sound explosionSound;
    explosionSound.setBuffer(explosionBuffer);

    // Variables de control del juego
    bool juegoTerminado = false;
    bool explosionVisible = false;
    bool clickExplosionVisible = false;
    sf::Clock explosionClock;
    sf::Clock clickExplosionClock;

    // Estado del juego
    enum EstadoJuego { MENU, JUGANDO, PERDISTE, GANASTE };
    EstadoJuego estado = MENU;
    musicMenu.play();

    // Bucle principal del juego
    while (App.isOpen()) {
        sf::Event evt;
        while (App.pollEvent(evt)) {
            switch (evt.type) {
            case sf::Event::Closed:
                App.close();
                break;
            case sf::Event::MouseMoved:
                if (estado == JUGANDO) {
                    mira.setPosition(evt.mouseMove.x, evt.mouseMove.y);
                }
                break;
            case sf::Event::MouseButtonPressed:
                if (estado == MENU) {
                    estado = JUGANDO;
                    musicMenu.stop();
                    musicGameplay.play();
                }
                else if (estado == JUGANDO && evt.mouseButton.button == sf::Mouse::Left) {
                    sf::Vector2f mousePos(evt.mouseButton.x, evt.mouseButton.y);
                    if (misil_1.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 15;
                        clickExplosionSprite.setPosition(misil_1.sprite.getPosition());
                        clickExplosionVisible = true;
                        clickExplosionClock.restart();
                        explosionSound.play();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_1.cambiarPosicion(nuevaX, nuevaY);
                    }
                    else if (misil_2.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 15;
                        clickExplosionSprite.setPosition(misil_2.sprite.getPosition());
                        clickExplosionVisible = true;
                        clickExplosionClock.restart();
                        explosionSound.play();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_2.cambiarPosicion(nuevaX, nuevaY);
                    }
                    else if (misil_3.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 15;
                        clickExplosionSprite.setPosition(misil_3.sprite.getPosition());
                        clickExplosionVisible = true;
                        clickExplosionClock.restart();
                        explosionSound.play();
                        int nuevaX = rand() % (App.getSize().x + 200) + App.getSize().x;
                        int nuevaY = rand() % (App.getSize().y + 200) + App.getSize().y;
                        misil_3.cambiarPosicion(nuevaX, nuevaY);

                    }
                    else if (bomba.sprite.getGlobalBounds().contains(mousePos)) {
                        puntos += 15;
                        clickExplosionSprite.setPosition(bomba.sprite.getPosition());
                        clickExplosionVisible = true;
                        clickExplosionClock.restart();

                        if (explosionSound.getStatus() == sf::Sound::Playing)
                            explosionSound.stop();
                        explosionSound.play();

                        int nuevaX = rand() % 100 + 200;
                        bomba.cambiarPosicion(nuevaX, -300);
                    }


                }
                else if (estado == PERDISTE || estado == GANASTE) {
                    puntos = 0;
                    vitalidad = 100;
                    misil_1.cambiarPosicion(1300, -300);
                    misil_2.cambiarPosicion(1300, -200);
                    misil_3.cambiarPosicion(1400, -500);
                    bomba.cambiarPosicion(1400, -500);
                    estado = JUGANDO;
                    musicMenu.stop();
                    musicGameplay.play();
                }
                break;
            case sf::Event::KeyPressed:
                if (estado == PERDISTE || estado == GANASTE) {
                    if (evt.key.code == sf::Keyboard::R) {
                        puntos = 0;
                        vitalidad = 100;
                        misil_1.cambiarPosicion(1300, -300);
                        misil_2.cambiarPosicion(1300, -200);
                        misil_3.cambiarPosicion(1400, -500);
                        bomba.cambiarPosicion(1400, -500);
                        estado = JUGANDO;
                        musicMenu.stop();
                        musicGameplay.play();
                    }
                }
                break;
            }
        }

        if (estado == JUGANDO) {
            misil_1.movimiento();
            misil_2.movimiento();
            misil_3.movimiento();
            bomba.movimiento();


            if (misil_1.sprite.getPosition().y >= 510) {
                vitalidad -= 2;
                explosionSprite.setPosition(misil_1.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                explosionSound.play();
                int salidamisil = rand() % 500 + 900;
                misil_1.cambiarPosicion(salidamisil, -300);
            }
            if (misil_2.sprite.getPosition().y >= 510) {
                vitalidad -= 2;
                explosionSprite.setPosition(misil_2.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                explosionSound.play();
                int salidamisil = rand() % 500 + 900;
                misil_2.cambiarPosicion(salidamisil, -300);
            }
            if (misil_3.sprite.getPosition().y >= 510) {
                vitalidad -= 2;
                explosionSprite.setPosition(misil_3.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();
                explosionSound.play();
                int salidamisil = rand() % 500 + 900;
                misil_3.cambiarPosicion(salidamisil, -300);
            }

            if (bomba.sprite.getPosition().y >= 510) {
                vitalidad -= 2;
                explosionSprite.setPosition(bomba.sprite.getPosition());
                explosionVisible = true;
                explosionClock.restart();

                if (explosionSound.getStatus() == sf::Sound::Playing)
                    explosionSound.stop();
                explosionSound.play();

                int nuevaX = rand() % 100 + 200;
                bomba.cambiarPosicion(nuevaX, -300);
            }



            puntosText.setString("Puntos: " + std::to_string(puntos));
            vidasText.setString("Energía disponible: " + std::to_string(vitalidad) + "%");

            if (vitalidad <= 0) {
                estado = PERDISTE;
                musicGameplay.stop();
                musicMenu.play();
            }
            if (puntos >= 500) {
                estado = GANASTE;
                musicGameplay.stop();
                musicMenu.play();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            App.close();

        App.clear();

        if (estado == MENU) {
            App.draw(menuSprite);
        }
        else if (estado == JUGANDO) {
            App.draw(gameplaySprite);
            App.draw(misil_1.sprite);
            App.draw(misil_2.sprite);
            App.draw(misil_3.sprite);
            bomba.draw(App);
            if (explosionVisible && explosionClock.getElapsedTime().asSeconds() < 0.5f) {
                App.draw(explosionSprite);
            }
            else {
                explosionVisible = false;
            }
            if (clickExplosionVisible && clickExplosionClock.getElapsedTime().asSeconds() < 0.5f) {
                App.draw(clickExplosionSprite);
            }
            else {
                clickExplosionVisible = false;
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

        App.display();
    }
}
