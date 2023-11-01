#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"

INGRESO cargarIngreso(int id, char dni[])
{
    INGRESO x;

    strcpy(x.dni, dni);

    x.ID = id;

    x.eliminado = 0;

    ///Matricula
    printf("Ingrese matricula del medico:  ");
    fflush(stdin);
    scanf("%i",&x.matricula);

    ///Fecha de ingreso

    int dia,mes,anio;
    obtenerFechaActual(&dia, &mes, &anio);
    sprintf(x.fechaIngreso, "%i/%i/%i", dia, mes, anio);
    printf("La fecha de ingreso se completo con la del dia de hoy: %s", x.fechaIngreso);

    ///Fecha de retiro
    printf("Ingrese fecha de retiro con formato dd/mm/aaaa:  ");
    fflush(stdin);
    gets(x.fechaRetiro);
    while(!validarFechaPosterior(x.fechaRetiro, x.fechaIngreso)) //Valida que la sea sea posterior, no incluye mismo dia
    {
        printf("\nFECHA NO VALIDA \n-Ingrese una fecha valida con formato dd/mm/aaaa \n-Que sea posterior a hoy: ");
        fflush(stdin);
        gets(x.fechaRetiro);
    }
    printf("\n");

    return x;
}

nodoPaciente * altaIngreso(nodoPaciente * arbol)
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

    nodoPaciente * paciente = buscarPaciente(arbol, dni);

    if(paciente != NULL) //Si el dni no es valido se vuelve al menu
    {
        printf("No se encontro el paciente, debe darlo de alta en el menu principal");
        printf("Seleccione la opcion de CARGAR PACIENTE ");
        return arbol;
    }
    printf("Se encontro el paciente, cargue el ingreso"); //Cargamos el ingreso

    paciente->listaIngresos = altaListaIngreso(paciente->listaIngresos, dni); //carga el ingreso completo solo en la lista

    paciente->listaIngresos->listaPxI = altaListaPxI(paciente->listaIngresos->listaPxI, paciente->listaIngresos->ingreso.ID); //carga pxi(puede ser mas de una) solo en la lista

    cargarArchivoPxI(archivoPxI, paciente->listaIngresos->listaPxI); //Se pasa la lista para ser recorrida en la funcion
    cargarArchivoIngresos(archivoIngresos, paciente->listaIngresos->ingreso); //Guardamos los datos en el archivo

    return arbol;
}

nodoIngreso * altaListaIngreso(nodoIngreso * lista, char dni[])
{
    int idAnt = 0;
    if(lista != NULL)
        idAnt = lista->ingreso.ID;  //Se toma el ultimo id como el primero, ya que agregamos al principio
    INGRESO aux = cargarIngreso(idAnt + 1, dni);
    lista = agregarPpioIngreso(lista, crearNodoIngreso(aux)); //añadimos ingreso a la lista

    return lista;
}


nodoIngreso * crearNodoIngreso(INGRESO ing)
{
    nodoIngreso * nodo = (nodoIngreso *) malloc(sizeof(nodoIngreso));
    nodo->ant = NULL;
    nodo->sig = NULL;
    nodo->ingreso = ing;
    nodo->listaPxI = NULL;
    return nodo;
}

nodoIngreso * agregarPpioIngreso(nodoIngreso * lista, nodoIngreso * nodo)
{
    if(!lista)
        return nodo;
    else
    {
        nodo->sig = lista;
        lista->ant = nodo;
        return nodo;
    }
}

PRACTICAxINGRESO cargarPxI(int idIngreso)
{
    PRACTICAxINGRESO pxi;
    pxi.idIngreso = idIngreso; //cargamos id de ingreso
    mostrarPracticasArch(archivoPracticas);
    printf("Ingrese el id de practica que desea: ");
    fflush(stdin);
    scanf("%i", &pxi.nroPractica);
    while(!validarExistenciaPracticaActiva(pxi.nroPractica, archivoPracticas)) //buscamos la practica en el archivo
    {
        mostrarPracticasArch(archivoPracticas);
        printf("ID NO VALIDO\n Por favor ingrese uno de los mostrados en pantalla: ");
        fflush(stdin);
        scanf("%i", &pxi.nroPractica);
    }
    strcpy(pxi.resultado, "Pendiente"); //Ponemos resultado en pendiente por defecto para luego completar
    return pxi;
}

nodoPxI * altaListaPxI(nodoPxI * lista, int idIngreso)
{
    char seguir = 's';
    while(seguir == 's' || seguir == 'S')
    {
        lista = agregarPpioPxI(lista, crearNodoPxI(cargarPxI(idIngreso)));
        printf("Ingrese s para cargar otra practica: ");
        fflush(stdin);
        scanf("%c", &seguir);
    }
    return lista;
}

nodoPxI * crearNodoPxI(PRACTICAxINGRESO pxi)
{
    nodoPxI *nodo = (nodoPxI *) malloc(sizeof(nodoPxI));
    nodo->sig = NULL;
    nodo->PxI = pxi;
    return nodo;
}

nodoPxI * agregarPpioPxI(nodoPxI * lista, nodoPxI * nodo)
{
    if(lista)
        return nodo;
    else
    {
        nodo->sig = lista;
        return nodo;
    }
}

void cargarArchivoIngresos(char nombreArch[],INGRESO x)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(INGRESO), 1, buffer);
        fclose(buffer);
    }
}

void cargarArchivoPxI(char nombreArch[],nodoPxI * lista)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        while(lista)
        {
            fwrite(&lista->PxI, sizeof(PRACTICAxINGRESO), 1, buffer);
            lista = lista->sig;
        }
        fclose(buffer);
    }
}


