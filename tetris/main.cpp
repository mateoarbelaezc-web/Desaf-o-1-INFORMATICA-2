#include "tablero.h"
#include "piezas.h"

int main() {

    inicializarTablero();
    generarPieza();

    cout << "\nPieza generada:" << endl;
    imprimirTablero();

    // Bajamos la pieza varias veces para probar
    for (int i = 0; i < 5; i++) {
        bajarPieza();
        cout << "\nDespues de bajar " << i + 1 << " vez:" << endl;
        imprimirTablero();
    }

    liberarTablero();
    return 0;
}
