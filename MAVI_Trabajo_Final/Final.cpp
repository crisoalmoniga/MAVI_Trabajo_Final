#include "Final.h"

Final::Final() {

    texturaPerdiste.loadFromFile("assets/perdiste.png");
    spritePerdiste.setTexture(texturaPerdiste);

    texturaGanaste.loadFromFile("assets/ganaste.png");
    spriteGanaste.setTexture(texturaGanaste);
}