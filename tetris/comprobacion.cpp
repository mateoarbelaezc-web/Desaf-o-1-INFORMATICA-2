#include <iostream>
#include "comprobacion.h"
using namespace std;

char pedirLetra() {
    char letra;

    while (true) {
        try {
            cout << "Ingrese una letra (a, s, d, w o q): ";
            cin >> letra;

            if (letra != 'a' && letra != 's' && letra != 'd' &&
                letra != 'w' && letra != 'q') {
                throw letra;  // lanza error si no es válida
            }

            return letra; // entrada válida
        }
        catch (char) {
            cout << "Error: solo se permiten las letras a, s, d, w o q." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

// ─────────────────────────────────────────────
// FUNCIÓN: pedirDimensiones
// Pide al usuario el alto y ancho del tablero.
// Recibe altura y ancho por referencia para
// modificarlos directamente desde esta función.
// El & significa que no se hace una copia, sino
// que se trabaja con la variable original.
// ─────────────────────────────────────────────
void pedirDimensiones(unsigned int &altura, unsigned int &ancho) {

    // while(true) repite indefinidamente hasta
    // que el usuario ingrese valores válidos
    // y se ejecute el return
    while (true) {

        // try intenta ejecutar el bloque de código,
        // si algo sale mal lanza un error con throw
        // y el catch lo atrapa
        try {

            // Usamos int con signo para detectar
            // números negativos antes de asignarlos
            // a unsigned int
            int temp = 0;

            // ── Pedir altura ───────────────────
            cout << "Ingrese la altura (minimo 8): ";
            cin >> temp;

            // cin.fail() detecta si el usuario ingresó
            // algo que no es un número (letras, símbolos)
            // temp < 8 detecta números negativos o muy pequeños
            if (cin.fail() || temp < 8)
                throw temp; // lanza el error con el valor inválido

            // Solo llegamos aquí si temp es válido,
            // lo convertimos a unsigned int y lo asignamos
            altura = (unsigned int)temp;

            // ── Pedir ancho ────────────────────
            cout << "Ingrese el ancho (multiplo de 8, minimo 8): ";
            cin >> temp;

            // Tres condiciones para ancho inválido:
            // 1. cin.fail()     → ingresaron letras
            // 2. temp < 8       → número muy pequeño o negativo
            // 3. temp % 8 != 0  → no es múltiplo de 8
            if (cin.fail() || temp < 8 || temp % 8 != 0)
                throw temp;

            // Solo llegamos aquí si ancho es válido
            ancho = (unsigned int)temp;

            // Salimos del while porque todo fue válido
            return;
        }

        // catch atrapa cualquier error lanzado con throw
        // el (int) indica que solo atrapa errores de tipo int
        catch (int) {
            cout << "Error: altura minimo 8 y ancho multiplo de 8." << endl;

            // cin.clear() limpia el estado de error de cin
            // para que pueda seguir leyendo entradas
            cin.clear();

            // cin.ignore descarta todo lo que quedó
            // en el buffer de entrada hasta el Enter
            cin.ignore(1000, '\n');
        }
    }
}
