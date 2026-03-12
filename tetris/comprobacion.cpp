#include <iostream>
using namespace std;

char pedirLetra() {
    char letra;

    while (true) {
        try {
            cout << "Ingrese una letra (a, s o d): ";
            cin >> letra;

            if (letra != 'a' && letra != 's' && letra != 'd') {
                throw letra;  // lanza error si no es válida
            }

            return letra; // entrada válida
        }
        catch (char) {
            cout << "Error: solo se permiten las letras a, s o d." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}

void pedirDimensiones(int &altura, int &ancho) {

    while (true) {
        try {
            cout << "Ingrese la altura (mayor a 2): ";
            cin >> altura;

            if (altura <= 2) {
                throw altura;
            }

            cout << "Ingrese el ancho (multiplo de 8): ";
            cin >> ancho;

            if (ancho % 8 != 0) {
                throw ancho;
            }

            return; // todo válido
        }
        catch (int) {
            cout << "Error: altura debe ser mayor a 2 y ancho multiplo de 8." << endl;
            cin.clear();
            cin.ignore(1000, '\n');
        }
    }
}
