#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
//Paciente
//PACIENTE
//paciente

nodoPaciente* crearNodoPaciente(PACIENTE x)
{
    nodoPaciente* NNP=(nodoPaciente*)malloc(sizeof(nodoPaciente));
    strcpy(NNP->paciente.apellido,x.apellido);
    strcpy(NNP->paciente.nombre,x.nombre);
    strcpy(NNP->paciente.dni,x.dni);
    strcpy(NNP->paciente.direccion,x.direccion);
    strcpy(NNP->paciente.telefono,x.telefono);
    NNP->paciente.edad = x.edad;
    NNP->paciente.eliminado = x.eliminado;
    NNP->izq=NULL;
    NNP->der=NULL;
    return NNP;
}

PACIENTE cargarPaciente()
{
    PACIENTE x;
    x.eliminado = 0;
    ///DNI
    printf("Ingrese DNI:  ");
    fflush(stdin);
    gets(x.dni);
    while(!validarDNI(x.dni))
    {
        printf("\nDNI NO VALIDO \nIngrese nuevamente:  ");
        fflush(stdin);
        gets(x.dni);
    }
    ///APELLIDO
    printf("\nIngrese Apellido: ");
    fflush(stdin);
    gets(x.apellido);
    while(!validarPalabras(x.apellido))
    {
        printf("\nApellido NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.apellido);
    }
    ///NOMBRE
    printf("\nIngrese Nombre: ");
    fflush(stdin);
    gets(x.nombre);
    while(!validarPalabras(x.nombre))
    {
        printf("\nNOMBRE NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.nombre);
    }
    ///DIRECCION
    printf("\nIngrese Direccion: ");
    fflush(stdin);
    gets(x.direccion);
    ///TELEFONO
    printf("\n Ingrese Telefono");
    fflush(stdin);
    gets(x.telefono);
    while(!validarTelefono(x.telefono))
    {
        printf("\nTelefono NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.telefono);
    }

    return x;
}

bool buscarPaciente(nodoPaciente * arbol, PACIENTE x)
{
    if(arbol)
    {
        if(strcmp(arbol->paciente.dni, x.dni) == 0)
            return true;
        else if(strcmp(arbol->paciente.dni, x.dni) < 0)
            return buscarPaciente(arbol->izq, x);
        else
            return buscarPaciente(arbol->der, x);
    }
    return false;
}


void mostrarPaciente(PACIENTE x)
{
    printf("\nDNI: %s",x.dni);
    printf("\nApellido y Nombre: %s %s",x.apellido,x.nombre);
    printf("\nDireccion: %s",x.direccion);
    printf("\nTelefono: %s",x.telefono);
    printf("Edad: %i",x.edad);
}

void mostrarPacientesTodos(nodoPaciente* arbol)
{
    if(arbol)
    {
        mostrarPacientesTodos(arbol->izq);
        mostrarPaciente(arbol->paciente);
        mostrarPacientesTodos(arbol->der);
    }
}

void mostrarPacientesActivos(nodoPaciente* arbol)
{
    if(arbol)
    {
        mostrarPacientesActivos(arbol->izq);
        if(arbol->paciente.eliminado == 0)
            mostrarPaciente(arbol->paciente);
        mostrarPacientesActivos(arbol->der);
    }
}

void appendPacienteArchivo(char nomArch[],PACIENTE x)
{
    FILE *buffer = fopen(nomArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(PACIENTE), 1, buffer);
        fclose(buffer);
    }
}

