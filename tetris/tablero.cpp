#include "tablero.h"
#include "comprobacion.h"

unsigned char** celdas       = 0;
unsigned int    anchoTablero = 0;
unsigned int    altoTablero  = 0;
unsigned int    bytesPorFila = 0;

void inicializarTablero() {
    pedirDimensiones(altoTablero, anchoTablero);
    bytesPorFila = anchoTablero / 8;
    celdas = new unsigned char*[altoTablero];
    for (unsigned int i = 0; i < altoTablero; i++) {
        celdas[i] = new unsigned char[bytesPorFila];
        for (unsigned int j = 0; j < bytesPorFila; j++)
            celdas[i][j] = 0;
    }
}

void liberarTablero() {
    for (unsigned int i = 0; i < altoTablero; i++)
        delete[] celdas[i];
    delete[] celdas;
    celdas = 0;
}

unsigned char obtenerCelda(unsigned int col, unsigned int fila) {
    unsigned int  indiceByte = col / 8;
    unsigned int  indiceBit  = col % 8;
    unsigned char mascara = 128 >> indiceBit;
    return (celdas[fila][indiceByte] & mascara) ? 1 : 0;
}

void setCelda(unsigned int col, unsigned int fila) {
    unsigned int  indiceByte = col / 8;
    unsigned int  indiceBit  = col % 8;
    unsigned char mascara    = 128 >> indiceBit;
    celdas[fila][indiceByte] |= mascara;
}

void limpiarCelda(unsigned int col, unsigned int fila) {
    unsigned int  indiceByte = col / 8;
    unsigned int  indiceBit  = col % 8;
    unsigned char mascara    = 128 >> indiceBit;
    celdas[fila][indiceByte] &= ~mascara;
}

unsigned char filaCompleta(unsigned int fila) {
    for (unsigned int j = 0; j < bytesPorFila; j++) {
        if (celdas[fila][j] != 0xFF)
            return 0;
    }
    return 1;
}

void eliminarFila(unsigned int fila) {
    delete[] celdas[fila];
    for (unsigned int i = fila; i > 0; i--)
        celdas[i] = celdas[i - 1];
    celdas[0] = new unsigned char[bytesPorFila];
    for (unsigned int j = 0; j < bytesPorFila; j++)
        celdas[0][j] = 0;
}

unsigned char limpiarFilasCompletas() {
    unsigned char filasEliminadas = 0;
    int i = (int)altoTablero - 1;
    while (i >= 0) {
        if (filaCompleta((unsigned int)i)) {
            eliminarFila((unsigned int)i);
            filasEliminadas++;
        } else {
            i--;
        }
    }
    return filasEliminadas;
}

void imprimirTablero() {
    cout << "+";
    for (unsigned int j = 0; j < anchoTablero; j++)
        cout << "-";
    cout << "+" << endl;
    for (unsigned int i = 0; i < altoTablero; i++) {
        cout << "|";
        for (unsigned int j = 0; j < anchoTablero; j++) {
            if (obtenerCelda(j, i))
                cout << "#";
            else
                cout << ".";
        }
        cout << "|" << endl;
    }
    cout << "+";
    for (unsigned int j = 0; j < anchoTablero; j++)
        cout << "-";
    cout << "+" << endl;
}
