#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "validaciones.h"
#include "ingresos.h"
#include "practicas.h"


///--------------------------------------------     DNI    ---------------------------------------------------------------------------------------------------

bool validarDNI(const char *dni)
{
    int len = strlen(dni);
    if (len < 7 || len > DIM_DNI)
        return false;
    for (int i = 0; i < len; i++)
    {
        if (dni[i] < '0' || dni[i] > '9')
            return false;
    }
    return true;
}


char* leerDNI()
{
    char dni[DIM_DNI];
    char* dniValido = NULL;

    fflush(stdin);
    gets(dni);

    while (!validarDNI(dni))
    {
        printf("\nDNI NO VALIDO\nIngrese nuevamente: ");
        fflush(stdin);
        gets(dni);
    }

    dniValido = (char*)malloc(DIM_DNI * sizeof(char)); // Asigna memoria dinámica para el DNI
    if (dniValido != NULL)
        strcpy(dniValido, dni); // Copia el DNI válido a la memoria dinámica

    return dniValido;
}


///--------------------------------------------     FECHA    ---------------------------------------------------------------------------------------------------

void obtenerFechaActual(int *dia, int *mes, int *anio)
{
    time_t tiempo;
    struct tm *tm_info;

    time(&tiempo);
    tm_info = localtime(&tiempo);

    *dia = tm_info->tm_mday;
    *mes = tm_info->tm_mon + 1; // Añadimos 1 porque enero es 0
    *anio = tm_info->tm_year + 1900; // Añadimos 1900 porque el año se cuenta desde 1900
}


bool validarFecha(const char *fecha)
{
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
    if (anio < 2023)
        return false;

    // Verifica el mes (debe estar en el rango 1-12)
    if (mes < 1 || mes > 12)
        return false;

    // Verifica el día según el mes
    switch (mes)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        if (dia < 1 || dia > 31)
            return false;

        break;
    case 4:
    case 6:
    case 9:
    case 11:
        if (dia < 1 || dia > 30)
            return false;

        break;
    case 2:
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))   //Pregunta si el año es bisiesto
        {
            if (dia < 1 || dia > 29)
                return false;  // Año bisiesto, febrero puede tener 29 días
        }
        else
        {
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


bool validarFechaPosterior(const char *fechaP, const char *fechaA)
{
    if (!validarFecha(fechaP))
        return false;  // Al menos una de las fechas no es válida

    int dia1, mes1, anio1;
    int dia2, mes2, anio2;
    sscanf(fechaP, "%d/%d/%d", &dia1, &mes1, &anio1);
    sscanf(fechaA, "%d/%d/%d", &dia2, &mes2, &anio2);

    if (anio1 > anio2)
    {
        return true;
    }
    else if (anio1 == anio2)
    {
        if (mes1 > mes2)
        {
            return true;
        }
        else if (mes1 == mes2)
        {
            if (dia1 > dia2)
            {
                return true;
            }
        }
    }

    return false;
}



///----------------------------------------------------    PALABRAS     --------------------------------------------------------------------------------------------------

bool validarPalabras(const char *Palabras,int rango)
{
    int len = strlen(Palabras);
    if(len > rango-1)
        return false;
    for (int i = 0; i < len; i++)
        if (!((Palabras[i] >= 'A' && Palabras[i] <= 'Z') || (Palabras[i] >= 'a' && Palabras[i] <= 'z') || Palabras[i] == ' '))
            return false;
    return true;
}



///-------------------------------------------------     TELEFONO     --------------------------------------------------------------------------------------------------------------

bool validarTelefono(const char *cadena)
{
    int longitud = strlen(cadena);
    if (longitud < 8 || longitud > DIM_TELEFONO)
        return false;
    for (int i = 0; i < longitud; i++)
        if (cadena[i] < '0' || cadena[i] > '9')
            return false;
    return true;
}


///--------------------------------------------------    EXISTENCIA   ---------------------------------------------------------------------------------------------------------

bool validarExistenciaPracticaActiva(int id, char nombreArchivo[])
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) >0)
        {
            if((aux.nro == id) && (aux.eliminado == 0))
                return true;
        }
        fclose(buffer);
    }
    return false;
}

bool validarExistenciaPractica(int id, char nombreArchivo[])
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) >0)
        {
            if((aux.nro == id))
                return true;
        }
        fclose(buffer);
    }
    return false;
}

bool validarPracticaRepetida(char nombre[DIM_NPRACTICA], char nombreArchivo[])/// TRUE si esta repetida
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    PRACTICA aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) >0)
        {
            if(strcmpi(aux.nombrePractica,nombre)==0)
                return true;
        }
        fclose(buffer);
    }
    return false;
}
///----------------------------------------------    NUMEROS     -----------------------------------------------------------------------------------------------------------

bool validarEdad(int edad)
{
    if(edad < 0 || edad > DIM_EDAD)
        return false;
    return true;
}


int leerEnteroPositivo()
{
    int entero;
    while(true)
    {
        fflush(stdin);
        if((scanf("%i", &entero) == 1) && (entero > 0))
            return entero;
        else
            printf("Eso no es un numero valido. Intenta de nuevo.\n");
    }
}
