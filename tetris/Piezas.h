#ifndef PIEZAS_H
#define PIEZAS_H

#include "tablero.h"

// ─────────────────────────────────────────────
// CONSTANTES DE LAS PIEZAS
// ─────────────────────────────────────────────
const int NUM_PIEZAS = 5;
const int MAX_CAJA   = 4;

// ─────────────────────────────────────────────
// VARIABLES GLOBALES DE LA PIEZA ACTUAL
// ─────────────────────────────────────────────
extern unsigned char piezaActual[MAX_CAJA];
extern unsigned int  tamanioCaja;
extern unsigned int  tipoPieza;
extern int           colPieza;
extern int           filaPieza;

// ─────────────────────────────────────────────
// FUNCIONES DE LAS PIEZAS
// ─────────────────────────────────────────────
void generarPieza();
int bajarPieza();
int moverPieza(int direccion);
void borrarPiezaTablero();
void dibujarPiezaTablero();
extern bool gameOver;

#endif // PIEZAS_H
