#ifndef PIEZAS_H
#define PIEZAS_H

#include <iostream>
#include <cstdlib>
#include <ctime>
#include "tablero.h"

using namespace std;

// ─────────────────────────────────────────────
// CONSTANTES DE LAS PIEZAS
//
// Cada pieza tiene un número identificador:
//   0 = I
//   1 = O
//   2 = S
//   3 = Z
//   4 = L
//
// MAX_CAJA = 4 porque la pieza I necesita
// una caja de 4x4, que es la más grande.
// Todas las piezas usan este mismo tamaño
// de arreglo para simplificar el manejo.
// ─────────────────────────────────────────────
const int NUM_PIEZAS = 5;
const int MAX_CAJA   = 4;

// ─────────────────────────────────────────────
// VARIABLES GLOBALES DE LA PIEZA ACTUAL
//
// piezaActual: arreglo de MAX_CAJA filas,
//   cada fila es un unsigned char que representa
//   los bits ocupados de esa fila de la pieza.
//
// tamanioCaja: tamaño real de la caja de la
//   pieza actual (2 para O, 3 para S/Z/L, 4 para I)
//
// tipoPieza: índice de la pieza (0 al 4)
//
// colPieza: columna del tablero donde está
//   ubicada la esquina superior izquierda
//   de la caja de la pieza
//
// filaPieza: fila del tablero donde está
//   ubicada la esquina superior izquierda
//   de la caja de la pieza
// ─────────────────────────────────────────────
extern unsigned char piezaActual[MAX_CAJA];
extern unsigned int  tamanioCaja;
extern unsigned int  tipoPieza;
extern int           colPieza;
extern int           filaPieza;

// ─────────────────────────────────────────────
// FUNCIONES DE LAS PIEZAS
// ─────────────────────────────────────────────

// Inicializa la semilla de aleatoriedad.
// Debe llamarse UNA SOLA VEZ al inicio del programa.
void inicializarAleatorio();

// Genera una pieza aleatoria, carga sus bits
// en piezaActual y la coloca en la parte superior
// central del tablero mostrando solo la primera
// fila visible
void generarPieza();

#endif // PIEZAS_H
