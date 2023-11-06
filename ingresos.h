#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED
#include "pacientes.h"
typedef struct{
    int ID;
    char fechaIngreso[10];
    char fechaRetiro[10];
    char dni[DIM_DNI];
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

///-------------------------------------    PRINCIPALES   -----------------------------------------------------------------------------------------------------------------------------

nodoPaciente * altaIngreso(nodoPaciente * arbol, char nombreArchivoPxI[], char nombreArchivoIngresos[]);
nodoPaciente * bajaIngreso(nodoPaciente * arbol, char nombreArchivo[]);

///-------------------------------------    MOSTRAR    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarIngreso(INGRESO x);
void mostrarIngresosPaciente(nodoPaciente * paciente);
void mostrarPxi(PRACTICAxINGRESO pxi);
void mostrarIngresoYPracticas(nodoIngreso * x);

///-------------------------------------    ARCHIVO    --------------------------------------------------------------------------------------------------------------------------------------

void cambiarEliminadoIngreso(int valor, INGRESO x, char nombreArch[]);
void cargarArchivoIngresos(char nombreArch[],INGRESO x);
void cargarArchivoPxI(char nombreArch[],nodoPxI * lista);

///-------------------------------------    AUXILIARES    --------------------------------------------------------------------------------------------------------------------------------

INGRESO cargarIngreso(int id, char dni[]);
nodoIngreso * crearNodoIngreso(INGRESO ing);
nodoIngreso * agregarPpioIngreso(nodoIngreso * lista, nodoIngreso * nodo);
nodoIngreso * altaListaIngreso(nodoIngreso * lista, char dni[]);
nodoIngreso * buscarIngreso(nodoIngreso * lista, int id);
nodoIngreso * eliminarNodoIngreso(nodoIngreso * lista, nodoIngreso * nodo);
PRACTICAxINGRESO cargarPxI(int idIngreso);
nodoPxI * altaListaPxI(nodoPxI * lista, int idIngreso);
nodoPxI * crearNodoPxI(PRACTICAxINGRESO pxi);
nodoPxI * agregarPpioPxI(nodoPxI * lista, nodoPxI * nodo);


#endif // INGRESOS_H_INCLUDED
