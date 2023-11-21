#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "practicas.h"



///------------------------------------------    PRINCIPALES     ---------------------------------------------------------------

void crearPractica(char nombreArchivo[])
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
    {
        int id = obtenerIdPractica(x.nombrePractica, nombreArchivo);
        x.nro = id;
        if(validarExistenciaPracticaActiva(id, nombreArchivo))
        {
            printf("Ingreso una practica que ya se encontraba en el sistema\n");
            mostrarPractica(x);
        }
        else
        {
            printf("¡La practica se encontraba dada de baja, Ahora se encuentra dada de alta!\n");
            cambiarEliminadoPractica(0, x, nombreArchivo);
        }

    }
}

void modificarPractica(char nombreArchivo[])
{

    mostrarListaPracticasActivas(nombreArchivo);
    PRACTICA practicaAModificar;
    printf("Ingrese ID de practica que quiere modificar: ");
    practicaAModificar.nro=leerEnteroPositivo();
    practicaAModificar = buscarPracticaArchivo(archivoPracticas,practicaAModificar.nro);
    if(practicaAModificar.nro != -1)
    {
        printf("Ingrese el nuevo Nombre de la practica ID %i: \n",practicaAModificar.nro);
        fflush(stdin);
        gets(practicaAModificar.nombrePractica);
        while(strlen(practicaAModificar.nombrePractica) > DIM_NPRACTICA)
        {
            printf("\nPractica INVALIDA\nIngrese nuevamente:  ");
            fflush(stdin);
            gets(practicaAModificar.nombrePractica);
        }
        strupr(practicaAModificar.nombrePractica);
        printf("Practica Modificada Exitosamente\n");
        mostrarPractica(practicaAModificar);
        modificarArchivoPracticas(practicaAModificar,nombreArchivo);

    }
    else
        printf("La practica la cual quiere modificar no se encuentra en el sistema\n");


}


void bajaPractica(char nombreArchivo[])
{
    mostrarListaPracticasActivas(nombreArchivo);
    PRACTICA practicaAModificar;
    printf("Ingrese ID de practica que quiere dar de baja\n");
    practicaAModificar.nro = leerEnteroPositivo();
    practicaAModificar = buscarPracticaArchivo(archivoPracticas,practicaAModificar.nro);
    if(practicaAModificar.nro == -1)
        printf("La practica no se encuentra en el sistema\n");
    else if(practicaAModificar.eliminado == 1)
        printf("La practica %s ya se encontraba dada de baja\n", practicaAModificar.nombrePractica);
    else
    {
        cambiarEliminadoPractica(1, practicaAModificar, nombreArchivo);
        printf("La practica fue dada de baja correctamente\n");
        practicaAModificar.eliminado = 1;
        mostrarPractica(practicaAModificar);
    }

}

void altaPractica(char nombreArchivo[])
{
    mostrarListaPracticasInActivas(nombreArchivo);
    PRACTICA practicaAModificar;
    printf("Ingrese ID de practica que quiere dar de alta\n");
    practicaAModificar.nro=leerEnteroPositivo();
    practicaAModificar = buscarPracticaArchivo(archivoPracticas,practicaAModificar.nro);
    if(practicaAModificar.nro == -1)
        printf("La practica no se encuentra en el sistema, carguela desde el menu de practicas\n");
    else if(practicaAModificar.eliminado == 0)
        printf("La practica %s ya se encontraba dada de alta\n", practicaAModificar.nombrePractica);
    else
    {
        cambiarEliminadoPractica(0, practicaAModificar, nombreArchivo);
        printf("La practica fue dada de alta correctamente\n");
        practicaAModificar.eliminado = 0;
        mostrarPractica(practicaAModificar);
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
        while((flag == 0) && (fread(&aux, sizeof(PRACTICA), 1, buffer) == 1))
        {
            if(nuevo.nro == aux.nro)
            {
                fseek(buffer, (-1) * sizeof(PRACTICA), 1);
                fwrite(&nuevo, sizeof(PRACTICA), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}

void cambiarEliminadoPractica(int valor, PRACTICA x, char nombreArchivo[])
{
    FILE * buffer = fopen(nombreArchivo, "r+b");
    PRACTICA aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 && fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
        {
            if(aux.nro == x.nro)
            {
                x.eliminado = valor;
                fseek(buffer, (-1) * sizeof(PRACTICA),1);
                fwrite(&x, sizeof(PRACTICA), 1, buffer);
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
    printf("Ingrese Nombre de la Practica:  ");
    fflush(stdin);
    gets(x.nombrePractica);
    while(strlen(x.nombrePractica) > DIM_NPRACTICA)
    {
        printf("Practica INVALIDA\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.nombrePractica);
    }
    strupr(x.nombrePractica);
    return x;
}

int obtenerUltimoNro(char nombreArchivo[])
{
    FILE * buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    int id = 0;
    if(buffer)
    {
        while(fread(&aux,sizeof(PRACTICA),1,buffer)>0)
            id = aux.nro;

        fclose(buffer);
    }
    return id+1;
}


int obtenerIdPractica(char nombrePractica[DIM_NPRACTICA], char nombreArchivo[])
{
    FILE * buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux,sizeof(PRACTICA),1,buffer)>0)
            if(strcmpi(nombrePractica, aux.nombrePractica) == 0)
                return aux.nro;

        fclose(buffer);
    }
    return -1;
}

nodoListaPR * crearNodoPR(PRACTICA x)
{
    nodoListaPR * nodo = (nodoListaPR *) malloc(sizeof(nodoListaPR));
    nodo->sig = NULL;
    nodo->practica = x;
    return nodo;
}

nodoListaPR * agregarEnOrdenListaPR(nodoListaPR * lista, nodoListaPR * nn)
{
    if(!lista)
        return nn;

    if(strcmp(nn->practica.nombrePractica,lista->practica.nombrePractica)== -1)
    {
        nn->sig = lista;
        return nn;
    }
    nodoListaPR* aux=lista;
    nodoListaPR* ante;

    while(aux && strcmp(nn->practica.nombrePractica,aux->practica.nombrePractica) == 1)
    {
        ante=aux;
        aux=aux->sig;
    }
    nn->sig = aux;
    ante->sig = nn;

    return lista;
}

char * obtenerNombrePractica(int nroPractica, char nombreArchivo[])
{
    char * nombre = (char *) malloc(DIM_NPRACTICA * (sizeof(char)));
    FILE * buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
        {
            if(aux.nro == nroPractica)
            {
                strcpy(nombre, aux.nombrePractica);
                fclose(buffer);
                return nombre;
            }
        }
        fclose(buffer);
    }
    return "ERROR";
}
