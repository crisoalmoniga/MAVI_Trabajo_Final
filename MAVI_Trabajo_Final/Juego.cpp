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
    juegoIniciado = false;
    puntos = 0;
    vidas = 3; // Ajusta según tus necesidades
    misilesenemigosDerribados = 0;
}

Juego::~Juego() {
    // Libera recursos aquí si es necesario
}

void Juego::Go() {

    Inicio inicio;
    Final final;
    Gameplay gameplay;

    sf::RenderWindow window(sf::VideoMode(1024, 768), "La cupula de Hierro");

    sf::Font fuente;
    if (!fuente.loadFromFile("EncodeSans-VariableFont_wdth,wght.ttf")) {
        std::cout << "Error al cargar la fuente." << std::endl;
        // Puedes decidir si quieres salir del juego en caso de un error al cargar la fuente
    }

    sf::Texture enemigoTexture;
    sf::Texture miraTexture;
    sf::Texture misilenemigoTexture;

    if (!enemigoTexture.loadFromFile("misilenemigo.png") || !miraTexture.loadFromFile("mira.png")) {
        std::cout << "Falta textura" << std::endl;
        // Puedes decidir si quieres salir del juego en caso de un error al cargar las texturas
    }

    Mira mira(miraTexture);

    sf::Clock tiempoEnPantalla;
    float tiempoLimite = 2.5f;

    srand(static_cast<unsigned int>(time(0)));

    MisilEnemigo misilenemigo(misilenemigoTexture, posiciones);

    bool juegoTerminado = false;
    sf::Clock tiempoPantallaFinal;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                sf::Vector2f worldPosition = window.mapPixelToCoords(mousePosition);

                if (!juegoIniciado) {
                    juegoIniciado = true;
                }

                if (misilenemigo.getSprite().getGlobalBounds().contains(worldPosition)) {
                    if (misilenemigo.getSprite().getTexture() == &misilenemigoTexture) {
                        puntos += 10;
                        misilesenemigosDerribados++;
                        misilenemigo.cambiarPosicion();
                        tiempoEnPantalla.restart();
                    }
                    else {
                        vidas--;
                        misilenemigo.cambiarPosicion();
                        tiempoEnPantalla.restart();
                    }
                }
            }
        }

        sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
        mira.setPosition(static_cast<float>(mousePosition.x), static_cast<float>(mousePosition.y));

        if (tiempoEnPantalla.getElapsedTime().asSeconds() > tiempoLimite) {
            if (misilenemigo.getSprite().getTexture() == &enemigoTexture) {
                vidas--;
            }

            misilenemigo.cambiarPosicion();
            tiempoEnPantalla.restart();
        }

        sf::Text textoVidas("Vidas: " + std::to_string(vidas), fuente, 30);
        textoVidas.setPosition(40, 710);

        sf::Text textoMisilesEnemigosDerribados("Misiles derribados: " + std::to_string(misilesenemigosDerribados), fuente, 30);
        textoMisilesEnemigosDerribados.setPosition(730, 710);

        sf::Text textoPuntaje("Puntaje: " + std::to_string(puntos), fuente, 30);
        textoPuntaje.setPosition(460, 710);

        window.clear();

        if (!juegoIniciado) {
            window.draw(inicio.spriteInicio);
        }

        if (juegoIniciado) {
            window.draw(misilenemigo.getSprite());
            // Si gameplay es un objeto de la clase Gameplay, deberías tener una instancia de esta clase aquí
            window.draw(gameplay.spriteFondo);
            mira.draw(window);

            window.draw(textoPuntaje);
            window.draw(textoVidas);
            window.draw(textoMisilesEnemigosDerribados);

            if (misilesenemigosDerribados >= 10) {
                // Si Final es un objeto de la clase Final, deberías tener una instancia de esta clase aquí
                window.draw(final.spriteGanaste);
            }
            else if (vidas <= 0) {
                window.draw(final.spritePerdiste);
            }
        }

        window.display();

        if (vidas <= 0 || misilesenemigosDerribados >= 10) {
            if (!juegoTerminado) {
                tiempoPantallaFinal.restart();
                juegoTerminado = true;
            }

            if (misilesenemigosDerribados >= 10) {
                // Si Final es un objeto de la clase Final, deberías tener una instancia de esta clase aquí
                window.draw(final.spriteGanaste);
            }
            else if (vidas <= 0) {
                window.draw(final.spritePerdiste);
            }

            if (tiempoPantallaFinal.getElapsedTime().asSeconds() > 10.0f) {
                window.close();
            }
        }
    }
}