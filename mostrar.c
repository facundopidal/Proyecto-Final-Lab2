#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "empleados.h"
#include "practicas.h"
#include "mostrar.h"


///-------------------------------------    PACIENTES    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarPaciente(PACIENTE x)
{
    printf("\nDNI: %s  ",x.dni);
    if(x.eliminado == 1)
        printf("|DADO DE BAJA|");
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
void mostrarListaP(nodoListaP * lista)
{
    nodoListaP * aux = lista;
    while(aux)
    {
        mostrarPaciente(aux->paciente);
        aux = aux->sig;
    }
}

void consultarPaciente(nodoPaciente * arbol)
{
    printf("Ingrese DNI del paciente a consultar: ");
    char * dni = leerDNI();
    nodoPaciente * paciente = buscarPaciente(arbol, dni);
    if(paciente)
    {
        printf("Se encontro el paciente, estos son sus datos:\n");
        mostrarPaciente(paciente->paciente);
        printf("Este es su historial: \n");
        mostrarIngresosPaciente(paciente);
    }
    else
        printf("Paciente no encontrado o dado de de baja\n Por favor darlo de alta en el menu principal\n");
}

///-------------------------------------    INGRESOS    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarIngresosArbol(nodoPaciente* arbol)
{
    if(arbol)
    {
        mostrarIngresosArbol(arbol->izq);
        mostrarIngresosPaciente(arbol);
        mostrarIngresosArbol(arbol->der);
    }
}

void mostrarIngresosPorDNI(nodoPaciente* arbol)
{
    char dni[DIM_DNI];
    printf("Ingrese el dni del paciente: ");
    strcpy(dni,leerDNI());
    nodoPaciente* paciente= buscarPaciente(arbol,dni);
    if(paciente)
        mostrarIngresosPaciente(paciente);
    else
        printf("ERROR-- No se encontro el paciente\n");
}


void mostrarIngreso(INGRESO x)
{
    printf("\n");
    if(x.eliminado==1)
        printf("ID de Ingreso: %i |DADO DE BAJA|\n",x.ID);
    else
        printf("ID de Ingreso: %i\n",x.ID);
    printf("Fecha de Ingreso: %s\n",x.fechaIngreso);
    printf("Fecha de Retiro: %s\n",x.fechaRetiro);
    printf("Matricula: %i\n",x.matricula);
    printf("-------------------------------------\n");
}

void mostrarIngresosPaciente(nodoPaciente * paciente)
{
    nodoIngreso * aux = paciente->listaIngresos;
    if(!aux)
        printf("\nEl paciente %s %s no tiene ingresos asignados\n\n", paciente->paciente.nombre, paciente->paciente.apellido);
    while(aux)
    {
        mostrarIngreso(aux->ingreso);
        aux = aux->sig;
    }
}

void mostrarPxi(PRACTICAxINGRESO pxi)
{
    printf("%c   Nro de practica: %i\n", 220,pxi.nroPractica);
    printf("    Nombre de practica: %s\n", obtenerNombrePractica(pxi.nroPractica, archivoPracticas));
    printf("    Resultado: %s\n",pxi.resultado);
    printf("  ------------------------\n");
}

void mostrarIngresoYPracticas(nodoIngreso * x)
{
    nodoIngreso * aux = x;
    mostrarIngreso(aux->ingreso);
    nodoPxI * seg = aux->listaPxI;
    printf("Practicas asociadas:\n");
    printf("  ------------------------\n");
    while(seg)
    {
        mostrarPxi(seg->PxI);
        seg = seg->sig;
    }
}

void mostrarPxIPaciente(nodoPaciente * arbol)
{
    char dni[DIM_DNI];
    printf("Ingrese dni del paciente: ");
    strcpy(dni, leerDNI());
    nodoPaciente * aux = buscarPaciente(arbol, dni);
    nodoIngreso * seg = aux->listaIngresos;
    if(aux)
    {
        if(seg)
            printf("Todos los ingresos del paciente %s %s: \n", aux->paciente.nombre, aux->paciente.apellido);
        else
            printf("\nEl paciente %s %s no tiene ingresos asignados\n\n", aux->paciente.nombre, aux->paciente.apellido);
        while(seg)
        {
            mostrarIngresoYPracticas(seg);
            seg = seg->sig;
        }
    }
    else
        printf("El paciente no se encontro\n");
}

void mostrarIngresoArchivo(char nombreArchivo[])
{
    FILE* buffer = fopen(nombreArchivo, "rb");
    INGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(INGRESO), 1, buffer) == 1)
        {
            printf("DNI DE PACIENTE: %s\n", aux.dni);
            mostrarIngreso(aux);
        }
        fclose(buffer);
    }
}

void mostrarPxIArchivo(char nombreArchivo[])
{
    FILE* buffer = fopen(nombreArchivo, "rb");
    PRACTICAxINGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICAxINGRESO), 1, buffer) == 1)
        {
            printf("Id de ingreso: %i\n", aux.idIngreso);
            mostrarPxi(aux);
        }

        fclose(buffer);
    }
}

