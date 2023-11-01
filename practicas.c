#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"



///------------------------------------------    PRINCIPALES     ---------------------------------------------------------------

void altaPractica(char nombreArchivo[])
{
    PRACTICA x = cargarPractica();
    if(!validarPracticaRepetida(x.nombrePractica,nombreArchivo))
    {
        x.nro=obtenerUltimoNro(nombreArchivo);
        cargarArchivoPracticas(archivoPracticas,x);
        printf("Practica cargada exitosamente:\n");
        mostrarPractica(x);
    }
    else
        printf("Ingreso una practica que ya se encontraba en el sistema\n");
}

void modificarPractica(char nombreArchivo[])
{
    PRACTICA practicaAModificar;
    printf("Ingrese ID de practica que quiere modificar\n");
    practicaAModificar.nro=leerEntero();
    practicaAModificar = buscarPracticaArchivo(archivoPracticas,practicaAModificar.nro);
    if(practicaAModificar.nro != -1)
    {
        printf("Ingrese el nuevo Nombre de la practica ID: %i\n",practicaAModificar.nro);
        gets(practicaAModificar.nombrePractica);
        while(!validarPalabras(practicaAModificar.nombrePractica,DIM_NPRACTICA))
        {
            printf("\nPractica INVALIDA\nIngrese nuevamente:  ");
            gets(practicaAModificar.nombrePractica);
        }
        printf("Practica Modificada Exitosamente\n");
        mostrarPractica(practicaAModificar);
        modificarArchivoPracticas(practicaAModificar,nombreArchivo);

    }
    else
        printf("La practica la cual quiere modificar no se encuentra en el sistema\n");


}


///Funcion Dar de baja y alta practica



///------------------------------------------    MOSTRAR     ---------------------------------------------------------------

void mostrarPractica(PRACTICA x)
{
    printf("----------------\n");
    if(x.eliminado==0)
        printf("ID: %i\n",x.nro);
    else
        printf("ID: i% (DADA DE BAJA)");
    printf("%s\n",x.nombrePractica);
    printf("----------------\n");
}

void mostrarPracticasArch(char nombreArchivo[])
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    if(buffer)
    {
        PRACTICA aux;
        printf("PRACTICAS CARGADAS EN EL SISTEMA\n");
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
        {
            mostrarPractica(aux);
        }
        fclose(buffer);
    }
}

///------------------------------------------    ARCHIVO     ---------------------------------------------------------------


void cargarArchivoPracticas(char nombreArch[],PRACTICA x)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(PRACTICA), 1, buffer);
        fclose(buffer);
    }
}

PRACTICA buscarPracticaArchivo(char nombreArchivo[],int id)
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
        {
            if(id == aux.nro)
                return aux;
        }
        fclose(buffer);
    }
    aux.nro = -1;
    return aux;
}

void modificarArchivoPracticas(PRACTICA nuevo,char nombreArchivo[])
{
    FILE * buffer = fopen(nombreArchivo, "r+b");
    PRACTICA aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 && fread(&aux, sizeof(PRACTICA), 1, buffer) == 1)
        {
            if(nuevo.nro == aux.nro)
            {
                fseek(buffer, (-1) * sizeof(PRACTICA), 1);
                fwrite(&aux, sizeof(PRACTICA), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}

///------------------------------------------    AUXILIARES     ---------------------------------------------------------------


PRACTICA cargarPractica()
{
    PRACTICA x;
    x.eliminado = 0;
    printf("\nIngrese Nombre de la Practica:  ");
    fflush(stdin);
    gets(x.nombrePractica);
    while(!validarPalabras(x.nombrePractica,DIM_NPRACTICA))
    {
        printf("\nPractica INVALIDA\nIngrese nuevamente:  ");
        gets(x.nombrePractica);
    }
    return x;
}

int obtenerUltimoNro(char nombreArchivo[])
{
    FILE * buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    int id;
    if(buffer)
    {
        while(fread(&aux,sizeof(PRACTICA),1,buffer)>0)

            id = aux.nro;

        fclose(buffer);
    }
    return id+1;
}






