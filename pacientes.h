#ifndef PACIENTES_H_INCLUDED
#define PACIENTES_H_INCLUDED

#define archivoPacientes "pacientes.bin"

typedef struct{
    char dni[9];
    char apellido[20];
    char nombre[20];
    int edad;
    char direccion[30];
    char telefono[15];
    int eliminado;
}PACIENTE;

typedef struct nodoPaciente{
    struct nodoPaciente* izq;
    struct nodoPaciente* der;
    struct nodoIngreso* listaIngresos;
    PACIENTE paciente;
}nodoPaciente;



nodoPaciente* crearNodoPaciente(PACIENTE x);
PACIENTE cargarPaciente(char dni[]);
nodoPaciente * buscarPaciente(nodoPaciente * arbol, char dni[9]);
void mostrarPaciente(PACIENTE x);
void mostrarPacientesTodos(nodoPaciente* arbol);
void mostrarPacientesActivos(nodoPaciente* arbol);
void cargarArchivoPacientes(char nombreArch[],PACIENTE x);
nodoPaciente* AltaPaciente(nodoPaciente* arbol);
void CambiarEliminadoPaciente(int valor, PACIENTE x, char nombreArch[]);
PACIENTE buscarPacienteArchivo(char nombreArch[], char dni[]);
nodoPaciente * agregarPacienteArbol(nodoPaciente * arbol, PACIENTE x);
nodoPaciente * bajaPaciente(nodoPaciente * arbol);
nodoPaciente * eliminarNodoPaciente(nodoPaciente * arbol, nodoPaciente * nodo);

#endif
