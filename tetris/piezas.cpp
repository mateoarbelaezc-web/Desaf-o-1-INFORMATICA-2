#include "piezas.h"

// ─────────────────────────────────────────────
// DEFINICIÓN DE VARIABLES GLOBALES
// ─────────────────────────────────────────────
unsigned char piezaActual[MAX_CAJA];
unsigned int  tamanioCaja = 0;
unsigned int  tipoPieza   = 0;
int           colPieza    = 0;

// ─────────────────────────────────────────────
// DEFINICIÓN DE LAS 5 PIEZAS EN BITS
//
// Cada pieza es un arreglo de MAX_CAJA filas.
// Cada fila es un unsigned char donde los bits
// de la izquierda representan las celdas ocupadas.
//
// Usamos 0x80 = 10000000 como referencia del
// bit más a la izquierda.
//
// Las piezas se almacenan en un arreglo de dos
// dimensiones: formas[tipoPieza][fila]
// ─────────────────────────────────────────────

// formas[5][MAX_CAJA]:
//   - 5 piezas
//   - MAX_CAJA filas por pieza
//
// Pieza I (caja 4x4):
//   0000 → 00000000
//   1111 → 11110000
//   0000 → 00000000
//   0000 → 00000000
//
// Pieza O (caja 2x2, usamos 4 filas pero solo 2 tienen bits):
//   11 → 11000000
//   11 → 11000000
//   00 → 00000000
//   00 → 00000000
//
// Pieza S (caja 3x3):
//   011 → 01100000
//   110 → 11000000
//   000 → 00000000
//   000 → 00000000
//
// Pieza Z (caja 3x3):
//   110 → 11000000
//   011 → 01100000
//   000 → 00000000
//   000 → 00000000
//
// Pieza L (caja 3x3):
//   100 → 10000000
//   100 → 10000000
//   110 → 11000000
//   000 → 00000000
// ─────────────────────────────────────────────
const unsigned char formas[NUM_PIEZAS][MAX_CAJA] = {
    // Pieza I
    { 0x00, 0xF0, 0x00, 0x00 },
    // Pieza O
    { 0xC0, 0xC0, 0x00, 0x00 },
    // Pieza S
    { 0x60, 0xC0, 0x00, 0x00 },
    // Pieza Z
    { 0xC0, 0x60, 0x00, 0x00 },
    // Pieza L
    { 0x80, 0x80, 0xC0, 0x00 }
};

// ─────────────────────────────────────────────
// tamanos[5]: tamaño real de la caja de cada pieza
//   I → 4, O → 2, S → 3, Z → 3, L → 3
// ─────────────────────────────────────────────
const unsigned int tamanos[NUM_PIEZAS] = { 4, 2, 3, 3, 3 };

// ─────────────────────────────────────────────
// FUNCIÓN: generarPieza
// Se encarga de:
//   1. Elegir aleatoriamente una de las 5 piezas
//   2. Cargar sus bits en piezaActual
//   3. Calcular la columna central del tablero
//   4. Mostrar solo la última fila con bits en 1
//      de la pieza en la fila 0 del tablero
// ─────────────────────────────────────────────
void generarPieza() {

    // ── 1. Elegir pieza aleatoria ──────────────
    // rand() % NUM_PIEZAS genera un número entre
    // 0 y 4, correspondiente a una de las 5 piezas
    tipoPieza   = rand() % NUM_PIEZAS;
    tamanioCaja = tamanos[tipoPieza];

    // ── 2. Cargar bits de la pieza en piezaActual
    // Copiamos las filas de la pieza elegida
    // al arreglo piezaActual para tenerla disponible
    for (unsigned int i = 0; i < MAX_CAJA; i++)
        piezaActual[i] = formas[tipoPieza][i];

    // ── 3. Calcular columna central ────────────
    // Centramos la pieza en el tablero restando
    // la mitad del tamaño de la caja a la mitad
    // del ancho del tablero
    colPieza = (int)(anchoTablero / 2) - (int)(tamanioCaja / 2);

    // ── 4. Encontrar la última fila visible ────
    // Recorremos las filas de la pieza de abajo
    // hacia arriba para encontrar la última fila
    // que tenga al menos un bit en 1.
    // Esa es la fila que asoma primero en pantalla.
    //
    // Ejemplo con pieza T:
    //   fila 0: 11100000 ← tiene bits, pero no es la última
    //   fila 1: 01000000 ← tiene bits, esta es la última visible
    //   fila 2: 00000000 ← vacía, se ignora
    int ultimaFila = -1;
    for (int i = (int)tamanioCaja - 1; i >= 0; i--) {
        if (piezaActual[i] != 0) {
            ultimaFila = i;
            break; // encontramos la última fila con bits
        }
    }

    // ── 5. Colocar la fila visible en el tablero
    // Recorremos bit por bit la última fila visible
    // y marcamos las celdas correspondientes en
    // la fila 0 del tablero usando setCelda
    if (ultimaFila >= 0) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {

            // Creamos una máscara para leer cada bit
            // de la fila de la pieza de izquierda a derecha
            unsigned char mascara = 0x80 >> col; // 0x80 = 10000000

            // Si el bit está en 1, marcamos esa celda en el tablero
            if (piezaActual[ultimaFila] & mascara)
                setCelda(colPieza + col, 0); // fila 0 = parte superior
        }
    }
}
