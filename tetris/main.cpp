#include <iostream>
using namespace std;
#include "tablero.h"
#include "Piezas.h"
#include "rotar.h"
#include "comprobacion.h"

int main() {

    inicializarTablero();
    generarPieza();

    bool jugando = true;

    cout << "=== TETRIS POR TURNOS ===" << endl;
    cout << "Comandos: [A]Izq [D]Der [S]Bajar [W]Rotar [Q]Salir" << endl;

    while (jugando && !gameOver) {

        imprimirTablero();

        char opcion = pedirLetra();

        switch(opcion) {
        case 'a':
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
        case 's':
            if (bajarPieza())
                cout << "Bajaste" << endl;
            else
                cout << "Nueva pieza generada" << endl;
            break;
        case 'w':
            rotarPieza();
            cout << "Rotaste la pieza" << endl;
            break;
        case 'q':
            jugando = false;
            cout << "Fin del juego" << endl;
            break;
        default:
            cout << "Comando invalido" << endl;
        }
    }

    if (gameOver) {
        imprimirTablero();
        cout << "GAME OVER" << endl;
    }

    liberarTablero();
    return 0;
}
