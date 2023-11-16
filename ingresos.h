#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED
#include "pacientes.h"
#define archivoIngresos "ingresos.bin" //constante de archivoIngresos
#define archivoPxI "pxi.bin" //constante de archivoPxI

typedef struct{
    int ID;
    char fechaRetiro[DIM_FECHA];
    int matricula;
    char fechaIngreso[DIM_FECHA];
    int eliminado;
    char dni[DIM_DNI];
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
    char resultado[DIM_RESULTADO];
}PRACTICAxINGRESO;


typedef struct nodoPxI{
    struct nodoPxI* sig;
    PRACTICAxINGRESO PxI;
}nodoPxI;

///-------------------------------------    CARGAR ARBOL   -----------------------------------------------------------------------------------------------------------------------------

nodoIngreso * crearListaIngresos(nodoPaciente * arbol, char archIngresos[], char archPxI[]);
nodoPxI * crearListaPxI(nodoIngreso * ing, char archPxI[]);

///-------------------------------------    PRINCIPALES   -----------------------------------------------------------------------------------------------------------------------------

nodoPaciente * altaIngreso(nodoPaciente * arbol, char nombreArchivoPxI[], char nombreArchivoIngresos[]);
nodoPaciente * bajaIngreso(nodoPaciente * arbol, char nombreArchivo[]);
nodoPaciente * modificarIngreso(nodoPaciente * arbol, char archIngresos[], char archPxI[]);

///-------------------------------------    MOSTRAR    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarIngresosPorDNI(nodoPaciente* arbol);
void mostrarIngresosArbol(nodoPaciente* arbol);
void mostrarIngreso(INGRESO x);
void mostrarIngresosPaciente(nodoPaciente * paciente);
void mostrarPxi(PRACTICAxINGRESO pxi);
void mostrarIngresoYPracticas(nodoIngreso * x);
void mostrarPxIPaciente(nodoPaciente * arbol);
void mostrarIngresoArchivo(char nombreArchivo[]);
void mostrarPxIArchivo(char nombreArchivo[]);
void mostrarPracticasAsociadas(nodoIngreso * ing);

///-------------------------------------    ARCHIVO    --------------------------------------------------------------------------------------------------------------------------------------

void cambiarEliminadoIngreso(int valor, INGRESO x, char nombreArch[]);
void cargarArchivoIngresos(char nombreArch[],INGRESO x);
void cargarArchivoPxI(char nombreArch[],nodoPxI * lista);
int obternerIdIngresoArchivo(char nombreArchivo[]);
void modificarArchivoIngresos(char nombreArch[], INGRESO x);
void modificarArchivoPxI(char nombreArch[], PRACTICAxINGRESO pxi, int nroPract);
void cambiarEliminadoPxI(PRACTICAxINGRESO pxi,char nombreArchivo[]);

///-------------------------------------    AUXILIARES    --------------------------------------------------------------------------------------------------------------------------------

INGRESO cargarIngreso(int id, char dni[]);
nodoIngreso * crearNodoIngreso(INGRESO ing);
nodoIngreso * agregarPpioIngreso(nodoIngreso * lista, nodoIngreso * nodo);
nodoIngreso * altaListaIngreso(nodoIngreso * lista, char dni[],char nombreArchivo[]);
nodoIngreso * buscarIngreso(nodoIngreso * lista, int id);
nodoIngreso * eliminarNodoIngreso(nodoIngreso * lista, nodoIngreso * nodo);
nodoPxI * eliminarNodoPxI(nodoPxI * lista, nodoPxI * nodo);
PRACTICAxINGRESO cargarPxI(int idIngreso);
nodoPxI* liberarListaPxI(nodoPxI* lista);
nodoPxI * altaListaPxI(nodoPxI * lista, int idIngreso);
nodoPxI * crearNodoPxI(PRACTICAxINGRESO pxi);
nodoPxI * agregarPpioPxI(nodoPxI * lista, nodoPxI * nodo);
nodoPxI * buscarPxI(nodoPxI * lista, int nroPract);
nodoIngreso * modificarPxI(nodoIngreso * ingresoAMod, char nombreArch[]);
nodoPxI * bajaPxI(nodoIngreso * listaIngresos,nodoIngreso * ingresoAMod, char archPxI[]);
bool pxiRepetida (nodoPxI* lista, int giorgio);
#endif // INGRESOS_H_INCLUDED
