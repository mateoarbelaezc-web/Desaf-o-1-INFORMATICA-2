#ifndef COMPROBACION_H
#define COMPROBACION_H

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────
// FUNCIÓN: pedirLetra
// Pide al usuario una letra válida para controlar
// el juego. Solo acepta: a, s, d, w, q
// Retorna la letra ingresada
// ─────────────────────────────────────────────
char pedirLetra();

// ─────────────────────────────────────────────
// FUNCIÓN: pedirDimensiones
// Pide al usuario el alto y ancho del tablero.
// Valida que altura sea mayor a 2 y ancho
// sea múltiplo de 8.
// Los valores se guardan en las variables
// pasadas por referencia.
// ─────────────────────────────────────────────
void pedirDimensiones(unsigned int &altura, unsigned int &ancho);

#endif // COMPROBACION_H
