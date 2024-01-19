#pragma once
#include <cstdlib>

class Edificios
{
private:
    int resistencia; // Resistencia del edificio
    int recibeGolpe;

public:
    Edificios();
    void recibirGolpe(int cantidad); // M�todo para simular el golpe al edificio
    bool estaDestruido() const; // M�todo para verificar si el edificio est� destruido

    void setRecibeGolpe(int valor);
    int getRecibeGolpe() const;

    int getResistencia() const; // M�todo para obtener la resistencia actual del edificio
};