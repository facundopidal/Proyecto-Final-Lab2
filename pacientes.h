#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

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
    struct nodoIngreso* ingresos;
    PACIENTE paciente;
}nodoPaciente;



nodoPaciente* crearNodoPaciente(PACIENTE x);
PACIENTE cargarPaciente();

nodoPaciente * buscarPaciente(nodoPaciente * arbol, char dni[9]);

void mostrarPaciente(PACIENTE x);
void mostrarPacientesTodos(nodoPaciente* arbol);
void mostrarPacientesActivos(nodoPaciente* arbol);

void appendPacienteArchivo(char nomArch[],PACIENTE x);





#endif // CLIENTES_H_INCLUDED
