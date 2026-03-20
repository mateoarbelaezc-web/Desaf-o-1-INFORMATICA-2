#include "rotar.h"
#include "piezas.h"
#include "colisiones.h"

void rotarPieza() {

    unsigned char piezaOriginal[MAX_CAJA];
    for (unsigned int i = 0; i < MAX_CAJA; i++)
        piezaOriginal[i] = piezaActual[i];

    unsigned char matriz[MAX_CAJA][MAX_CAJA] = {{0}};
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara)
                matriz[fila][col] = 1;
        }
    }


    unsigned char matrizRotada[MAX_CAJA][MAX_CAJA] = {{0}};
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            if (matriz[fila][col])
                matrizRotada[col][tamanioCaja - 1 - fila] = 1;
        }
    }

    unsigned char nuevaPieza[MAX_CAJA] = {0};
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            if (matrizRotada[fila][col]) {
                unsigned char mascara = 0x80 >> col;
                nuevaPieza[fila] |= mascara;
            }
        }
    }

    borrarPiezaTablero();

    for (unsigned int i = 0; i < MAX_CAJA; i++)
        piezaActual[i] = nuevaPieza[i];

    if (colisionValida(colPieza, filaPieza)) {
        dibujarPiezaTablero();
    } else {
        for (unsigned int i = 0; i < MAX_CAJA; i++)
            piezaActual[i] = piezaOriginal[i];
        dibujarPiezaTablero();
    }
}
