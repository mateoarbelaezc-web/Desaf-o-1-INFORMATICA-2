#include "colisiones.h"

// ─────────────────────────────────────────────
// FUNCIÓN: colisionValida
// Recorre cada celda de la pieza actual y verifica
// si la nueva posición es válida.
//
// ¿Cómo funciona?
//   Para cada fila de la pieza, revisamos bit por bit.
//   Si el bit está en 1, calculamos su posición real
//   en el tablero sumando nuevaCol y nuevaFila.
//   Luego verificamos si esa posición es válida.
// ─────────────────────────────────────────────
int colisionValida(int nuevaCol, int nuevaFila) {

    // Recorremos cada fila de la caja de la pieza
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {

        // Recorremos cada columna de la caja
        for (unsigned int col = 0; col < tamanioCaja; col++) {

            // Creamos una máscara para leer el bit
            // correspondiente a esta columna
            // 0x80 = 10000000, desplazamos hacia la derecha
            // según la columna para leer cada bit
            unsigned char mascara = 0x80 >> col;

            // Solo verificamos si el bit está en 1
            // (si la celda de la pieza está ocupada)
            if (piezaActual[fila] & mascara) {

                // Calculamos la posición real en el tablero
                // sumando la posición de la pieza
                int colReal  = nuevaCol + (int)col;
                int filaReal = nuevaFila + (int)fila;

                // ── Verificación 1: borde izquierdo ───
                // Si la columna real es menor a 0,
                // la pieza se saldría por la izquierda
                if (colReal < 0)
                    return 0;

                // ── Verificación 2: borde derecho ─────
                // Si la columna real es mayor o igual
                // al ancho del tablero, se saldría
                // por la derecha
                if (colReal >= (int)anchoTablero)
                    return 0;

                // ── Verificación 3: borde inferior ────
                // Si la fila real es mayor o igual
                // al alto del tablero, la pieza llegó
                // al fondo
                if (filaReal >= (int)altoTablero)
                    return 0;

                // ── Verificación 4: colisión con pieza ─
                // Si la celda del tablero ya está ocupada,
                // hay colisión con otra pieza fija
                if (filaReal >= 0 && obtenerCelda((unsigned int)colReal, (unsigned int)filaReal))
                    return 0;
            }
        }
    }

    // Si ninguna celda tuvo colisión, el movimiento es válido
    return 1;
}
