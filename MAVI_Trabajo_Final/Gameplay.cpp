#include "Gameplay.h"

Gameplay::Gameplay() {

    //Carga de las texturas y configuracion de los sprites para las pantallas
    texturaFondo.loadFromFile("assets/fondo.png");
    spriteFondo.setTexture(texturaFondo);

}