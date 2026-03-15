#include "tablero.h"

// ─────────────────────────────────────────────
// DEFINICIÓN DE LAS VARIABLES GLOBALES
// Aquí es donde realmente existen y ocupan memoria.
// En el .h solo las anunciamos con extern.
// ─────────────────────────────────────────────
unsigned char** celdas       = 0;
unsigned int    anchoTablero = 0;
unsigned int    altoTablero  = 0;
unsigned int    bytesPorFila = 0;

// ─────────────────────────────────────────────
// FUNCIÓN: inicializarTablero
// Se encarga de:
//   1. Pedir ancho y alto al usuario
//   2. Validar que ancho sea múltiplo de 8 y ambos >= 8
//   3. Reservar memoria dinámica para el tablero
//   4. Inicializar todas las celdas en 0 (vacías)
// ─────────────────────────────────────────────
void inicializarTablero() {

    // ── Pedir y validar ancho ──────────────────
    // El do-while repite la pregunta hasta que el valor sea válido.
    // Condición: ancho >= 8 Y sea múltiplo de 8 (ancho % 8 == 0)
    do {
        cout << "Ingrese el ancho del tablero (multiplo de 8, minimo 8): ";
        cin  >> anchoTablero;

        if (anchoTablero < 8 || anchoTablero % 8 != 0)
            cout << "Ancho invalido. Debe ser multiplo de 8 y minimo 8." << endl;

    } while (anchoTablero < 8 || anchoTablero % 8 != 0);

    // ── Pedir y validar alto ───────────────────
    do {
        cout << "Ingrese el alto del tablero (minimo 8): ";
        cin  >> altoTablero;

        if (altoTablero < 8)
            cout << "Alto invalido. Debe ser minimo 8." << endl;

    } while (altoTablero < 8);

    // ── Calcular bytes por fila ────────────────
    // Como cada byte tiene 8 bits y cada bit es una celda,
    // dividimos el ancho entre 8 para saber cuántos bytes
    // necesitamos por fila.
    // Ejemplo: ancho=16 → bytesPorFila=2
    bytesPorFila = anchoTablero / 8;

    // ── Reservar memoria para las filas ───────
    // Creamos un arreglo dinámico de punteros,
    // uno por cada fila del tablero.
    celdas = new unsigned char*[altoTablero];

    // ── Reservar memoria para cada fila ───────
    // Cada fila es un arreglo de bytesPorFila bytes.
    // Los inicializamos en 0 (todas las celdas vacías).
    for (unsigned int i = 0; i < altoTablero; i++) {
        celdas[i] = new unsigned char[bytesPorFila];

        // Ponemos cada byte de la fila en 0
        // 0 en binario = 00000000 → 8 celdas vacías
        for (unsigned int j = 0; j < bytesPorFila; j++)
            celdas[i][j] = 0;
    }
}

// ─────────────────────────────────────────────
// FUNCIÓN: liberarTablero
// Libera la memoria en orden inverso a como se reservó:
//   1. Primero libera cada fila
//   2. Luego libera el arreglo de punteros
// No hacerlo causaría memory leaks (memoria perdida)
// ─────────────────────────────────────────────
void liberarTablero() {
    for (unsigned int i = 0; i < altoTablero; i++)
        delete[] celdas[i];  // libera cada fila

    delete[] celdas;         // libera el arreglo de punteros
    celdas = 0;              // buena práctica: apuntar a 0 tras liberar
}

