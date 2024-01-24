#include "Juego.h"

//Me tomé la licencia de hacer una versión del shooter, faltan muchas cosas como poder reiniciar el juego y agregar animaciones, las cuales no llego a armar.

// Los assets fueron creados con photoshop, la fuente utilizada es de la familia "EncodeSans-VariableFont_wdth,wght", la cual es propia de la marca "Argentina" y se puede
// descargar libremente de la página de Nacion.
// 
// Con respecto a la ayuda recibida, en la lógica de Spawneo tuve que ayudarme con videos de youtube y chat gpt ya que es lo que no podia hacer que funcione bien.
// 
// Tengo un gran bug, el contador de los sprites comienza a funcionar con la pantalla de inicio, 
// por lo que debería cambiar la lógica de ese contador pero no llego con el tiempo a modificarlo
//La solución que pensé momentáneamente es incrementar la cantidad de vidas para que mientras se leen las instrucciones no se pierdan vidas

int main() {

    Juego juego;
    juego.Go();

    return 0;
}