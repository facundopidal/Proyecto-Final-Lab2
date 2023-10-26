#ifndef VALIDACIONES_H_INCLUDED
#define VALIDACIONES_H_INCLUDED

bool validarDNI(const char *dni);
bool validarPalabras(const char *Palabras);
bool validarTelefono(const char *cadena);
bool validarFecha(const char *fecha);
bool validarFechaPosterior(const char *fechaP, const char *fechaA);
void obtenerFechaActual(int *dia, int *mes, int *anio);
bool validarExistenciaPractica(int id, char nombreArchivo[]);
bool validarEdad(int edad);

#endif // VALIDACIONES_H_INCLUDED
