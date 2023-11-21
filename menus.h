#ifndef MENUS_H_INCLUDED
#define MENUS_H_INCLUDED

#define DIM_TELEFONO  15
#define DIM_APELLIDO 20
#define DIM_NOMBRE 20
#define DIM_DIRECCION 30
#define DIM_DNI 10
#define DIM_NPRACTICA 50
#define DIM_FECHA 10
#define DIM_RESULTADO 40
#define DIM_PASSWORD 20
#define MAX_EDAD 125
#define MAX_MATRICULA 99999

void menuDeMenus();

///---------------------------- ADMIN -----------------------------------------------------
void menuAdmin();
///ABM
void menuPrincipalesAdmin();
void menuABMPacientes();
void menuABMIngresos();
void menuABMEmpleados();
void menuABMPracticas();
///ADICIONALES
void menuAdicionalesAdmin();
void menuAdicionalesPacientes();
void menuAdicionalesIngresos();
void menuAdicionalesEmpleados();
void menuAdicionalesPracticas();
///MOSTRAR
void menuMostrarArchivosAdmin();

///---------------------------- ADMINISTRATIVO -------------------------------------
void menuAdministrativo();

void menuPacientesAdministrativos();
void menuMostrarPacientes();

void menuIngresosAdministrativos();
void menuMostrarIngresos();

void menuAjustes();

///---------------------------- PROFESIONALES -------------------------------------
void menuProfesional();

void menuPacientesProfesional();
void menuIngresosProfesional();
void menuPracticasProfesional();

#endif // MENUS_H_INCLUDED
