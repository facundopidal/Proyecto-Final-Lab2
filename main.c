#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "ingresos.h"
#include "practicas.h"

nodoPaciente* arbolPacientes = NULL;
void menuAdmin();
int main()
{
    arbolPacientes = crearArbolPacientes(arbolPacientes, archivoPacientes,archivoIngresos, archivoPxI);
    ///mostrarPacientesActivos(arbolPacientes);

    menuAdmin();

    return 0;
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
        printf("3.\n");
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
                    arbolPacientes = altaIngreso(arbolPacientes, archivoPxI, archivoIngresos);
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
    while(opt!=0);
}
