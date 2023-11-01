#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"

///-------------------------------------    PRINCIPALES   -----------------------------------------------------------------------------------------------------------------------------

nodoPaciente* altaPaciente(nodoPaciente* arbol)
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
            printf("El Paciente que quiere agregar ya existe en la base de datos, puede modificarlo desde el menu principal\n");
            mostrarPaciente(aux);
        }
        else
        {
            printf("¡El Paciente se encontraba dado de baja, Ahora se encuentra dado de alta!\n");
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
        printf("Paciente cargado con exito\n");
        mostrarPaciente(x);
    }

    return arbol;
}



nodoPaciente * modificarPaciente(nodoPaciente * arbol)
{
    printf("Ingrese DNI del Paciente:  ");
    char * dni = leerDNI();
    nodoPaciente * pacienteAModificar = buscarPaciente(arbol, dni);
    if(pacienteAModificar)
    {
        int opcion;
        do
        {
            printf("MODIFICAR Paciente\n");
            mostrarPaciente(pacienteAModificar->paciente);
            printf("Ingrese:\n(1) Nombre y Apellido\n(2) Edad\n(3) Telefono\n(4) Direccion\n(00) Salir\n");
            scanf("%i", &opcion);
            fflush(stdin);
            switch(opcion)
            {
            case 1:
                printf("\nIngrese nuevo Apellido: ");
                fflush(stdin);
                gets(pacienteAModificar->paciente.apellido);
                while(!validarPalabras(pacienteAModificar->paciente.apellido,DIM_APELLIDO))
                {
                    printf("\nApellido NO VALIDO\n Ingrese nuevamente:  ");
                    fflush(stdin);
                    gets(pacienteAModificar->paciente.apellido);
                }

                printf("\nIngrese nuevo Nombre: ");
                fflush(stdin);
                gets(pacienteAModificar->paciente.nombre);
                while(!validarPalabras(pacienteAModificar->paciente.nombre,DIM_NOMBRE))
                {
                    printf("\nNOMBRE NO VALIDO\n Ingrese nuevamente:  ");
                    fflush(stdin);
                    gets(pacienteAModificar->paciente.nombre);
                }
                system("cls");
                printf("El nuevo nombre y apellido es: %s %s",pacienteAModificar->paciente.nombre, pacienteAModificar->paciente.apellido);
                break;
            case 2:
                printf("Ingrese la nueva edad: \n");
                fflush(stdin);
                while(scanf("%i", &pacienteAModificar->paciente.edad) != 1 || !validarEdad(pacienteAModificar->paciente.edad))
                {
                    printf("\nEdad no valida - Ingrese nuevamente edad del paciente: ");
                    fflush(stdin);
                }
                system("cls");
                printf("Se edito la edad a:%i\n", pacienteAModificar->paciente.edad);
                break;
            case 3:
                printf("\n Ingrese el nuevo Telefono");
                fflush(stdin);
                gets(pacienteAModificar->paciente.telefono);
                while(!validarTelefono(pacienteAModificar->paciente.telefono))
                {
                    printf("\nTelefono NO VALIDO\n Ingrese nuevamente:  ");
                    fflush(stdin);
                    gets(pacienteAModificar->paciente.telefono);
                }
                system("cls");
                printf("Se edito el telefono a:%s\n", pacienteAModificar->paciente.telefono);
                break;
            case 4:
                printf("\nIngrese nueva Direccion: ");
                fflush(stdin);
                gets(pacienteAModificar->paciente.direccion);
                system("cls");
                printf("Se edito la direccion a:%s\n", pacienteAModificar->paciente.direccion);
                break;
            case 00:
                modificarArchivoPacientes(archivoPacientes, pacienteAModificar->paciente);
                printf("Saliendo...\n");
                //system("pause");
                break;
            default:
                printf("No ingreso un numero valido\n");
            }
        }
        while(opcion != 00);
    }
    else
        printf("ERROR--El paciente que quiere modificar, no se encuentra en al lista de pacientes dados de alta\n");

    return arbol;
}

