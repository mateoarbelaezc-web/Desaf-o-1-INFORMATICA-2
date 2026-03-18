#include "tablero.h"
#include "piezas.h"
#include "colisiones.h"
#include "comprobacion.h"

int main() {

    // Inicializa el tablero
    inicializarTablero();

    // Genera la primera pieza
    generarPieza();

    cout << "\nTablero inicial:" << endl;
    imprimirTablero();

    // Solo probamos bajar con 's' y salir con 'q'
    char accion;
    bool jugando = true;

    while (jugando) {

        cout << "Accion: [S]Bajar [Q]Salir: ";
        cin >> accion;

        if (accion == 's') {
            bajarPieza();
            imprimirTablero();
        } else if (accion == 'q') {
            jugando = false;
        }
    }

    liberarTablero();
    return 0;
}
