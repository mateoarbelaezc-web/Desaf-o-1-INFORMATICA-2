#ifndef TABLERO_H
#define TABLERO_H

#include <iostream>
using namespace std;

// ─────────────────────────────────────────────
// VARIABLES GLOBALES DEL TABLERO
//
// Al no poder usar struct, las variables que describen
// el tablero se declaran como punteros y valores globales.
//
// unsigned char** celdas:
//   - Es un puntero a punteros, es decir un arreglo de filas.
//   - Cada fila es un arreglo de bytes (unsigned char).
//   - Cada bit dentro de un byte representa una celda:
//       1 = ocupada, 0 = libre
//
// Ejemplo visual con ancho=16 (2 bytes por fila):
//   celdas[0] → [ 00000000 | 00000000 ]  ← fila 0, 16 celdas vacías
//   celdas[1] → [ 11111111 | 11111111 ]  ← fila 1, 16 celdas ocupadas
// ─────────────────────────────────────────────

extern unsigned char** celdas;      // arreglo dinámico de filas del tablero
extern unsigned int    anchoTablero; // número de columnas (siempre múltiplo de 8)
extern unsigned int    altoTablero;  // número de filas
extern unsigned int    bytesPorFila; // = anchoTablero / 8

// ─────────────────────────────────────────────
// FUNCIONES DEL TABLERO
// ─────────────────────────────────────────────

// Pide ancho y alto al usuario, valida e inicializa
// toda la memoria dinámica del tablero en 0
void inicializarTablero();

// Libera toda la memoria dinámica reservada para el tablero
void liberarTablero();

// Retorna 1 si la celda (col, fila) está ocupada, 0 si está libre.
// Funciona calculando en qué byte cae la columna (col / 8)
// y qué bit dentro de ese byte (col % 8), luego aplica una máscara con &
unsigned char obtenerCelda(unsigned int col, unsigned int fila);

// Pone en 1 el bit de la celda (col, fila) usando una máscara con OR |
void setCelda(unsigned int col, unsigned int fila);

// Pone en 0 el bit de la celda (col, fila)
// usando una máscara con AND & y complemento ~
void limpiarCelda(unsigned int col, unsigned int fila);

// Retorna 1 si todos los bits de la fila están en 1.
// Una fila completa tiene todos sus bytes en 0xFF (11111111 en binario)
unsigned char filaCompleta(unsigned int fila);

// Elimina la fila indicada, mueve todas las filas
// superiores una posición hacia abajo usando los punteros,
// y crea una nueva fila vacía en la parte superior
void eliminarFila(unsigned int fila);

// Recorre todas las filas del tablero,
// elimina las completas y retorna cuántas eliminó
unsigned char limpiarFilasCompletas();

// Imprime el tablero en consola fila por fila,
// bit por bit: '#' si el bit es 1, '.' si es 0
void imprimirTablero();

#endif // TABLERO_H
