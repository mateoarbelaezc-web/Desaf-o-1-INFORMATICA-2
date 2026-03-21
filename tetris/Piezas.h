#ifndef PIEZAS_H
#define PIEZAS_H

#include "tablero.h"

const int NUM_PIEZAS = 5;
const int MAX_CAJA   = 4;

extern unsigned char piezaActual[MAX_CAJA];
extern unsigned int  tamanioCaja;
extern unsigned int  tipoPieza;
extern int           colPieza;
extern int           filaPieza;

void generarPieza();
int bajarPieza();
int moverPieza(int direccion);
void borrarPiezaTablero();
void dibujarPiezaTablero();
extern bool gameOver;

#endif
