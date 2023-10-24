#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"

bool validarDNI(const char *dni)
{
    int len = strlen(dni);
    if (len < 7 || len > 9)
        return false;
    for (int i = 0; i < len; i++)
    {
        if (dni[i] < '0' || dni[i] > '9')
            return false;
    }
    return true;
}

bool validarPalabras(const char *Palabras)
{
    int len = strlen(Palabras);
    for (int i = 0; i < len; i++)
        if (!((Palabras[i] >= 'A' && Palabras[i] <= 'Z') || (Palabras[i] >= 'a' && Palabras[i] <= 'z') || Palabras[i] == ' '))
            return false;
    return true;
}

bool validarTelefono(const char *cadena)
{
    int longitud = strlen(cadena);
    if (longitud < 8)
        return false;
    for (int i = 0; i < longitud; i++)
        if (cadena[i] < '0' || cadena[i] > '9')
            return false;
    return true;
}

bool validarFecha(const char *fecha) {
    // Verifica la longitud de la cadena
    if (strlen(fecha) != 10)
        return false;

    // Verifica el formato dd/mm/aaaa
    if (fecha[2] != '/' || fecha[5] != '/')
        return false;

    // Extrae día, mes y año de la cadena
    int dia, mes, anio;
    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) != 3)
        return false;

    // Verifica el año
    if (anio <= 2022)
        return false;

    // Verifica el mes (debe estar en el rango 1-12)
    if (mes < 1 || mes > 12)
        return false;

    // Verifica el día según el mes
    switch (mes) {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12:
            if (dia < 1 || dia > 31)
                return false;

            break;
        case 4: case 6: case 9: case 11:
            if (dia < 1 || dia > 30)
                return false;

            break;
        case 2:
            if (anio == 2024) { //Se podria hacer una validacion completa para todos los años bisiestos
                if (dia < 1 || dia > 29)
                    return false;  // Año bisiesto, febrero puede tener 29 días
            } else {
                if (dia < 1 || dia > 28)
                    return false;  // Febrero normal con 28 días
            }
            break;
        default:
            return false;
    }

    // Si no se encontraron problemas, la fecha es válida
    return true;
}
