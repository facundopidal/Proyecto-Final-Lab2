#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"

PRACTICA cargarPractica()
{
    PRACTICA x;
    x.eliminado = 0;
    x.nro=obtenerUltimoNro(archivoPractica);
    printf("\nIngrese Nombre de la Practica:  ");
    gets(x.nombrePractica);
    while(!validarPalabras(x.nombrePractica))
    {
        printf("\nPractica INVALIDA\nIngrese nuevamente:  ");
        gets(x.nombrePractica);
    }
    x.eliminado=0;
    return x;
}

void appendPracticaArchivo(char nomArch[],PRACTICA x)
{
    FILE *buffer = fopen(nomArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(PRACTICA), 1, buffer);
        fclose(buffer);
    }
}


