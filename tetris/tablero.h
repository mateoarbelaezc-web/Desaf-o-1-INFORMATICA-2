#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
using namespace std;

extern unsigned char** celdas;
extern unsigned int    anchoTablero;
extern unsigned int    altoTablero;
extern unsigned int    bytesPorFila;
void inicializarTablero();
void liberarTablero();
unsigned char obtenerCelda(unsigned int col, unsigned int fila);
void setCelda(unsigned int col, unsigned int fila);
void limpiarCelda(unsigned int col, unsigned int fila);
unsigned char filaCompleta(unsigned int fila);
void eliminarFila(unsigned int fila);
unsigned char limpiarFilasCompletas();
void imprimirTablero();

#endif
