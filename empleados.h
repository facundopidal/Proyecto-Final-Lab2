#ifndef EMPLEADOS_H_INCLUDED
#define EMPLEADOS_H_INCLUDED
#define T_ADMIN 0
#define T_PROFESIONAL 1
#define T_ADMINISTRATIVO 2
#define archivoEmpleados "empleados.bin"

typedef struct
{
    char dni[DIM_DNI];
    char nombre[DIM_NOMBRE];
    char apellido[DIM_APELLIDO];
    int tipoPerfil;//0 ADMIN 1 PROFESIONAL 2 ADMINISTRATIVO
    char password[DIM_PASSWORD];
}EMPLEADO;

typedef struct nodoListaE
{
    EMPLEADO empleado;
    struct nodoListaE * sig;
}nodoListaE;

void altaEmpleado(char nombreArch[]);
void modificarEmpleado(char nombreArch[]);
void bajaEmpleado(char nombreArch[]);
EMPLEADO buscarEmpleado(char dni[], char nombreArch[]);
EMPLEADO cargarEmpleado(char dni[]);
void cargarArchivoEmpleados(EMPLEADO x, char nombreArch[]);
char * tipoEmpleado(int tipo);
void eliminarUsuario(char dni[], char nombreArchivo[]);
int buscarUsuario(char nombreArchivo[],char dni[DIM_DNI],char password[DIM_PASSWORD]);
void cambiarPassword (char nombreArchivo[]);
void cambiarNombreYApellido(char nombreArchivo[]);

void modificarArchivoEmpleado(EMPLEADO x, char nombreArchivo[]);

nodoListaE * crearNodoE(EMPLEADO x);
nodoListaE * agregarEnOrdenListaE(nodoListaE * lista, nodoListaE * nn);
#endif // EMPLEADOS_H_INCLUDED
