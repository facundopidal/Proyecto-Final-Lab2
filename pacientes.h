#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED

#define archivoPacientes "pacientes.bin"

typedef struct{
    char dni[DIM_DNI];
    char apellido[DIM_APELLIDO];
    char nombre[DIM_NOMBRE];
    int edad;
    char direccion[DIM_DIRECCION];
    char telefono[DIM_TELEFONO];
    int eliminado;
}PACIENTE;

typedef struct nodoPaciente{
    struct nodoPaciente* izq;
    struct nodoPaciente* der;
    struct nodoIngreso* listaIngresos;
    PACIENTE paciente;
}nodoPaciente;


///PRINCIPALES
nodoPaciente* altaPaciente(nodoPaciente* arbol);
nodoPaciente * modificarPaciente(nodoPaciente * arbol);
nodoPaciente * bajaPaciente(nodoPaciente * arbol);

///MOSTRAR
void mostrarPaciente(PACIENTE x);
void mostrarPacientesTodos(char nombreArchivo[]);
void mostrarPacientesActivos(nodoPaciente* arbol);

///ARCHIVO
void cargarArchivoPacientes(char nombreArch[],PACIENTE x);
void CambiarEliminadoPaciente(int valor, PACIENTE x, char nombreArch[]);
void modificarArchivoPacientes(char nombreArch[], PACIENTE x);
PACIENTE buscarPacienteArchivo(char nombreArch[], char dni[]);

///AUXILIARES
nodoPaciente* crearNodoPaciente(PACIENTE x);
PACIENTE cargarPaciente(char dni[]);
nodoPaciente * buscarPaciente(nodoPaciente * arbol, char dni[]);
nodoPaciente * agregarPacienteArbol(nodoPaciente * arbol, PACIENTE x);
nodoPaciente * eliminarNodoPaciente(nodoPaciente * arbol, nodoPaciente * nodo);
nodoPaciente * encontrarMenorArbolPaciente(nodoPaciente * arbol);

#endif
