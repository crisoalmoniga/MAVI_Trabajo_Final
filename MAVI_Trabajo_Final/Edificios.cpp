#include "Edificios.h"
#include <cstdlib>

Edificios::Edificios()
{
    resistencia = rand() % 100 + 1; // Inicializa la resistencia aleatoriamente
    recibeGolpe = 0;
}

void Edificios::recibirGolpe(int cantidad)
{
    resistencia -= cantidad;
    if (resistencia < 0) {
        resistencia = 0; // Ojo, que la resistencia no sea negativa
    }
}

bool Edificios::estaDestruido() const
{
    return resistencia <= 0;
}

void Edificios::setRecibeGolpe(int valor)
{
    recibeGolpe = valor;
}

int Edificios::getRecibeGolpe() const
{
    return recibeGolpe;
}

int Edificios::getResistencia() const
{
    return resistencia;
}