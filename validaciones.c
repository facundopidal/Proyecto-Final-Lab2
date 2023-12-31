#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "validaciones.h"
#include "practicas.h"
#include "menus.h"



///--------------------------------------------     DNI    ---------------------------------------------------------------------------------------------------

bool validarDNI(const char *dni)
{
    int len = strlen(dni);
    if (len < 7 || len > DIM_DNI - 1)
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

    dniValido = (char*)malloc(DIM_DNI * sizeof(char)); // Asigna memoria din�mica para el DNI
    if (dniValido != NULL)
        strcpy(dniValido, dni); // Copia el DNI v�lido a la memoria din�mica

    return dniValido;
}

int dnicmp(char * dni1, char * dni2)
{
    int len1 = strlen(dni1);
    int len2 = strlen(dni2);
    if(len1 > len2) //Compara las longitudes antes de hacer strcmp
        return 1;
    else if(len1 < len2)
        return -1;
    else
        return strcmp(dni1, dni2);
}

///--------------------------------------------     FECHA    ---------------------------------------------------------------------------------------------------

void obtenerFechaActual(int *dia, int *mes, int *anio)
{
    time_t tiempo;
    struct tm *tm_info;

    time(&tiempo);
    tm_info = localtime(&tiempo);

    *dia = tm_info->tm_mday;
    *mes = tm_info->tm_mon + 1; // A�adimos 1 porque enero es 0
    *anio = tm_info->tm_year + 1900; // A�adimos 1900 porque el a�o se cuenta desde 1900
}


bool validarFecha(const char *fecha)
{
    // Verifica la longitud de la cadena
    if (strlen(fecha) != 10)
        return false;

    // Verifica el formato dd/mm/aaaa
    if (fecha[2] != '/' || fecha[5] != '/')
        return false;

    // Extrae d�a, mes y a�o de la cadena
    int dia, mes, anio;
    if (sscanf(fecha, "%d/%d/%d", &dia, &mes, &anio) != 3)
        return false;

    // Verifica el a�o
    if (anio < 2023)
        return false;

    // Verifica el mes (debe estar en el rango 1-12)
    if (mes < 1 || mes > 12)
        return false;

    // Verifica el d�a seg�n el mes
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
        if ((anio % 4 == 0 && anio % 100 != 0) || (anio % 400 == 0))   //Pregunta si el a�o es bisiesto
        {
            if (dia < 1 || dia > 29)
                return false;  // A�o bisiesto, febrero puede tener 29 d�as
        }
        else
        {
            if (dia < 1 || dia > 28)
                return false;  // Febrero normal con 28 d�as
        }
        break;
    default:
        return false;
    }

    // Si no se encontraron problemas, la fecha es v�lida
    return true;
}


bool validarFechaPosterior(const char *fechaP, const char *fechaA)
{
    if (!validarFecha(fechaP))
        return false;  // La fecha no es v�lida

    int dia1, mes1, anio1;
    int dia2, mes2, anio2;
    sscanf(fechaP, "%d/%d/%d", &dia1, &mes1, &anio1);
    sscanf(fechaA, "%d/%d/%d", &dia2, &mes2, &anio2);

    if (anio1 > anio2)
        return true;

    else if (anio1 == anio2)
    {
        if (mes1 > mes2)
            return true;
        else if (mes1 == mes2)
        {
            if (dia1 > dia2)
                return true;
        }
    }

    return false;
}

char * leerFecha()
{
    char * fecha = (char *) malloc(DIM_FECHA * sizeof(char));
    fflush(stdin);
    fgets(fecha, DIM_FECHA + 1, stdin);
    fecha[strcspn(fecha, "\n")] = '\0';
    while(getchar() != '\n');
    while(!validarFecha(fecha))
    {
        printf("Fecha NO VALIDA \n-Ingrese una fecha valida con formato dd/mm/aaaa \n-Que sea posterior a hoy: ");
        fflush(stdin);
        fgets(fecha, DIM_FECHA + 1, stdin);
        fecha[strcspn(fecha, "\n")] = '\0';
        while(getchar() != '\n');
    }
    return fecha;
}

int fchcmp(char * fecha1, char * fecha2)
{
    int dia1, mes1, anio1;
    int dia2, mes2, anio2;
    sscanf(fecha1, "%d/%d/%d", &dia1, &mes1, &anio1);
    sscanf(fecha2, "%d/%d/%d", &dia2, &mes2, &anio2);

    if (anio1 > anio2)
        return 1;

    else if (anio1 == anio2)
    {
        if (mes1 > mes2)
            return 1;
        else if (mes1 == mes2)
        {
            if (dia1 > dia2)
                return 1;

            else if(dia1 == dia2)
                return 0;
        }
    }

    return -1;
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
        printf("NO LA ENCONTRROOOOR\n");
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
    if(edad < 0 || edad > MAX_EDAD)
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
            printf("Eso no es un numero valido. Intenta de nuevo: ");
    }
}

int generarMatricula()
{
    srand(time(NULL));
    int n = rand()% 90000 + 10000;
    return n;
}

char * generarPassword()
{
    srand(time(NULL));
    char caracteres[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    int longitud = 5;
    char* resultado = (char*)malloc((longitud + 1) * sizeof(char));

    for (int i = 0; i < longitud; ++i)
    {
        int indice = rand() % (sizeof(caracteres) - 1);
        resultado[i] = caracteres[indice];
    }

    resultado[longitud] = '\0';

    return resultado;
}

bool validarPassword(char * password)
{
    int len = strlen(password);
    if(len > DIM_PASSWORD)
        return false;
    if (password == NULL)
        return false;

    for (int i = 0; password[i] != '\0'; ++i) {
        if (!((password[i] >= '0' && password[i] <= '9') ||
              (password[i] >= 'a' && password[i] <= 'z') ||
              (password[i] >= 'A' && password[i] <= 'Z')))
            return false;
    }

    return true;
}
