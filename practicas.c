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
//    x.nro=obtenerUltimoNro(archivoPractica);
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

void cargarArchivoPracticas(char nombreArch[],PRACTICA x)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(PRACTICA), 1, buffer);
        fclose(buffer);
    }
}
void mostrarPractica(PRACTICA x)
{
     printf("\n----------------\n");
     printf("ID: %i\n",x.nro);
     printf("%s\n",x.nombrePractica);
     printf("\n----------------\n");
}

void mostrarPracticasActivasArch(char nombreArchivo[])
{
     FILE *buffer = fopen(nombreArchivo, "rb");
     if(buffer)
     {
          PRACTICA aux;
          while(fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
          {
               if(aux.eliminado == 0)
                    mostrarPractica(aux);
          }
          fclose(buffer);
     }
}
