#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "empleados.h"
#include "practicas.h"
#include "mostrar.h"
#include "menus.h"

nodoPaciente* arbolPacientes = NULL;

///-------------------------------------    MENU PPAL    ----------------------------------------------------------------------------------------------------------------------------------------

void menuDeMenus()
{
    arbolPacientes = crearArbolPacientes(arbolPacientes, archivoPacientes,archivoIngresos, archivoPxI);
    int opcion;
    char * dni;
    char password[DIM_PASSWORD];
    do
    {
        system("cls");
        printf("LABORATORIO DE ANALISIS JUAN AUX\n\n");
        printf(" (1)Iniciar Sesion\n");
        printf(" (00)Salir al Escritorio\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i", &opcion);

        switch(opcion)
        {
        case 1:
            printf("Ingrese DNI: ");
            dni = leerDNI();
            printf("Ingrese Contrase%ca: ",164);
            fflush(stdin);
            gets(password);
            int perfil;
            if(dnicmp(dni,"1234567") == 0 &&  strcmp(password,"admin1234") == 0 )
                menuAdmin();
            else
            {
                perfil = buscarUsuario(archivoEmpleados,dni,password);
                if(perfil == 1)
                    menuProfesional();
                else if(perfil == 2)
                    menuAdministrativo();
                else
                {
                    printf("Usuario No Encontrado\n Intente nuevamente\n");
                    system("pause");
                }
            }
            break;
        case 00:
            printf("Cerrando Aplicacion...\n");
            system("pause");
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);

}

///-------------------------------------    ADMIN    ----------------------------------------------------------------------------------------------------------------------------------------


void menuAdmin()
{
    int opcion;
    do
    {
        system("cls");
        printf("Bienvenido al LABORATORIO \n   ---NOMBRE ACA---\n\n");
        printf("Usted ha iniciado sesion como ADMIN. A que desea acceder?\n\n");
        printf("1.FUNCIONES PRINCIPALES\n");
        printf("2.FUNCIONES ADICIONALES\n");
        printf("3.VER ARCHIVOS\n");
        printf("\n00.Salir\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            menuPrincipalesAdmin();
            break;
        case 2:
            menuAdicionalesAdmin();
            break;
        case 3:
            menuMostrarArchivosAdmin();
            break;
        case 00:
            break;
        default:
            break;
        }
    }
    while(opcion != 00);
}

void menuPrincipalesAdmin()
{
    int opt;
    do
    {
        system("cls");
        printf("Bienvenido al LABORATORIO \n   ---NOMBRE ACA---\n\n");
        printf("FUNCIONES PRINCIPALES. A cual desea acceder?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.EMPLEADOS\n");
        printf("4.PRACTICAS\n");
        printf("\n00.Salir\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&opt);
        system("cls");
        switch(opt)
        {
        case 1:
            menuABMPacientes();
            break;
        case 2:
            menuABMIngresos();
            break;
        case 3:
            menuABMEmpleados();
            break;
        case 4:
            menuABMPracticas();
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(opt!=00);
}


void menuABMPacientes()
{
    int optPacientes;
    do
    {
        system("cls");
        printf("Pacientes\n");
        printf("    1.Alta Paciente\n");
        printf("    2.Modificar Paciente\n");
        printf("    3.Baja Paciente\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optPacientes);
        system("cls");

        switch(optPacientes)
        {
        case 1:
            arbolPacientes = altaPaciente(arbolPacientes);
            system("pause");
            break;
        case 2:
            arbolPacientes = modificarPaciente(arbolPacientes);
            system("pause");
            break;
        case 3:
            arbolPacientes = bajaPaciente(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optPacientes !=00);
}

void menuABMIngresos()
{
    int optIngresos;
    do
    {
        system("cls");
        printf("INGRESOS\n");
        printf("    1.Alta Ingreso\n");
        printf("    2.Modificar Ingreso\n");
        printf("    3.Baja Ingreso\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optIngresos);
        system("cls");

        switch(optIngresos)
        {
        case 1:
            arbolPacientes = altaIngreso(arbolPacientes, archivoIngresos, archivoPxI);
            system("pause");
            break;
        case 2:
            arbolPacientes = modificarIngreso(arbolPacientes, archivoIngresos, archivoPxI);
            system("pause");
            break;
        case 3:
            arbolPacientes = bajaIngreso(arbolPacientes, archivoIngresos);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optIngresos != 00);
}

void menuABMEmpleados()
{
    int optEmpleados;
    do
    {
        system("cls");
        printf("EMPLEADOS\n");
        printf("    1.Alta Empleado\n");
        printf("    2.Modificar Empleado\n");
        printf("    3.Baja Empleado\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optEmpleados);
        system("cls");

        switch(optEmpleados)
        {
        case 1:
            altaEmpleado(archivoEmpleados);
            system("pause");
            break;
        case 2:
            modificarEmpleado(archivoEmpleados);
            system("pause");
            break;
        case 3:
            bajaEmpleado(archivoEmpleados);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(optEmpleados != 00);
}

void menuABMPracticas()
{
    int optPracticas;
    do
    {
        system("cls");
        printf("PRACTICAS\n");
        mostrarPracticasArch(archivoPracticas);
        printf("    1.Cargar Practica\n");
        printf("    2.Modificar Practica\n");
        printf("    3.Baja Practica\n");
        printf("    4.Dar de alta Practica por Nro\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optPracticas);
        system("cls");

        switch(optPracticas)
        {
        case 1:
            crearPractica(archivoPracticas);
            system("pause");
            break;
        case 2:
            modificarPractica(archivoPracticas);
            system("pause");
            break;
        case 3:
            bajaPractica(archivoPracticas);
            system("pause");
            break;
        case 4:
            altaPractica(archivoPracticas);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optPracticas != 00);
}

void menuAdicionalesAdmin()
{
    int optA;
    do
    {
        system("cls");
        printf("Bienvenido al LABORATORIO \n   ---NOMBRE ACA---\n\n");
        printf("FUNCIONES ADICIONALES. A cual desea acceder?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.EMPLEADOS\n");
        printf("4.PRACTICAS\n");
        printf("\n00.Salir\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optA);
        system("cls");
        switch(optA)
        {
        case 1:
            menuAdicionalesPacientes();
            break;
        case 2:
            menuAdicionalesIngresos();
            break;
        case 3:
            menuAdicionalesEmpleados();
            break;
        case 4:
            menuAdicionalesPracticas();
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(optA != 00);
    system("pause");
}

void menuAdicionalesPacientes()
{
    int optPacientesA;
    nodoListaP * lista = NULL;
    do
    {
        system("cls");
        printf("Pacientes (Adicionales)\n");
        printf("    1.Ver Pacientes Activos Ordenados Por DNI\n");
        printf("    2.Ver Listado General de Pacientes Ordenados por Apellido\n");
        printf("    3.Ver Todos los Pacientes\n");
        printf("    4.Consultar Paciente Por DNI\n");
        printf("    5.Consultar Paciente e Ingresos Por DNI\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optPacientesA);
        system("cls");

        switch(optPacientesA)
        {
        case 1:
            printf("Todos los pacientes activos:\n");
            mostrarPacientesActivos(arbolPacientes);
            system("pause");
            break;
        case 2:
            printf("Listado general de pacientes ordenado Por Apellido:\n");
            mostrarListaP(listaPacientesAlfabetica(arbolPacientes, lista));
            system("pause");
            break;
        case 3:
            printf("Listado general de pacientes:\n");
            mostrarPacientesTodos(archivoPacientes);
            system("pause");
            break;
        case 4:
            printf("Consulta de paciente\n");
            consultarPaciente(arbolPacientes);
            system("pause");
            break;
        case 5:
            printf("Consulta de paciente e ingresos\n");
            consultarPacienteEIngresos(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optPacientesA !=00);
}

void menuAdicionalesIngresos()
{
    int optIngresosA;
    do
    {
        system("cls");
        printf("Ingresos (Adicionales)\n");
        printf("    1.Ver Ingresos Activos con Detalle de Paciente\n");
        printf("    2.Consultar Ingreso\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optIngresosA);
        system("cls");

        switch(optIngresosA)
        {
        case 1:
            printf("Listado de Ingresos con detalle de Paciente\n");
            mostrarIngresosConDetalle(arbolPacientes);
            system("pause");
            break;
        case 2:
            printf("Consulta de ingreso\n");
            consultarIngreso(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optIngresosA != 00);
}


void menuAdicionalesEmpleados()
{
    int optEmpleadosA;
    do
    {
        system("cls");
        printf("Empleados (Adicionales)\n");
        printf("    1.Listado General Ordenado Por Apellido\n");
        printf("    2.Consultar Empleado por DNI\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optEmpleadosA);
        system("cls");

        switch(optEmpleadosA)
        {
        case 1:
            printf("Listado general de empleados ordenado por Apellido:\n");
            mostrarListaEmpleados(archivoEmpleados);
            system("pause");
            break;
        case 2:
            printf("Consultar Empleado\n");
            consultarEmpleado(archivoEmpleados);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optEmpleadosA != 00);
}

void menuAdicionalesPracticas()
{
    int optPracticasA;
    do
    {
        system("cls");
        printf("Practicas (Adicionales)\n");
        printf("    1.Listado general ordenado por Nombre\n");
        printf("    2.Filtrar Practicas que comiencen con: \n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optPracticasA);
        system("cls");

        switch(optPracticasA)
        {
        case 1:
            printf("Listado general de Practicas ordenado Por Nombre: \n");
            mostrarListaPracticas(archivoPracticas);
            system("pause");
            break;
        case 2:
            printf("Filtrar Practicas por Caracteres\n");
            filtrarPracticasPorCaracteres(archivoPracticas);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optPracticasA != 00);
}


void menuMostrarArchivosAdmin()
{
    int optMostrar;
    do
    {
        system("cls");
        printf("Cual Archivo desea visualizar?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.EMPLEADOS\n");
        printf("4.PRACTICAS\n");
        printf("5.PRACTICAS x INGRESO\n");
        printf("\n00.Salir\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optMostrar);
        system("cls");
        switch(optMostrar)
        {
        case 1:
            printf("-Archivo de Pacientes:\n");
            mostrarPacientesTodos(archivoPacientes);
            system("pause");
            break;
        case 2:
            printf("-Archivo de Ingresos:\n");
            mostrarIngresoArchivo(archivoIngresos);
            system("pause");
            break;
        case 3:
            printf("-Archivo de Empleados:\n");
            mostrarEmpleadosArchivo(archivoEmpleados);
            system("pause");
            break;
        case 4:
            printf("-Archivo de Practicas:\n");
            mostrarPracticasArch(archivoPracticas);
            system("pause");
            break;
        case 5:
            printf("-Archivo de Practicas x Ingreso:\n");
            mostrarPxIArchivo(archivoPxI);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Por favor ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(optMostrar != 00);
}

///-------------------------------------    ADMINISTRATIVO    ----------------------------------------------------------------------------------------------------------------------------------------


void menuAdministrativo()
{
    int opt;
    do
    {
        system("cls");
        printf("-------Bienvenido al LABORATORIO DE ANALISIS JUAN AUX-------\n\n");
        printf("Usted ha iniciado sesion como Administrativo. A que desea acceder?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.Ver practicas\n");
        printf("4.AJUSTES\n");
        printf("\n00. Salir\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opt);
        system("cls");
        switch(opt)
        {
        case 1:
            menuPacientesAdministrativos();
            break;
        case 2:
            menuIngresosAdministrativos();
            break;
        case 3:
            mostrarListaPracticas(archivoPracticas);
            system("pause");
            break;
        case 4:
            menuAjustes();
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion correcta\n");
            system("pause");
            break;
        }
    }
    while(opt != 00);
}
void menuPacientesAdministrativos()
{
    int optPacientes;
    do
    {
        system("cls");
        printf("%c PACIENTES\n", 284);
        printf("    1.Consultar Pacientes\n");
        printf("    2.Alta Paciente\n");
        printf("    3.Dar de baja Paciente\n");
        printf("    4.Modificar Paciente\n");
        printf("    00.Menu Principal\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&optPacientes);
        system("cls");
        switch(optPacientes)
        {
        case 1:
            menuMostrarPacientes();
            system("pause");
            break;
        case 2:
            arbolPacientes = altaPaciente(arbolPacientes);
            system("pause");
            break;
        case 3:
            arbolPacientes = bajaPaciente(arbolPacientes);
            system("pause");
            break;
        case 4:
            arbolPacientes = modificarPaciente(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }

    }
    while(optPacientes != 00);
}

void menuMostrarPacientes()
{
    int opcion;
    nodoListaP * lista = NULL;
    do
    {
        system("cls");
        printf("%c CONSULTAR PACIENTES\n", 284);
        printf("    1.Ver Pacientes Activos Ordenados Por DNI\n");
        printf("    2.Ver Listado General de Pacientes Ordenados por Apellido\n");
        printf("    3.Ver Todos los Pacientes\n");
        printf("    4.Consultar Paciente Por DNI\n");
        printf("    5.Consultar Paciente e Ingresos Por DNI\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("%c Pacientes Activos: \n", 284);
            mostrarPacientesActivos(arbolPacientes);
            system("pause");
            break;
        case 2:
            printf("%c Pacientes Activos Por Apellido: \n", 284);
            lista = listaPacientesAlfabetica(arbolPacientes, lista);
            mostrarListaP(lista);
            system("pause");
            break;
        case 3:
            printf("%c Todos los Pacientes: \n", 284);
            mostrarPacientesTodos(archivoPacientes);
            system("pause");
            break;
        case 4:
            printf("%c Consultar Paciente: \n", 284);
            consultarPaciente(arbolPacientes);
            break;
        case 5:
            printf("%c Consultar Paciente e Ingresos: \n", 284);
            consultarPacienteEIngresos(arbolPacientes);
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}
void menuIngresosAdministrativos()
{
    int optIngresos;
    do
    {
        system("cls");
        printf("INGRESOS\n");
        printf("    1.Consultar Ingreso Por ID O Fecha\n");
        printf("    2.Dar de alta Ingreso\n");
        printf("    3.Dar de baja Ingreso\n");
        printf("    4.Modificar Ingreso\n");
        printf("    5.Mostrar Ingresos Por DNI\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optIngresos);
        system("cls");

        switch(optIngresos)
        {
        case 1:
            consultarIngreso(arbolPacientes);
            break;
        case 2:
            arbolPacientes = altaIngreso(arbolPacientes,archivoIngresos,archivoPxI);
            system("pause");
            break;
        case 3:
            arbolPacientes = bajaIngreso(arbolPacientes, archivoIngresos);
            system("pause");
            break;
        case 4:
            arbolPacientes = modificarIngreso(arbolPacientes, archivoIngresos, archivoPxI);
            system("pause");
            break;
        case 5:
            menuMostrarIngresos();
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(optIngresos != 0);
}

void menuMostrarIngresos()
{
    int opcion;
    do
    {
        system("cls");
        printf("%c MOSTRAR INGRESOS\n", 284);
        printf("    1.Mostrar Ingresos Por DNI\n");
        printf("    2.Mostrar un Ingreso Y sus Practicas\n");
        printf("    3.Mostrar Todos los Ingresos Y sus Practicas\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            mostrarIngresosPorDNI(arbolPacientes);
            system("pause");
            break;
        case 2:
            mostrarIngresoyPracticasPorDNI(arbolPacientes);
            system("pause");
            break;
        case 3:
            mostrarPxIPaciente(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}
void menuAjustes()
{
    int opcion;
    do
    {
        system("cls");
        printf("MENU AJUSTES\n");
        printf("    1.Cambiar nombre y apellido\n");
        printf("    2.Cambiar contrase%ca\n",164);
        printf("    3.Ver Listado de Empleados\n");
        printf("    00.Salir del menu\n");
        printf("--> ");
        scanf("%i", &opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            cambiarNombreYApellido(archivoEmpleados);
            system("pause");
            break;
        case 2:
            cambiarPassword(archivoEmpleados);
            system("pause");
            break;
        case 3:
            mostrarListaEmpleados(archivoEmpleados);
            system("pause");
        case 00:
            break;
        default :
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}

///-------------------------------------    PROFESIONAL    ----------------------------------------------------------------------------------------------------------------------------------------


void menuProfesional()
{
    int opt;
    do
    {
        system("cls");
        printf("-------Bienvenido al LABORATORIO DE ANALISIS JUAN AUX-------\n\n");
        printf("Usted ha iniciado sesion como Profesional. A que desea acceder?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.PRACTICAS\n");
        printf("4.AJUSTES\n");
        printf("\n00. Salir\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opt);
        system("cls");
        switch(opt)
        {
        case 1:
            menuPacientesProfesional();
            break;
        case 2:
            menuIngresosProfesional();
            break;
        case 3:
            menuPracticasProfesional();
            break;
        case 4:
            menuAjustes();
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion correcta\n");
            system("pause");
            break;
        }
    }
    while(opt != 00);
}


void menuPacientesProfesional()
{
    int opcion;
    nodoListaP * lista = NULL;
    do
    {
        system("cls");
        printf("%c PACIENTES\n", 284);
        printf("    1.Ver Pacientes Activos Ordenados Por DNI\n");
        printf("    2.Ver Listado General de Pacientes Ordenados por Apellido\n");
        printf("    3.Consultar Paciente Por DNI\n");
        printf("    4.Consultar Paciente e Ingresos Por DNI\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("%c Pacientes Activos: \n", 284);
            mostrarPacientesActivos(arbolPacientes);
            system("pause");
            break;
        case 2:
            printf("%c Pacientes Activos Por Apellido: \n", 284);
            lista = listaPacientesAlfabetica(arbolPacientes, lista);
            mostrarListaP(lista);
            system("pause");
            break;
        case 3:
            printf("%c Consultar Paciente: \n", 284);
            consultarPaciente(arbolPacientes);
            system("pause");
            break;
        case 4:
            printf("%c Consultar Paciente e Ingresos: \n", 284);
            consultarPacienteEIngresos(arbolPacientes);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}


void menuIngresosProfesional()
{
    int opcion;
    do
    {
        system("cls");
        printf("%c INGRESOS\n", 284);
        printf("    1.Modificar Ingreso o Practicas Asociadas\n");
        printf("    2.Dar de Baja Ingreso\n");
        printf("    3.Cargar o Editar Resultado\n");
        printf("    4.Mostrar Ingresos Por DNI\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            arbolPacientes = modificarIngreso(arbolPacientes, archivoIngresos, archivoPxI);
            system("pause");
            break;
        case 2:
            arbolPacientes = bajaIngreso(arbolPacientes, archivoIngresos);
            system("pause");
            break;
        case 3:
            arbolPacientes = cargarResultado(arbolPacientes, archivoPxI);
            system("pause");
            break;
        case 4:
            menuMostrarIngresos();
            system("pause");            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}

void menuPracticasProfesional()
{
    int opcion;
    do
    {
        system("cls");
        printf("%c PRACTICAS\n", 284);
        printf("    1.Cargar Practica\n");
        printf("    2.Modificar Practica\n");
        printf("    3.Dar de Baja Practica\n");
        printf("    4.Dar de Alta por ID Practica\n");
        printf("    5.Ver Practicas Activas\n");
        printf("    6.Ver Todas las Practicas\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            crearPractica(archivoPracticas);
            system("pause");            break;
        case 2:
            modificarPractica(archivoPracticas);
            system("pause");
            break;
        case 3:
            bajaPractica(archivoPracticas);
            system("pause");
            break;
        case 4:
            altaPractica(archivoPracticas);
            system("pause");
            break;
        case 5:
            mostrarListaPracticasActivas(archivoPracticas);
            system("pause");
        case 6:
            mostrarListaPracticas(archivoPracticas);
            system("pause");
            break;
        case 00:
            break;
        default:
            printf("Por favor Ingrese una opcion valida\n");
            system("pause");
            break;
        }
    }
    while(opcion != 00);
}
