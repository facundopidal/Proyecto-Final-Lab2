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

///menu de menus
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
        int opcion;
        fflush(stdin);
        scanf("%i",&opcion);

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
                    printf("Usuario No Encontrado\n Intente nuevamente\n");
            }
            system("pause");
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

void menuAdmin()
{
    int opt;
    int optPacientes;
    int optIngresos;
    int optPracticas;
    do
    {
        //system("cls");
        printf("Bienvenido al LABORATORIO \n   ---NOMBRE ACA---\n\n");
        printf("Que desea realizar?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.EMPLEADOS\n");
        printf("4.PRACTICAS\n");
        printf("5.\n");
        printf("6.\n");
        printf("\n00,para salir\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&opt);
        system("cls") ;
        switch(opt)
        {
        case 1:
            do
            {
                system("cls");
                printf("Pacientes\n");
                printf("    1.Cargar Paciente\n");
                printf("    2.Modificar Paciente\n");
                printf("    3.Dar de baja Paciente\n");
                printf("    4.Buscar y mostrar\n");
                printf("    5.Ver Pacientes Activos\n");
                printf("    6.Ver todos los pacientes\n");
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
                case 4:
                    break;
                case 5:
                    mostrarPacientesActivos(arbolPacientes);
                    system("pause");
                    break;
                case 6:
                    mostrarPacientesTodos(archivoPacientes);
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
            while(optPacientes !=0);
            break;
        case 2:
            do
            {
                system("cls");
                printf("INGRESOS\n");
                printf("    1.Cargar Ingreso\n");
                printf("    2.Modificar Ingreso\n");
                printf("    3.Dar de baja Ingreso\n");
                printf("    4.Mostrar ingresos en el arbol\n");
                printf("    5.Mostrar ingreso y practicas\n");
                printf("    6.Mostrar ingresos archivo\n");
                printf("    7.Mostrar pxi archivo\n");
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
                case 4:
                    mostrarIngresosPorDNI(arbolPacientes);
                    system("pause");
                    break;
                case 5:
                    mostrarPxIPaciente(arbolPacientes);
                    system("pause");
                    break;
                case 6:
                    mostrarIngresoArchivo(archivoIngresos);
                    system("pause");
                    break;
                case 7:
                    mostrarPxIArchivo(archivoPxI);
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
            while(optIngresos != 0);
            break;
        case 3:
            altaEmpleado(archivoEmpleados);
            system("pause");
            system("cls");
            break;
        case 4:
            do
            {
                system("cls");
                printf("PRACTICAS\n");
                mostrarPracticasArch(archivoPracticas);
                printf("    1.Cargar Practica\n");
                printf("    2.Modificar Practica\n");
                printf("    3.Dar de baja Practica\n");
                printf("    4.Dar de alta Practica\n");
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
                    printf("Ingrese una opcion Correcta\n");
                    system("pause");
                    break;
                }
            }
            while(optPracticas !=0);
            break;

        case 00:
            printf("Gracias por usar!\n");
            break;
        default:
            printf("Ingrese una opcion Correcta\n");
            system("pause");
            break;
        }
    }
    while(opt!=00);
}

void menuAdministrativo()
{
    int opt;
    int optIngresos;
    int optAjustes;
    do
    {
        system("cls");
        printf("-------Bienvenido al LABORATORIO DE ANALISIS JUAN AUX-------\n\n");
        printf("Que desea realizar?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.AJUSTES\n");
        printf("\n00,para salir\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opt);
        system("cls");
        switch(opt)
        {
        case 1:
            menuPacientesAdministrativos();
            system("pause");
            break;
        case 2:
            menuIngresosAdministrativos();
            break;
        case 3:
            break;
        default:
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
            printf("Saliendo...");
            system("pause");
            break;
        default:
            printf("Ingrese una opcion valida\n");
            system("pause");
            break;
        }

    }
    while(optPacientes != 00);
    system("pause");
}

void menuMostrarPacientes()
{
    int opcion;
    nodoListaP * lista = NULL;
    do
    {
        printf("%c CONSULTAR PACIENTES\n", 284);
        printf("    1.Mostrar Pacientes Activos\n");
        printf("    2.Mostrar Pacientes Activos Por Apellido\n");
        printf("    3.Mostrar Todos los Pacientes\n");
        printf("    4.Consultar Paciente\n");
        printf("    00.Atras\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i",&opcion);
        system("cls");
        switch(opcion)
        {
        case 1:
            printf("%c Pacientes Activos: \n", 78);
            mostrarPacientesActivos(arbolPacientes);
            system("pause");
            break;
        case 2:
            printf("%c Pacientes Activos Por Apellido: \n", 122);
            lista = listaPacientesAlfabetica(arbolPacientes);
            mostrarListaP(lista);
            system("pause");
            break;
        case 3:
            printf("%c Todos los Pacientes: \n", 78);
            mostrarPacientesTodos(archivoPacientes);
            system("pause");
            break;
        case 4:
            printf("%c Consultar Paciente: \n", 69);
            consultarPaciente(arbolPacientes);
            system("pause");
            break;
        case 00:
            printf("Saliendo...");
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
void menuIngresosAdministrativos()
{
    int optIngresos;
    do
    {
        system("cls");
        printf("INGRESOS\n");
        printf("    1.Consultar Ingreso\n");
        printf("    2.Dar de alta Ingreso\n");
        printf("    3.Dar de baja Ingreso\n");
        printf("    4.Modificar Ingreso\n");
        printf("    5.Mostrar Ingresos\n");
        printf("    00.Menu Principal\n");
        printf("--> ");

        fflush(stdin);
        scanf("%i",&optIngresos);
        system("cls");

        switch(optIngresos)
        {
        case 1:
            consultarIngreso(arbolPacientes);
            system("pause");
            break;
        case 2:
            arbolPacientes = altaIngreso(arbolPacientes, archivoPxI, archivoIngresos);
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
    while(optIngresos != 0);
}

void menuMostrarIngresos()
{
    int opcion;
    do
    {
        printf("%c CONSULTAR PACIENTES\n", 284);
        printf("    1.Mostrar Ingresos Por DNI\n");
        printf("    2.Mostrar un Ingreso Y sus Practicas\n");
        printf("    3.Mostrar \n");
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
            mostrarIngresoYPracticas();
            system("pause");
            break;
        case 3:

            system("pause");
            break;
        case 00:
            printf("Saliendo...");
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