// ─────────────────────────────────────────────
// FUNCIÓN: obtenerCelda
// Retorna 1 si la celda (col, fila) está ocupada, 0 si no.
//
// ¿Cómo funciona con bits?
//   - Cada byte guarda 8 celdas consecutivas.
//   - Para saber en qué byte cae la columna: col / 8
//   - Para saber qué bit dentro de ese byte:  col % 8
//
// Ejemplo: col=10, ancho=16
//   byte = 10 / 8 = 1       → segundo byte de la fila
//   bit  = 10 % 8 = 2       → tercer bit de ese byte
//
// Luego aplicamos una máscara con AND (&):
//   mascara  = 10000000 >> 2 = 00100000
//   byte     = ????????
//   resultado= 00?00000  → si el bit es 1, resultado != 0
// ─────────────────────────────────────────────
unsigned char obtenerCelda(unsigned int col, unsigned int fila) {

    unsigned int  indiceByte = col / 8;       // qué byte de la fila
    unsigned int  indiceBit  = col % 8;       // qué bit dentro del byte

    // La máscara tiene un 1 en la posición del bit que queremos leer.
    // Empezamos desde el bit más significativo (izquierda = columna 0).
    unsigned char mascara = 128 >> indiceBit; // 128 = 10000000 en binario

    // AND entre el byte y la máscara:
    //   - Si el bit estaba en 1 → resultado != 0 → retorna valor distinto de 0
    //   - Si el bit estaba en 0 → resultado == 0 → retorna 0
    return (celdas[fila][indiceByte] & mascara) ? 1 : 0;
}

// ─────────────────────────────────────────────
// FUNCIÓN: setCelda
// Pone en 1 el bit de la celda (col, fila).
// Usa OR | con la máscara para activar el bit
// sin afectar los demás bits del byte.
//
// Ejemplo:
//   byte    = 00100000
//   mascara = 00010000
//   OR      = 00110000  ← solo se activó el bit nuevo
// ─────────────────────────────────────────────
void setCelda(unsigned int col, unsigned int fila) {

    unsigned int  indiceByte = col / 8;
    unsigned int  indiceBit  = col % 8;
    unsigned char mascara    = 128 >> indiceBit;

    // OR activa el bit sin tocar los demás
    celdas[fila][indiceByte] |= mascara;
}

// ─────────────────────────────────────────────
// FUNCIÓN: limpiarCelda
// Pone en 0 el bit de la celda (col, fila).
// Usa AND & con el complemento ~ de la máscara.
//
// Ejemplo:
//   byte    = 00110000
//   mascara = 00010000
//  ~mascara = 11101111
//   AND     = 00100000  ← solo se apagó el bit deseado
// ─────────────────────────────────────────────
void limpiarCelda(unsigned int col, unsigned int fila) {

    unsigned int  indiceByte = col / 8;
    unsigned int  indiceBit  = col % 8;
    unsigned char mascara    = 128 >> indiceBit;

    // ~mascara invierte todos los bits de la máscara,
    // AND apaga solo el bit deseado
    celdas[fila][indiceByte] &= ~mascara;
}

// ─────────────────────────────────────────────
// FUNCIÓN: filaCompleta
// Retorna 1 si todos los bits de la fila están en 1.
//
// ¿Cómo funciona?
//   - Una fila completa tiene todos sus bits en 1.
//   - Un byte con todos sus bits en 1 es 0xFF (11111111).
//   - Entonces basta con revisar que cada byte
//     de la fila sea igual a 0xFF.
//   - Si algún byte no es 0xFF, la fila no está completa.
//
// Ejemplo con ancho=16 (2 bytes por fila):
//   fila = [ 11111111 | 11111111 ] → completa   → retorna 1
//   fila = [ 11111111 | 11011111 ] → incompleta → retorna 0
// ─────────────────────────────────────────────
unsigned char filaCompleta(unsigned int fila) {

    for (unsigned int j = 0; j < bytesPorFila; j++) {

        // 0xFF = 11111111 en binario (todos los bits en 1)
        // Si algún byte no es 0xFF, la fila tiene celdas vacías
        if (celdas[fila][j] != 0xFF)
            return 0; // fila incompleta
    }

    return 1; // todos los bytes eran 0xFF → fila completa
}

