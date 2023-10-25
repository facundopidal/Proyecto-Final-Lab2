#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED
#include "pacientes.h"
typedef struct{
    int ID;
    char fechaIngreso[10];
    char fechaRetiro[10];
    char dni[9];
    int matricula;
    int eliminado;
}INGRESO;

typedef struct nodoIngreso{
    struct nodoIngreso* ant;
    struct nodoIngreso* sig;
    struct nodoPxI* listaPxI;
    INGRESO ingreso;
}nodoIngreso;

typedef struct{
    int idIngreso;
    int nroPractica;
    char resultado[40];
}PRACTICAxINGRESO;


typedef struct nodoPxI{
    struct nodoPxI* sig;
    PRACTICAxINGRESO PxI;
}nodoPxI;

#define archivoIngresos "ingresos.bin" //constante de archivoIngresos
#define archivoPxI "pxi.bin" //constante de archivoPxI

///Funciones Ingreso
INGRESO cargarIngreso(int id, char dni[]);
nodoPaciente * altaIngreso(nodoPaciente * arbol);
nodoIngreso * crearNodoIngreso(INGRESO ing);
nodoIngreso * agregarPpioIngreso(nodoIngreso * lista, nodoIngreso * nodo);
nodoIngreso * altaListaIngreso(nodoIngreso * lista, char dni[]);
void cargarArchivoIngresos(char nombreArch[],INGRESO x);



///Funciones PxI
PRACTICAxINGRESO cargarPxI(int idIngreso);
nodoPxI * altaListaPxI(nodoPxI * lista, int idIngreso);
nodoPxI * crearNodoPxI(PRACTICAxINGRESO pxi);
nodoPxI * agregarPpioPxI(nodoPxI * lista, nodoPxI * nodo);
void cargarArchivoPxI(char nombreArch[],nodoPxI * lista);



#endif // INGRESOS_H_INCLUDED
