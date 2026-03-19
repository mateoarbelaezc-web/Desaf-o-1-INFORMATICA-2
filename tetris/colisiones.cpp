#include "colisiones.h"

int colisionValida(int nuevaCol, int nuevaFila) {
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara) {
                int colReal  = nuevaCol + (int)col;
                int filaReal = nuevaFila + (int)fila;
                if (colReal < 0)
                    return 0;
                if (colReal >= (int)anchoTablero)
                    return 0;
                if (filaReal >= (int)altoTablero)
                    return 0;
                if (filaReal >= 0 && obtenerCelda((unsigned int)colReal, (unsigned int)filaReal))
                    return 0;
            }
        }
    }
    return 1;
}

