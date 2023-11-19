#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

#include "menus.h"

///DNI
bool validarDNI(const char *dni);
char * leerDNI();
int dnicmp(char * dni1, char * dni2);

bool validarPalabras(const char *Palabras,int rango);
bool validarTelefono(const char *cadena);

bool validarFecha(const char *fecha);
bool validarFechaPosterior(const char *fechaP, const char *fechaA);
void obtenerFechaActual(int *dia, int *mes, int *anio);
char * leerFecha();
int fchcmp(char * fecha1, char * fecha2);

bool validarExistenciaPracticaActiva(int id, char nombreArchivo[]);
bool validarExistenciaPractica(int id, char nombreArchivo[]);

bool validarEdad(int edad);
int leerEnteroPositivo();
bool validarPracticaRepetida(char nombre[DIM_NPRACTICA], char nombreArchivo[]);/// TRUE si esta repetida
int generarMatricula();
char * generarPassword();
bool validarPassword(char * password);

#endif // VALIDACIONES_H_INCLUDED
