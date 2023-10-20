#include <stdio.h>
#include <stdlib.h>
///#include "clientes.h"
#include <stdbool.h>
#include "string.h"

///--------------------------------------------------Estructuras Clientes --------------------------------------------------------------------------------------

typedef struct{
    char DNI[9];
    char Apellido[20];
    char Nombre[20];
    char mail[40];
    ///char FechaNac[];
}CLIENTE;

typedef struct nodoCliente{
    struct nodoCliente* izq;
    struct nodoCliente* der;
    struct nodoIngreso* ingresos;
    CLIENTE cliente;
}nodoCliente;

///-------------------------------------------------------------------------------------------------------------------------------------------



///----------------------------------------------------Prototipados----------------------------------------------------------------

//nodoCliente* crearNodoCliente(CLIENTE x);












///-------------------------------------------------------------------------------------------------------------------------------------




typedef struct{

    int ID;
    char DNI[9];
    ///fecha
}INGRESO;

typedef struct nodoIngreso{
    struct nodoIngreso* ant;
    struct nodoIngreso* sig;
    struct nodoPractica* practicas;
    INGRESO ingreso;
}nodoIngreso;

typedef struct{
    int ID;
    char estudio[20];
    char Resultado[40];
}PRACTICA;

typedef struct nodoPractica{
    PRACTICA practica;
    struct nodoPractica* sig;
}nodoPractica;

int main()
{
    return 0;
}

nodoCliente* crearNodoCliente(CLIENTE x)
{
    nodoCliente* NNC=(nodoCliente*)malloc(sizeof(nodoCliente));
    strcpy(NNC->cliente.Apellido,x.Apellido);
    strcpy(NNC->cliente.Nombre,x.Nombre);
    strcpy(NNC->cliente.DNI,x.DNI);
    strcpy(NNC->cliente.mail,x.mail);
    ///strcpy(NNC->cliente.FechaNac,x.FechaNac);
    NNC->izq=NULL;
    NNC->der=NULL;
 return NNC;
}

CLIENTE cargarCliente()
{
    CLIENTE x;
    ///DNI
    printf("Ingrese DNI:  ");
    fflush(stdin);
    scanf("%s",&x.DNI);
    while(!validarDNI(x.DNI))
    {
    printf("\nDNI NO VALIDO \nIngrese nuevamente:  ");
    fflush(stdin);
    gets(x.DNI);
    }
    ///APELLIDO
    printf("\nIngrese APELLIDO: ");
    fflush(stdin);
    gets(x.Apellido);
    while(!validarPalabras(x.Apellido))
    {
    printf("\nAPELLIDO NO VALIDO\n Ingrese nuevamente:  ");
    fflush(stdin);
    gets(x.Apellido);
    }
    ///NOMBRE
    printf("\nIngrese NOMBRE: ");
    fflush(stdin);
    gets(x.Nombre);
    while(!validarPalabras(x.Nombre))
    {
    printf("\nNOMBRE NO VALIDO\n Ingrese nuevamente:  ");
    fflush(stdin);
    gets(x.Nombre);
    }
    ///MAIL
    printf("\nIngrese MAIL: ");
    fflush(stdin);
    gets(x.Nombre);
    ///FECHA NACIMIENTO

return x;
}

bool validarDNI(const char *dni) {
    int len = strlen(dni);
    if (len < 7 || len > 9) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (dni[i] < '0' || dni[i] > '9') {
            return false;
        }
    }
    return true;
}

bool validarPalabras(const char *Palabras) {
    int len = strlen(Palabras);
    for (int i = 0; i < len; i++)
        if (!((Palabras[i] >= 'A' && Palabras[i] <= 'Z') || (Palabras[i] >= 'a' && Palabras[i] <= 'z') || Palabras[i] == ' '))
            return false;
    return true;
}
