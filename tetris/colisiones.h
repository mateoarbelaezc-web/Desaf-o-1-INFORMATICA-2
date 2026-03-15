#ifndef COLISIONES_H
#define COLISIONES_H

#include "tablero.h"
#include "piezas.h"

// ─────────────────────────────────────────────
// FUNCIÓN: colisionValida
//
// Verifica si la pieza actual puede moverse a
// la nueva posición (nuevaCol, nuevaFila).
//
// Recibe:
//   nuevaCol → columna donde querría ir la pieza
//   nuevaFila → fila donde querría ir la pieza
//
// Retorna:
//   1 si el movimiento es válido (no hay colisión)
//   0 si el movimiento es inválido (hay colisión)
//
// Se debe llamar ANTES de cualquier movimiento:
//   if (colisionValida(colPieza - 1, filaPieza))
//       colPieza--;  // mover izquierda
//
//   if (colisionValida(colPieza, filaPieza + 1))
//       filaPieza++; // mover abajo
// ─────────────────────────────────────────────
int colisionValida(int nuevaCol, int nuevaFila);

#endif // COLISIONES_H
