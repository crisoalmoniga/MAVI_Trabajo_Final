#include "Inicio.h"

Inicio::Inicio() {

    //Carga de las texturas y configuracion de los sprites para las pantallas
    texturaInicio.loadFromFile("inicio.png");
    spriteInicio.setTexture(texturaInicio);

}