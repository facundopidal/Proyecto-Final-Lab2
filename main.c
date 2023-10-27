#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "ingresos.h"
#include "practicas.h"

nodoPaciente* arbolPacientes;
void menuAdmin();
int main()
{

    menuAdmin();


    return 0;
}

void menuAdmin()
{
    int opt;
    int optPacientes;
    do{
        //system("cls");
        printf("Bienvenido al LABORATORIO \n   ---NOMBRE ACA---\n\n");
        printf("Que desea realizar?\n\n");
        printf("1.PACIENTES\n");
        printf("2.INGRESOS\n");
        printf("3.\n");
        printf("4.\n");
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
                printf("    4.Dar de alta Paciente\n");
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
                    arbolPacientes=altaPaciente(arbolPacientes);
                    system("pause");
                    break;
                case 2:
                    arbolPacientes=modificarPaciente(arbolPacientes);
                    system("pause");
                    break;
                case 3:

                    break;
                case 4:

                    system("pause");
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
