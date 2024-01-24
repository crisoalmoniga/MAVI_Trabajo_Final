#include "Final.h"

Final::Final() {

    //Carga de las texturas y configuracion de los sprites para las pantallas

    texturaPerdiste.loadFromFile("perdiste.png");
    spritePerdiste.setTexture(texturaPerdiste);

    texturaGanaste.loadFromFile("ganaste.png");
    spriteGanaste.setTexture(texturaGanaste);
}