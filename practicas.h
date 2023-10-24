#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

typedef struct{
    int nro;
    char nombrePractica[30];
    int eliminado;
}PRACTICA;


void mostrarPractica(PRACTICA x);
void mostrarPracticasActivasArch(char nombreArchivo[]);
#endif // PRACTICAS_H_INCLUDED
