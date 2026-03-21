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
                throw letra;
            }

            return letra;
        }
        catch (char) {
            cout << "Error: solo se permiten las letras a, s, d, w o q." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void pedirDimensiones(unsigned int &altura, unsigned int &ancho) {

    while (true) {

        try {

            int temp = 0;

            cout << "Ingrese la altura (minimo 8): ";
            cin >> temp;

            if (cin.fail() || temp < 8)
                throw temp;

            altura = (unsigned int)temp;

            cout << "Ingrese el ancho (multiplo de 8, minimo 8): ";
            cin >> temp;

            if (cin.fail() || temp < 8 || temp % 8 != 0)
                throw temp;

            ancho = (unsigned int)temp;
            return;
        }
        catch (int) {
            cout << "Error: altura minimo 8 y ancho multiplo de 8." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}
