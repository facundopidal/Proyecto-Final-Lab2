#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"

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


nodoPaciente* AltaPaciente(nodoPaciente* arbol)
{
    PACIENTE x;
    printf("Ingrese DNI del Paciente:  ");
    fflush(stdin);
    gets(x.dni);
    while(!validarDNI(x.dni))
    {
        printf("\nDNI NO VALIDO \nIngrese nuevamente:  ");
        fflush(stdin);
        gets(x.dni);
    }
    PACIENTE aux= buscarPacienteArchivo(archivoPacientes,x.dni);
    if(aux.edad != -1)
    {
        if(aux.eliminado==0)
        {
            printf("El Paciente que ingreso ya existe en la base de datos, puede modificarlo desde el menu principal\n");
            mostrarPaciente(aux);
        }
        else
        {
            printf("�El Paciente se encontraba dado de baja, Ahora se encuentra dado de alta!\n");
            mostrarPaciente(aux);
            aux.eliminado=0;
            CambiarEliminadoPaciente(0,aux,archivoPacientes);
            arbol = agregarPacienteArbol(arbol,aux);
        }
    }
    else
    {
        x=cargarPaciente(x.dni);
        arbol = agregarPacienteArbol(arbol,x);
        cargarArchivoPacientes(archivoPacientes,x);
    }

   return arbol;
}




PACIENTE cargarPaciente(char dni[])
{
    PACIENTE x;
    strcpy(x.dni, dni);
    x.eliminado = 0;
    printf("\nIngrese edad del paciente: ");
    fflush(stdin);
    while(scanf("%i", &x.edad) != 1 || !validarEdad(x.edad))
    {
        printf("\nError al ingresar edad - Ingrese nuevamente edad del paciente: ");
        fflush(stdin);
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

nodoPaciente * buscarPaciente(nodoPaciente * arbol, char dni[9])
{
    if(arbol)
    {
        if(strcmp(arbol->paciente.dni, dni) == 0)
            return arbol;
        else if(strcmp(arbol->paciente.dni, dni) < 0)
            return buscarPaciente(arbol->izq, dni);
        else
            return buscarPaciente(arbol->der, dni);
    }
    return NULL;
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

void cargarArchivoPacientes(char nombreArch[],PACIENTE x)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(PACIENTE), 1, buffer);
        fclose(buffer);
    }
}

void CambiarEliminadoPaciente(int valor, PACIENTE x, char nombreArch[])
{
    x.eliminado = valor;
    FILE * buffer = fopen(nombreArch, "r+b");
    PACIENTE aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PACIENTE), 1, buffer) > 0)
        {
            if(strcmp(aux.dni, x.dni) == 0)
            {
                fseek(buffer, -1 * sizeof(PACIENTE), SEEK_CUR);
                fwrite(&x, sizeof(PACIENTE), 1, buffer);
            }
        }
        fclose(buffer);
    }
}

PACIENTE buscarPacienteArchivo(char nombreArch[], char dni[])
{
    FILE * buffer = fopen(nombreArch, "rb");
    PACIENTE aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PACIENTE), 1, buffer) > 0)
        {
            if(strcmp(aux.dni, dni) == 0)
                return aux;
        }
        fclose(buffer);
    }
    aux.edad = -1;
    return aux;
}

nodoPaciente * agregarPacienteArbol(nodoPaciente * arbol, PACIENTE x)
{
    if (!arbol)
        return crearNodoPaciente(x);

    if (strcmp(arbol->paciente.dni, x.dni) > 0)
        arbol->izq = agregarPacienteArbol(arbol->izq, x);
    else if (strcmp(arbol->paciente.dni, x.dni) < 0)
        arbol->der = agregarPacienteArbol(arbol->der, x);

    return arbol;
}

nodoPaciente * bajaPaciente(nodoPaciente * arbol)
{
    char dni[9];
    printf("Ingrese DNI del Paciente a dar de baja:  ");
    fflush(stdin);
    gets(dni);
    while(!validarDNI(dni))
    {
        printf("\nDNI NO VALIDO \nIngrese nuevamente:  ");
        fflush(stdin);
        gets(dni);
    }
    nodoPaciente * nodo = buscarPaciente(arbol, dni);
    if(nodo)
    {
        if(nodo->listaIngresos == NULL)
        {
            CambiarEliminadoPaciente(1,nodo->paciente,archivoPacientes);
            arbol = eliminarNodoPaciente(arbol, nodo);
        }
        else
        {
            printf("\nERROR--El paciente tiene ingresos asignados\n");
            printf("Si desea darlo de baja, debera dar de baja sus ingresos en el menu\n");
        }
    }
    else
        printf("\nERROR-- El paciente no existe o ya fue dado de baja\n");

     return arbol;
}

nodoPaciente * eliminarNodoPaciente(nodoPaciente * arbol, nodoPaciente * nodo)
{
    if (arbol == NULL)
        return NULL;

    else
    {
        /// el nodo a eliminar ha sido encontrado (NO FUE NI MENOR NI MAYOR)
        /// Caso 1: Nodo sin hijos o un solo hijo (los mas sencillos)
        if (nodo->izq == NULL)
        {
            nodoPaciente* temp = nodo->der;
            free(nodo);
            return temp;
        }
        else if (nodo->der == NULL)
        {
            nodoPaciente* temp = nodo->izq;
            free(nodo);
            return temp;
        }

        /// Caso 2: Nodo con dos hijos
        /// Encontrar el sucesor inmediato (nodo m�s a la izquierda en el sub�rbol derecho)
        nodoPaciente* temp = encontrarMenorArbolPaciente(nodo->der);///funcion complementaria...

        /// Copiar el valor del sucesor inmediato al nodo actual
        nodo->paciente = temp->paciente;

        /// Eliminar el sucesor inmediato
        nodo->der = eliminarNodoPaciente(nodo->der, temp);
    }

    return arbol;
}
