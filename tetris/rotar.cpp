#include "rotar.h"
#include "piezas.h"
#include "colisiones.h"
#include "tablero.h"

void rotarPieza() {
    unsigned char piezaOriginal[MAX_CAJA];
    unsigned int tamanioOriginal = tamanioCaja;

    for (unsigned int i = 0; i < MAX_CAJA; i++) {
        piezaOriginal[i] = piezaActual[i];
    }

    unsigned char piezaRotada[MAX_CAJA][MAX_CAJA] = {{0}};
    unsigned char nuevaPieza[MAX_CAJA] = {0};

    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara) {
                piezaRotada[fila][col] = 1;
            }
        }
    }

    unsigned char piezaRotadaMatriz[MAX_CAJA][MAX_CAJA] = {{0}};
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            piezaRotadaMatriz[col][tamanioCaja - 1 - fila] = piezaRotada[fila][col];
        }
    }

    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        unsigned char byteFila = 0;
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            if (piezaRotadaMatriz[fila][col]) {
                unsigned char mascara = 0x80 >> col;
                byteFila |= mascara;
            }
        }
        nuevaPieza[fila] = byteFila;
    }

    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara) {
                int colReal = colPieza + col;
                int filaReal = filaPieza + fila;
                if (filaReal >= 0) {
                    limpiarCelda(colReal, filaReal);
                }
            }
        }
    }

    for (unsigned int i = 0; i < MAX_CAJA; i++) {
        piezaActual[i] = nuevaPieza[i];
    }

    if (colisionValida(colPieza, filaPieza)) {
        for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
            for (unsigned int col = 0; col < tamanioCaja; col++) {
                unsigned char mascara = 0x80 >> col;
                if (piezaActual[fila] & mascara) {
                    int colReal = colPieza + col;
                    int filaReal = filaPieza + fila;
                    if (filaReal >= 0) {
                        setCelda(colReal, filaReal);
                    }
                }
            }
        }
    } else {
        for (unsigned int i = 0; i < MAX_CAJA; i++) {
            piezaActual[i] = piezaOriginal[i];
        }

        for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
            for (unsigned int col = 0; col < tamanioCaja; col++) {
                unsigned char mascara = 0x80 >> col;
                if (piezaActual[fila] & mascara) {
                    int colReal = colPieza + col;
                    int filaReal = filaPieza + fila;
                    if (filaReal >= 0) {
                        setCelda(colReal, filaReal);
                    }
                }
            }
        }
    }
}
