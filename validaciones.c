#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"

bool validarDNI(const char *dni) {
    int len = strlen(dni);
    if (len < 7 || len > 9) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (dni[i] < '0' || dni[i] > '9') {
            return false;
        }
    }
    return true;
}

bool validarPalabras(const char *Palabras) {
    int len = strlen(Palabras);
    for (int i = 0; i < len; i++)
        if (!((Palabras[i] >= 'A' && Palabras[i] <= 'Z') || (Palabras[i] >= 'a' && Palabras[i] <= 'z') || Palabras[i] == ' '))
            return false;
    return true;
}
