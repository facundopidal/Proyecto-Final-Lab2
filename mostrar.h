#ifndef MOSTRAR_H_INCLUDED
#define MOSTRAR_H_INCLUDED

///-------------------------------------    PACIENTES    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarPaciente(PACIENTE x);
void mostrarPacientesTodos(char nombreArchivo[]);
void mostrarPacientesActivos(nodoPaciente* arbol);
void consultarPaciente(nodoPaciente * arbol);
void consultarPacienteEIngresos(nodoPaciente * arbol);
void mostrarListaP(nodoListaP * lista);
///-------------------------------------    INGRESOS    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarIngresosPorDNI(nodoPaciente* arbol);
void mostrarIngresosArbol(nodoPaciente* arbol);
void mostrarIngreso(INGRESO x);
void mostrarIngresosPaciente(nodoPaciente * paciente);
void mostrarPxi(PRACTICAxINGRESO pxi);
void mostrarIngresoYPracticas(nodoIngreso * x);
void mostrarPxIPaciente(nodoPaciente * arbol);
void mostrarIngresoArchivo(char nombreArchivo[]);
void mostrarPxIArchivo(char nombreArchivo[]);
void mostrarPracticasAsociadas(nodoIngreso * ing);
void mostrarIngresoyPracticasPorDNI(nodoPaciente* arbol);
void mostrarIngresosConDetalle(nodoPaciente * arbol);

///   CONSULTAR
void consultarIngreso(nodoPaciente * arbol);
void mostrarIngresoPorID(nodoPaciente * arbol);
nodoIngreso * mostrarIngresoPorIDArbol(nodoPaciente * arbol, int id);
void mostrarIngresosPorFecha(nodoPaciente * arbol);
void mostrarIngresosPorFechaArbol(nodoPaciente * arbol, char * fecha);
void filtrarIngresosPorFecha(nodoPaciente * arbol);
void filtrarIngresosPorFechaArbol(nodoPaciente * arbol, char * fechaD, char * fechaH);
///

///-------------------------------------    EMPLEADOS    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarEmpleado(EMPLEADO x);
void mostrarEmpleadoSinPass(EMPLEADO x);
void mostrarListaEmpleados(char nombreArchivo[]);
void consultarEmpleado(char nombreArchivo[]);
void mostrarEmpleadosArchivo(char nombreArchivo[]);

///-------------------------------------    PRACTICAS    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarPractica(PRACTICA x);
void mostrarPracticasArch(char nombreArchivo[]);
void mostrarPracticasActivas(char nombreArchivo[]);
void mostrarListaPracticas(char nombreArchivo[]);
void mostrarListaPracticasActivas(char nombreArchivo[]);
void mostrarListaPracticasInActivas(char nombreArchivo[]);
void filtrarPracticasPorCaracteres(char nombreArchivo[]);

#endif // MOSTRAR_H_INCLUDED
