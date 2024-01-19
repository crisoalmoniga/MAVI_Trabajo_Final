#pragma once
#include <cstdlib>

class Edificios
{
private:
    int resistencia; // Resistencia del edificio
    int recibeGolpe;

public:
    Edificios();
    void recibirGolpe(int cantidad); // Método para simular el golpe al edificio
    bool estaDestruido() const; // Método para verificar si el edificio está destruido

    void setRecibeGolpe(int valor);
    int getRecibeGolpe() const;

    int getResistencia() const; // Método para obtener la resistencia actual del edificio
};