// ─────────────────────────────────────────────
// FUNCIÓN: eliminarFila
// Elimina la fila indicada y baja todas las
// filas superiores una posición hacia abajo.
//
// ¿Cómo funciona?
//   En lugar de copiar contenido byte por byte,
//   movemos directamente los PUNTEROS del arreglo.
//   Esto es mucho más eficiente porque solo
//   reasignamos direcciones de memoria.
//
// Ejemplo con altoTablero=4, eliminando fila 2:
//
//   Antes:          Después:
//   celdas[0] → A   celdas[0] → (nueva fila vacía)
//   celdas[1] → B   celdas[1] → A
//   celdas[2] → C   celdas[2] → B
//   celdas[3] → D   celdas[3] → D
//
//   La fila C (completa) se libera y se crea
//   una nueva fila vacía en la parte superior.
// ─────────────────────────────────────────────
void eliminarFila(unsigned int fila) {

    // ── Liberar la fila completa ───────────────
    delete[] celdas[fila];

    // ── Subir los punteros una posición ───────
    // Movemos cada puntero desde la fila eliminada
    // hacia arriba, bajando así las filas superiores.
    for (unsigned int i = fila; i > 0; i--)
        celdas[i] = celdas[i - 1]; // el puntero de arriba baja una posición

    // ── Crear nueva fila vacía en la cima ─────
    // La fila 0 (tope del tablero) ahora apunta
    // a una nueva fila reservada e inicializada en 0
    celdas[0] = new unsigned char[bytesPorFila];

    for (unsigned int j = 0; j < bytesPorFila; j++)
        celdas[0][j] = 0; // 0 = 00000000 → fila completamente vacía
}

// ─────────────────────────────────────────────
// FUNCIÓN: limpiarFilasCompletas
// Recorre todas las filas del tablero de abajo
// hacia arriba, elimina las que están completas
// y retorna cuántas filas fueron eliminadas.
//
// ¿Por qué de abajo hacia arriba?
//   Porque al eliminar una fila, las superiores
//   bajan una posición. Si recorriéramos de arriba
//   hacia abajo podríamos saltarnos filas que
//   quedaron en la posición recién revisada.
// ─────────────────────────────────────────────
unsigned char limpiarFilasCompletas() {

    unsigned char filasEliminadas = 0;
    int i = (int)altoTablero - 1; // empezamos desde la fila más baja

    while (i >= 0) {

        if (filaCompleta((unsigned int)i)) {

            eliminarFila((unsigned int)i);
            filasEliminadas++;

            // No decrementamos i porque al eliminar la fila,
            // la fila que estaba arriba bajó a esta misma posición
            // y también hay que revisarla
        } else {
            i--; // solo avanzamos si la fila actual no era completa
        }
    }

    return filasEliminadas;
}

// ─────────────────────────────────────────────
// FUNCIÓN: imprimirTablero
// Recorre el tablero fila por fila y bit por bit,
// imprimiendo '#' si el bit es 1 (ocupado)
// o '.' si el bit es 0 (libre).
//
// Al final de cada fila imprime '|' como borde
// y salta a la siguiente línea.
// ─────────────────────────────────────────────
void imprimirTablero() {

    // ── Borde superior ────────────────────────
    cout << "+";
    for (unsigned int j = 0; j < anchoTablero; j++)
        cout << "-";
    cout << "+" << endl;

    // ── Filas del tablero ─────────────────────
    for (unsigned int i = 0; i < altoTablero; i++) {

        cout << "|"; // borde izquierdo

        for (unsigned int j = 0; j < anchoTablero; j++) {

            // obtenerCelda revisa el bit correspondiente
            // a la columna j de la fila i
            if (obtenerCelda(j, i))
                cout << "#"; // celda ocupada
            else
                cout << "."; // celda vacía
        }

        cout << "|" << endl; // borde derecho y salto de línea
    }

    // ── Borde inferior ────────────────────────
    cout << "+";
    for (unsigned int j = 0; j < anchoTablero; j++)
        cout << "-";
    cout << "+" << endl;
}
