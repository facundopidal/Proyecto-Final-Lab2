#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "empleados.h"

void altaEmpleado(char nombreArch[])
{
    printf("Ingrese dni del nuevo empleado: ");
    char * dni = leerDNI();
    EMPLEADO aux = buscarEmpleado(dni, nombreArch);
    if(aux.tipoPerfil == -1)
    {
        aux = cargarEmpleado(dni);
        cargarArchivoEmpleados(aux, nombreArch);
        printf("Se creo el empleado correctamente: \n");
        mostrarEmpleado(aux);
    }
    else
        printf("\nERROR El empleado ya existe en el archivo\n\n");

}


void bajaEmpleado(char nombreArch[])
{
    printf("Ingrese dni del empleado a dar de baja: ");
    char * dni = leerDNI();
    char eliminar;
    EMPLEADO aux = buscarEmpleado(dni, nombreArch);
    if(aux.tipoPerfil > 0)
    {
        printf("Esta seguro de que quiere eliminar el usuario: \n");
        mostrarEmpleado(aux);
        printf("Ingrese S para eliminarlo definitivamente\nIngrese otra tecla para cancelar");
        printf("--> \n");
        fflush(stdin);
        scanf("%c", &eliminar);
        if(eliminar == 'S')
        {
            eliminarUsuario(dni, nombreArch);
            printf("El usuario se elimino correctamente\n");
        }
        else
            printf("El usuario NO se elimino\n");
    }
    else
        printf("No se encontro el usuario\n");
}

void modificarEmpleado(char nombreArch[])
{
    printf("Ingrese dni del empleado a modificar: ");
    char * dni = leerDNI();
    EMPLEADO aux = buscarEmpleado(dni, nombreArch);
    if(aux.tipoPerfil > 0)
    {
        int opcion;
        do
        {
            system("cls");
            mostrarEmpleado(aux);
            printf("Ingrese:\n(1) Editar Nombre\n(2) Editar Apellido \n(3) Editar Tipo de Empleado\n(00) Salir\n");
            printf("--> ");
            scanf("%i", &opcion);
            switch(opcion)
            {
            case 1:
                printf("Ingrese nuevo Nombre: ");
                fflush(stdin);
                gets(aux.nombre);
                while(!validarPalabras(aux.nombre,DIM_NOMBRE))
                {
                    printf("Nombre NO VALIDO\n Ingrese nuevamente:  ");
                    fflush(stdin);
                    gets(aux.nombre);
                }
                system("pause");
                break;
            case 2:
                printf("Ingrese nuevo Apellido: ");
                fflush(stdin);
                gets(aux.apellido);
                while(!validarPalabras(aux.apellido,DIM_APELLIDO))
                {
                    printf("Apellido NO VALIDO\n Ingrese nuevamente:  ");
                    fflush(stdin);
                    gets(aux.apellido);
                }
                system("pause");
                break;
            case 3:
                printf("Ingrese el  nuevo tipo de perfil del empleado \n(1) Profesional\n(2) Administrativo\n");
                printf("--> ");
                fflush(stdin);
                scanf("%i", &aux.tipoPerfil);
                while(aux.tipoPerfil != 1 && aux.tipoPerfil != 2)
                {
                    printf("Tipo de perfil NO VALIDO\n Ingrese nuevamente\n");
                    printf("--> ");
                    fflush(stdin);
                    scanf("%i", &aux.tipoPerfil);
                }
                system("pause");
                break;
            case 00:
                printf("Saliendo...");
                system("pause");
                break;
            default:
                printf("Por favor ingrese una opcion correcta");
                system("pause");
                break;
            }
        }
        while(opcion != 00);
    }
    else
        printf("No se encontro el usuario\n");
}
EMPLEADO cargarEmpleado(char dni[])
{
    EMPLEADO x;
    strcpy(x.dni, dni);

    ///APELLIDO
    printf("Ingrese Apellido: ");
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
    while(!validarPalabras(x.nombre,DIM_NOMBRE))
    {
        printf("Nombre NO VALIDO\n Ingrese nuevamente:  ");
        fflush(stdin);
        gets(x.nombre);
    }

    ///TIPO PERFIL
    printf("Ingrese el tipo de perfil del empleado \n(1) Profesional\n(2) Administrativo\n");
    printf("--> ");
    fflush(stdin);
    scanf("%i", &x.tipoPerfil);
    while(x.tipoPerfil != 1 && x.tipoPerfil != 2)
    {
        printf("Tipo de perfil NO VALIDO\n Ingrese nuevamente\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i", &x.tipoPerfil);
    }

    ///PASSWORD
    strcpy(x.password, generarPassword());
    printf("\nLa contrase%ca se autocompleto con: %s\n\n", 164, x.password);

    return x;
}

EMPLEADO buscarEmpleado(char dni[], char nombreArch[])
{
    FILE * buffer = fopen(nombreArch, "rb");
    EMPLEADO aux;
    int flag = 0;
    if(buffer)
    {
        while(fread(&aux, sizeof(EMPLEADO), 1, buffer) > 0)
        {
            if(dnicmp(aux.dni, dni) == 0)
                flag = 1;
        }
        fclose(buffer);
    }
    if(flag == 0)
        aux.tipoPerfil = -1;

    return aux;
}

void cargarArchivoEmpleados(EMPLEADO x, char nombreArch[])
{
    FILE * buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(EMPLEADO), 1, buffer);
        fclose(buffer);
    }
}

void mostrarEmpleado(EMPLEADO x)
{
    printf("------------------------\n");
    printf("DNI: %s\n", x.dni);
    printf("Nombre: %s\n", x.nombre);
    printf("Apellido: %s\n", x.apellido);
    printf("Contrase%ca: %s\n", 164, x.password);
    printf("Tipo de empleado: %s\n", tipoEmpleado(x.tipoPerfil));
    printf("------------------------\n");
}

char * tipoEmpleado(int tipo)
{
    if(tipo == 0)
        return "ADMIN";
    if(tipo == 1)
        return "PROFESIONAL";
    if(tipo == 2)
        return "ADMINISTRATIVO";

    return "ERROR";
}

void eliminarUsuario(char dni[], char nombreArchivo[])
{
    FILE *archivoEntrada, *archivoSalida;
    EMPLEADO aux;

    archivoEntrada = fopen(nombreArchivo, "rb");
    archivoSalida = fopen("temp.bin", "wb");
    if(archivoEntrada && archivoSalida)
    {
        while(fread(&aux, sizeof(EMPLEADO), 1, archivoEntrada) > 0)
        {
            if(dnicmp(dni, aux.dni) != 0)
                fwrite(&aux, sizeof(EMPLEADO), 1, archivoSalida);
        }

        fclose(archivoEntrada);
        fclose(archivoSalida);
    }

    remove(nombreArchivo);

    rename("temporal.bin", nombreArchivo);
}
