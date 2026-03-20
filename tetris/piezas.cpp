#include "piezas.h"
#include "colisiones.h"
#include <cstdlib>

unsigned char piezaActual[MAX_CAJA];
unsigned int  tamanioCaja = 0;
unsigned int  tipoPieza   = 0;
int           colPieza    = 0;
int           filaPieza   = 0;
bool gameOver = false;

const unsigned char formas[NUM_PIEZAS][MAX_CAJA] = {
    { 0x00, 0xF0, 0x00, 0x00 },
    { 0xC0, 0xC0, 0x00, 0x00 },
    { 0x60, 0xC0, 0x00, 0x00 },
    { 0xC0, 0x60, 0x00, 0x00 },
    { 0x80, 0x80, 0xC0, 0x00 }
};

const unsigned int tamanos[NUM_PIEZAS] = { 4, 2, 3, 3, 3 };

void generarPieza() {
    tipoPieza   = rand() % NUM_PIEZAS;
    tamanioCaja = tamanos[tipoPieza];
    for (unsigned int i = 0; i < MAX_CAJA; i++)
        piezaActual[i] = formas[tipoPieza][i];
    colPieza = (int)(anchoTablero / 2) - (int)(tamanioCaja / 2);

    int ultimaFila = -1;
    for (int i = (int)tamanioCaja - 1; i >= 0; i--) {
        if (piezaActual[i] != 0) {
            ultimaFila = i;
            break;
        }
    }
    if (ultimaFila >= 0)
        filaPieza = -ultimaFila;
    else
        filaPieza = 0;

    if (!colisionValida(colPieza, filaPieza)) {
        gameOver = true;
        return; // no dibujamos la pieza
    }

    dibujarPiezaTablero();
}

int bajarPieza() {
    borrarPiezaTablero();

    if (colisionValida(colPieza, filaPieza + 1)) {
        filaPieza++;
        dibujarPiezaTablero();
        return 1;
    } else {
        dibujarPiezaTablero();
        limpiarFilasCompletas();
        generarPieza();
        return 0;
    }
}

int moverPieza(int direccion) {
    borrarPiezaTablero();

    if (colisionValida(colPieza + direccion, filaPieza)) {
        colPieza += direccion;
        dibujarPiezaTablero();
        return 1;
    } else {
        dibujarPiezaTablero();
        return 0;
    }
}

void borrarPiezaTablero() {
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara) {
                int colReal  = colPieza  + (int)col;
                int filaReal = filaPieza + (int)fila;
                if (filaReal >= 0)
                    limpiarCelda((unsigned int)colReal, (unsigned int)filaReal);
            }
        }
    }
}

void dibujarPiezaTablero() {
    for (unsigned int fila = 0; fila < tamanioCaja; fila++) {
        for (unsigned int col = 0; col < tamanioCaja; col++) {
            unsigned char mascara = 0x80 >> col;
            if (piezaActual[fila] & mascara) {
                int colReal  = colPieza  + (int)col;
                int filaReal = filaPieza + (int)fila;
                if (filaReal >= 0)
                    setCelda((unsigned int)colReal, (unsigned int)filaReal);
            }
        }
    }
}
