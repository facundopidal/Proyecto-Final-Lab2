#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "clientes.h"

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
