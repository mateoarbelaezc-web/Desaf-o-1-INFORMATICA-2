#include <iostream>
using namespace std;

#include "tablero.h"
#include "piezas.h"
#include "colisiones.h"
#include "rotar.h"

int main() {
    inicializarTablero();
    generarPieza();

    char opcion;
    bool jugando = true;

    cout << "=== TETRIS POR TURNOS ===" << endl;
    cout << "Comandos: (i)zquierda, (d)erecha, (b)ajar, (s)alir" << endl;

    while (jugando) {
        imprimirTablero();
        cout << "Turno - Elige comando (i/d/b/s): ";
        cin >> opcion;

        switch(opcion) {
        case 'i':
            if (moverPieza(-1))
                cout << "Moviste izquierda" << endl;
            else
                cout << "No puedes mover izquierda" << endl;
            break;

        case 'd':
            if (moverPieza(1))
                cout << "Moviste derecha" << endl;
            else
                cout << "No puedes mover derecha" << endl;
            break;

        case 'b':
            if (bajarPieza())
                cout << "Bajaste" << endl;
            else
                cout << "Nueva pieza generada" << endl;
            break;

        case 's':
            jugando = false;
            cout << "Fin del juego" << endl;
            break;

        case 'r':
            rotarPieza();
            cout << "Rotaste la pieza" << endl;
            break;

        default:
            cout << "Comando invalido" << endl;
        }
    }

    liberarTablero();
    return 0;
}