nodoPaciente * bajaPaciente(nodoPaciente * arbol)
{
    printf("Ingrese DNI del Paciente a dar de baja:  ");
    char * dni = leerDNI();

    nodoPaciente * nodo = buscarPaciente(arbol, dni);
    if(nodo)
    {
        if(nodo->listaIngresos == NULL)
        {
            CambiarEliminadoPaciente(1,nodo->paciente,archivoPacientes);
            arbol = eliminarNodoPaciente(arbol, nodo);
            printf("El paciente: ");
            mostrarPaciente(nodo->paciente);
            printf("\nFue dado de baja exitosamente\n");
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



///-------------------------------------    MOSTRAR    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarPaciente(PACIENTE x)
{
    printf("\nDNI: %s",x.dni);
    printf("\nApellido y Nombre: %s %s",x.apellido,x.nombre);
    printf("\nDireccion: %s",x.direccion);
    printf("\nTelefono: %s",x.telefono);
    printf("\nEdad: %i\n",x.edad);
}

void mostrarPacientesTodos(char nombreArchivo[])
{
    FILE *buffer= fopen(nombreArchivo,"rb");
    PACIENTE aux;
    if(buffer)
    {
        while(fread(&aux,sizeof(PACIENTE),1,buffer) == 1)
            mostrarPaciente(aux);
    fclose(buffer);
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

///-------------------------------------    ARCHIVO    --------------------------------------------------------------------------------------------------------------------------------------

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
    FILE * buffer = fopen(nombreArch, "r+b");
    PACIENTE aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 && fread(&aux, sizeof(PACIENTE), 1, buffer) > 0)
        {
            if(strcmp(aux.dni, x.dni) == 0)
            {
                x.eliminado = valor;
                fseek(buffer, (-1) * sizeof(PACIENTE),1);
                fwrite(&x, sizeof(PACIENTE), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}

void modificarArchivoPacientes(char nombreArch[], PACIENTE x)
{
    FILE * buffer = fopen(nombreArch, "r+b");
    PACIENTE aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 &&fread(&aux, sizeof(PACIENTE), 1, buffer) == 1)
        {
            if(strcmp(aux.dni, x.dni) == 0)
            {
                fseek(buffer, (-1) * sizeof(PACIENTE), 1);
                fwrite(&x, sizeof(PACIENTE), 1, buffer);
                flag = 1;
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



///-------------------------------------    AUXILIARES    --------------------------------------------------------------------------------------------------------------------------------


nodoPaciente* crearNodoPaciente(PACIENTE x)
{
    nodoPaciente* NNP=(nodoPaciente*)malloc(sizeof(nodoPaciente));
    NNP->paciente = x;
    NNP->listaIngresos = NULL;
    NNP->izq=NULL;
    NNP->der=NULL;
    return NNP;
}

PACIENTE cargarPaciente(char dni[])
{
    PACIENTE x;
    strcpy(x.dni, dni);
    x.eliminado = 0;
    ///APELLIDO
    printf("\nIngrese Apellido: ");
    fflush(stdin);
    gets(x.apellido);
    while(!validarPalabras(x.apellido,DIM_APELLIDO))
    {
        printf("Apellido NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.apellido);
    }
    ///NOMBRE
    printf("Ingrese Nombre: ");
    fflush(stdin);
    gets(x.nombre);
    while(!validarPalabras(x.nombre,DIM_NPRACTICA))
    {
        printf("\nNOMBRE NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.nombre);
    }
    ///DIRECCION
    printf("Ingrese Direccion: ");
    fflush(stdin);
    gets(x.direccion);
    ///TELEFONO
    printf("Ingrese Telefono: ");
    fflush(stdin);
    gets(x.telefono);
    while(!validarTelefono(x.telefono))
    {
        printf("\nTelefono NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.telefono);
    }
    printf("\nIngrese edad del paciente: ");
    fflush(stdin);
    while(scanf("%i", &x.edad) != 1 || !validarEdad(x.edad))
    {
        printf("\nEdad no valida - Ingrese nuevamente edad del paciente: ");
        fflush(stdin);
    }

    return x;
}

nodoPaciente * buscarPaciente(nodoPaciente * arbol, char dni[])
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
        /// Encontrar el sucesor inmediato (nodo más a la izquierda en el subárbol derecho)
        nodoPaciente* temp=encontrarMenorArbolPaciente(nodo->der);

        /// Copiar el valor del sucesor inmediato al nodo actual
        nodo->paciente = temp->paciente;

        /// Eliminar el sucesor inmediato
        nodo->der = eliminarNodoPaciente(nodo->der, temp);
    }

    return arbol;
}

nodoPaciente * encontrarMenorArbolPaciente(nodoPaciente * arbol)
{
    while(arbol->izq)
        arbol = arbol->izq;
    return arbol;
}




