#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

#define archivoPracticas "practicas.bin" //constante de archivoPracticas

typedef struct{
    int nro;
    char nombrePractica[30];
    int eliminado;
}PRACTICA;

PRACTICA cargarPractica();
void cargarArchivoPracticas(char nombreArch[],PRACTICA x);
void mostrarPractica(PRACTICA x);
void mostrarPracticasActivasArch(char nombreArchivo[]);

#endif // PRACTICAS_H_INCLUDED
