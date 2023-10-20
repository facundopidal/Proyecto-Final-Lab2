#include <stdio.h>
#include <stdlib.h>
#include "clientes.h"
#include "string.h"

int main()
{
    return 0;
}

nodoCliente* crearNodoCliente(CLIENTE x)
{
    nodoCliente* NNC=(nodoCliente*)malloc(sizeof(nodoCliente));
    strcpy(NNC->cliente.AyN,x.AyN);
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
    printf("Ingrese DNI:  ");
    fflush(stdin);
    scanf("%s",&x.DNI);
}

///--------------------------------------------------Estructuras Clientes --------------------------------------------------------------------------------------

typedef struct{
    char DNI[9];
    char AyN[30];
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

nodoCliente* crearNodoCliente(CLIENTE x);












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
