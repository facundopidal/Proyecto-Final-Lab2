#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

#define archivoPracticas "practicas.bin" //constante de archivoPracticas

typedef struct{
    int nro;
    char nombrePractica[DIM_NPRACTICA];
    int eliminado;
}PRACTICA;

///PRINCIPALES
void altaPractica(char nombreArchivo[]);
void modificarPractica(char nombreArchivo[]);

PRACTICA cargarPractica();
void cargarArchivoPracticas(char nombreArch[],PRACTICA x);
void mostrarPractica(PRACTICA x);
void mostrarPracticasArch(char nombreArchivo[]);
PRACTICA buscarPracticaArchivo(char nombreArchivo[],int id);
void modificarArchivoPracticas(PRACTICA nuevo,char nombreArchivo[]);
int obtenerUltimoNro(char nombreArchivo[]);

#endif // PRACTICAS_H_INCLUDED
