#include "Final.h"

Final::Final() {

    //Carga de las texturas y configuracion de los sprites para las pantallas

    texturaPerdiste.loadFromFile("assets/perdiste.png");
    spritePerdiste.setTexture(texturaPerdiste);

    texturaGanaste.loadFromFile("assets/ganaste.png");
    spriteGanaste.setTexture(texturaGanaste);
}