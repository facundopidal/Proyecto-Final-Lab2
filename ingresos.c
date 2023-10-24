#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"

INGRESO cargarIngreso()
{
    INGRESO x;
    x.eliminado = 0;
    ///Fecha de ingreso
    printf("Ingrese fecha de ingreso en formato dd/mm/aaaa:  ");
    fflush(stdin);
    gets(x.fechaIngreso);
    while(!validarFecha(x.fechaIngreso))
    {
        printf("\nFECHA NO VALIDA Ej: 04/05/2023\nIngrese nuevamente:  ");
        fflush(stdin);
        gets(x.fechaIngreso);
    }
    ///Fecha de retiro
    printf("Ingrese fecha de retiro:  ");
    fflush(stdin);
    gets(x.fechaRetiro);
    printf("\n");
    return x;
}

bool altaIngreso(nodoPaciente * arbol)
{
    char dni[9];
    printf("Ingrese dni del paciente: ");
    fflush(stdin);
    gets(dni);
    while(!validarDNI(dni))
    {
        printf("\nDNI NO VALIDO \nIngrese nuevamente:  ");
        fflush(stdin);
        gets(dni);
    }
    if(buscarPaciente(arbol, dni) != NULL) //Si el dni no es valido se vuelve al menu
    {
        printf("No se encontro el paciente, debe darlo de alta en el menu principal");
        printf("Seleccione la opcion de CARGAR PACIENTE ");
        return false;
    }
    printf("Se encontro el paciente, cargue el ingreso"); //Cargamos el ingreso
    INGRESO aux = cargarIngreso();
    strcpy(aux.dni, dni);
    nodoPaciente * paciente = buscarPaciente(arbol, dni);

    int idAnt = 0;
    if(paciente->listaIngresos != NULL)
        idAnt = paciente->listaIngresos->ingreso.ID;  //Se toma el ultimo id como el primero, ya que agregamos al principio
    aux.ID = idAnt+ 1;                 //Si la lista ingresos todavia no existe se le asigna id 1

//    paciente->listaIngresos = agregarPpio(paciente->listaIngresos, crearNodoIngreso(aux, NULL));
    ///falta agregar la estructura ingresosxpractica y ademas agregar el ingreso al archivo




}

nodoIngreso * crearNodoIngreso(INGRESO ing, nodoPxI * pxi)
{
    nodoIngreso * nodo = (nodoIngreso *) malloc(sizeof(nodoIngreso));
}