void mostrarPracticasAsociadas(nodoIngreso * ing)
{
    nodoPxI * aux = ing->listaPxI;
    while(aux)
    {
        mostrarPxi(aux->PxI);
        aux = aux->sig;
    }
}

void consultarIngreso(nodoPaciente * arbol)
{
    int opcion;
    do
    {
        system("cls");
        printf("%c Consultar Ingreso\n", 85);
        printf("1. Filtrar por fechas\n");
        printf("2. Buscar por fecha de ingreso\n");
        printf("3. Buscar por ID de ingreso\n");
        printf("00. Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i", &opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            filtrarIngresosPorFecha(arbol);
            system("pause");
            break;
        case 2:
            mostrarIngresosPorFecha(arbol);
            system("pause");
            break;
        case 3:
            mostrarIngresoPorID(arbol);
            system("pause");
            break;
        case 00:
            printf("Saliendo...");
            system("pause");
            break;
        default:
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}

void mostrarIngresoPorID(nodoPaciente * arbol)
{
    printf("Ingrese el ID del Ingreso a mostrar: ");
    int id = leerEnteroPositivo();
    nodoIngreso * juan = mostrarIngresoPorIDArbol(arbol, id);
    if(juan)
        mostrarIngreso(juan->ingreso);
    else
        printf("El ID que ingreso no pertenece a un ingreso valido\n");
}

nodoIngreso * mostrarIngresoPorIDArbol(nodoPaciente * arbol, int id)
{
    nodoIngreso * nodo = NULL;
    nodoIngreso * aux;
    if(arbol)
    {
        nodo = mostrarIngresoPorIDArbol(arbol->izq, id);
        aux = arbol->listaIngresos;
        while(aux)
        {
            if(aux->ingreso.ID == id)
                nodo = aux;
            aux = aux->sig;
        }
        if(!nodo)
            nodo = mostrarIngresoPorIDArbol(arbol->der, id);
    }
    return nodo;
}

void mostrarIngresosPorFecha(nodoPaciente * arbol)
{
    printf("Ingrese la fecha de los ingresos a mostrar con formato dd/mm/aaaa: ");
    char * fecha = leerFecha();

    mostrarIngresosPorFechaArbol(arbol, fecha);
}

void mostrarIngresosPorFechaArbol(nodoPaciente * arbol, char * fecha)
{
    nodoIngreso * aux;
    if(arbol)
    {
        mostrarIngresosPorFechaArbol(arbol->izq, fecha);
        aux = arbol->listaIngresos;
        while(aux)
        {
            if(strcmp(aux->ingreso.fechaIngreso, fecha) == 0)///Falta mejorar obtenerFechaActual
                mostrarIngreso(aux->ingreso);
            aux = aux->sig;
        }
        mostrarIngresosPorFechaArbol(arbol->der, fecha);
    }
}


void filtrarIngresosPorFecha(nodoPaciente * arbol)
{
    printf("Fecha desde (formato dd/mm/aaaa): ");
    char * fechaD = leerFecha();
    printf("Fecha hasta (formato dd/mm/aaaa): ");
    char * fechaH = leerFecha();
    while(!validarFechaPosterior(fechaD, fechaH))
    {
        printf("Fecha Hasta NO VALIDA\n Ingrese una fecha que sea posterior a la primera: ");
        fechaH = leerFecha();
    }
    filtrarIngresosPorFechaArbol(arbol, fechaD, fechaH);
}

void filtrarIngresosPorFechaArbol(nodoPaciente * arbol, char * fechaD, char * fechaH)
{
    nodoIngreso * aux;
    if(arbol)
    {
        filtrarIngresosPorFechaArbol(arbol->izq, fechaD, fechaH);
        aux = arbol->listaIngresos;
        while(aux)
        {
            if(fchcmp(aux->ingreso.fechaIngreso, fechaD) >= 0 && fchcmp(aux->ingreso.fechaIngreso, fechaH) <= 0)
            {
                mostrarPaciente(arbol->paciente);
                mostrarIngreso(aux->ingreso);
            }
            aux = aux->sig;
        }
        filtrarIngresosPorFechaArbol(arbol->der, fechaD, fechaH);
    }
}

///-------------------------------------    EMPLEADOS    ----------------------------------------------------------------------------------------------------------------------------------------

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

///-------------------------------------    PRACTICAS    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarPractica(PRACTICA x)
{
    printf("-----------------------------------\n");
    printf("ID:%i ",x.nro);
    printf("%s",x.nombrePractica);
    if(x.eliminado==1)
        printf(" |DADA DE BAJA| \n");
    else
        printf("\n");
    printf("-----------------------------------\n");
}

void mostrarPracticasArch(char nombreArchivo[])
{
    FILE *buffer = fopen(nombreArchivo, "rb");
    if(buffer)
    {
        PRACTICA aux;
        printf("PRACTICAS CARGADAS EN EL SISTEMA\n");
        while(fread(&aux, sizeof(PRACTICA), 1, buffer) > 0)
        {
            mostrarPractica(aux);
        }
        fclose(buffer);
    }
}
