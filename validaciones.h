#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED
#define DIM_TELEFONO  15
#define DIM_APELLIDO 20
#define DIM_NOMBRE 20
#define DIM_DIRECCION 30
#define DIM_DNI 9
#define MAX_EDAD 125
#define DIM_NPRACTICA 30
#define DIM_FECHA 10

///DNI
bool validarDNI(const char *dni);
char * leerDNI();
bool validarPalabras(const char *Palabras,int rango);
bool validarTelefono(const char *cadena);
bool validarFecha(const char *fecha);
bool validarFechaPosterior(const char *fechaP, const char *fechaA);
void obtenerFechaActual(int *dia, int *mes, int *anio);
bool validarExistenciaPracticaActiva(int id, char nombreArchivo[]);
bool validarExistenciaPractica(int id, char nombreArchivo[]);
bool validarEdad(int edad);
int leerEnteroPositivo();
bool validarPracticaRepetida(char nombre[DIM_NPRACTICA], char nombreArchivo[]);/// TRUE si esta repetida


#endif // VALIDACIONES_H_INCLUDED
