#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ingresos.h"
#include <stdbool.h>
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

bool validarPalabras(const char *Palabras);










///-------------------------------------------------------------------------------------------------------------------------------------


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
     char * nombre = "";
     if(validarPalabras(nombre))
          printf("%s", nombre);
     else
          printf("Nombre invalido");
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

bool validarPalabras(const char *Palabras) {
    int len = strlen(Palabras);

    for (int i = 0; i < len; i++)
        if (!((Palabras[i] >= 'A' && Palabras[i] <= 'Z') || (Palabras[i] >= 'a' && Palabras[i] <= 'z') || Palabras[i] == ' '))
            return false;

    return true;
}

CLIENTE cargarCliente()
{
    CLIENTE x;
    printf("Ingrese DNI:  ");
    fflush(stdin);
    scanf("%s",&x.DNI);
}
