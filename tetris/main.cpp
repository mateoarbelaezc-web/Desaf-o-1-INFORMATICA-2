#include "tablero.h"
#include "piezas.h"

int main() {

    // Inicializa el tablero
    inicializarTablero();

    // Genera una pieza y la muestra en el tablero
    generarPieza();

    // Imprime el tablero con la pieza asomando
    cout << "\nTablero con pieza generada:" << endl;
    imprimirTablero();

    // Libera la memoria
    liberarTablero();

    return 0;
}
