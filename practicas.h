#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

#define archivoPracticas "practicas.bin" //constante de archivoPracticas

typedef struct{
    int nro;
    char nombrePractica[DIM_NPRACTICA];
    int eliminado;
}PRACTICA;

typedef struct nodoListaPR
{
    PRACTICA practica;
    struct nodoListaPR * sig;
}nodoListaPR;

///PRINCIPALES
void crearPractica(char nombreArchivo[]);
void modificarPractica(char nombreArchivo[]);
void bajaPractica(char nombreArchivo[]);
void altaPractica(char nombreArchivo[]);

///AUXILIARES
PRACTICA cargarPractica();
int obtenerUltimoNro(char nombreArchivo[]);
int obtenerIdPractica(char nombrePractica[DIM_NPRACTICA], char nombreArchivo[]);
nodoListaPR * crearNodoPR(PRACTICA x);
nodoListaPR * agregarEnOrdenListaPR(nodoListaPR * lista, nodoListaPR * nn);


///ARCHIVO
void cargarArchivoPracticas(char nombreArch[],PRACTICA x);
PRACTICA buscarPracticaArchivo(char nombreArchivo[],int id);
void modificarArchivoPracticas(PRACTICA nuevo,char nombreArchivo[]);
void cambiarEliminadoPractica(int valor, PRACTICA x, char nombreArchivo[]);
char * obtenerNombrePractica(int nroPractica, char nombreArchivo[]);

#endif // PRACTICAS_H_INCLUDED
