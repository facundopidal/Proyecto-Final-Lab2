#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "validaciones.h"
#include "pacientes.h"
#include "ingresos.h"
#include "practicas.h"

///-------------------------------------    CARGAR ARBOL   -----------------------------------------------------------------------------------------------------------------------------


nodoIngreso * crearListaIngresos(nodoPaciente * paciente, char archIngresos[], char archPxI[])
{
    FILE * buffer = fopen(archIngresos, "rb");
    INGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(INGRESO), 1, buffer) == 1)
        {
            if((aux.eliminado == 0) && (dnicmp(aux.dni, paciente->paciente.dni) == 0))
            {
                nodoIngreso * nodo = crearNodoIngreso(aux);
                nodo->listaPxI = crearListaPxI(nodo, archPxI);
                paciente->listaIngresos = agregarPpioIngreso(paciente->listaIngresos, nodo);
            }
        }

        fclose(buffer);
    }
    return paciente->listaIngresos;
}

///Creamos la lista pxi
nodoPxI * crearListaPxI(nodoIngreso * ing, char archPxI[])
{
    FILE * buffer = fopen(archPxI, "rb");
    PRACTICAxINGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICAxINGRESO), 1, buffer) == 1)
        {
            if(aux.idIngreso == ing->ingreso.ID)
                ing->listaPxI = agregarPpioPxI(ing->listaPxI, crearNodoPxI(aux));
        }
        fclose(buffer);
    }
    return ing->listaPxI;
}

///-------------------------------------    PRINCIPALES   -----------------------------------------------------------------------------------------------------------------------------


nodoPaciente * altaIngreso(nodoPaciente * arbol, char nombreArchivoPxI[], char nombreArchivoIngresos[])
{
    char dni[DIM_DNI];
    printf("Ingrese dni del paciente: ");
    strcpy(dni,leerDNI());

    nodoPaciente * paciente = buscarPaciente(arbol, dni);

    if(!paciente) //Si el dni no es valido se vuelve al menu
    {
        printf("No se encontro el paciente, debe darlo de alta en el menu principal\n");
        printf("Seleccione la opcion de CARGAR PACIENTE ");
        return arbol;
    }
    printf("Se encontro el paciente %s %s, cargue el ingreso\n", paciente->paciente.nombre, paciente->paciente.apellido); //Cargamos el ingreso

    paciente->listaIngresos = altaListaIngreso(paciente->listaIngresos, dni,nombreArchivoIngresos); //carga el ingreso completo solo en la lista

    paciente->listaIngresos->listaPxI = altaListaPxI(paciente->listaIngresos->listaPxI, paciente->listaIngresos->ingreso.ID); //carga pxi(puede ser mas de una) solo en la lista

    cargarArchivoPxI(nombreArchivoPxI, paciente->listaIngresos->listaPxI); //Se pasa la lista para ser recorrida en la funcion
    cargarArchivoIngresos(nombreArchivoIngresos, paciente->listaIngresos->ingreso); //Guardamos los datos en el archivo
    printf("Ingreso cargado satisfactoriamente\n");
    mostrarIngresoYPracticas(paciente->listaIngresos);
    return arbol;
}


nodoPaciente * bajaIngreso(nodoPaciente * arbol, char nombreArchivo[])
{
    char dni[DIM_DNI];
    printf("Ingrese dni del paciente: ");
    strcpy(dni,leerDNI());

    nodoPaciente * paciente = buscarPaciente(arbol, dni);

    if(!paciente) //Si el dni no es valido se vuelve al menu
    {
        printf("No se encontro el paciente, debe darlo de alta en el menu principal");
        printf("Seleccione la opcion de CARGAR PACIENTE ");
        return arbol;
    }
    printf("Se encontro el paciente, estos son sus ingresos: \n");
    mostrarIngresosPaciente(paciente);
    int idBaja;
    printf("Ingrese el Id de ingreso a dar de baja: ");
    fflush(stdin);
    while(scanf("%i",&idBaja) != 1)
    {
        printf("Id NO VALIDO\n Ingrese Nuevamente: ");
        fflush(stdin);
    }

    nodoIngreso * ingresoBaja = buscarIngreso(paciente->listaIngresos, idBaja);
    if(ingresoBaja)
    {
        cambiarEliminadoIngreso(1, ingresoBaja->ingreso, nombreArchivo);
        paciente->listaIngresos = eliminarNodoIngreso(paciente->listaIngresos, ingresoBaja);
        ingresoBaja->ingreso.eliminado = 1;
        printf("Ingreso Dado de Baja Exitosamente\n");
        mostrarIngresoYPracticas(ingresoBaja);
    }
    else
        printf("El Id no se encontro en los ingresos, volviendo al menu \n");

    return arbol;
}

nodoPaciente * modificarIngreso(nodoPaciente * arbol, char nombreArch[])
{
    printf("Ingrese dni del paciente a modificar: ");
    char * dni = leerDNI();
    nodoPaciente * pacienteAModificar = buscarPaciente(arbol, dni);
    if(pacienteAModificar)
    {
        printf("Se encontro el paciente, estos son sus ingresos: \n");
        mostrarIngresosPaciente(pacienteAModificar);
        printf("\n");
        if(!pacienteAModificar->listaIngresos)
            return arbol;

        int idAModificar;
        printf("Ingrese el Id de ingreso a modificar: ");
        fflush(stdin);
        while(scanf("%i",&idAModificar) != 1)
        {
            printf("Id NO VALIDO\n Ingrese Nuevamente: ");
            fflush(stdin);
        }
        nodoIngreso * ingresoAMod = buscarIngreso(pacienteAModificar->listaIngresos, idAModificar);
        if(ingresoAMod)
        {
            int opcion;

            do
            {
                system("cls");
                mostrarIngreso(ingresoAMod->ingreso);
                printf("-------------------------------------\n");
                printf("Ingrese:\n(1) Editar Matricula\n(2) Editar Fecha de retiro\n(00) Salir\n");
                printf("--> ");
                scanf("%i", &opcion);
                switch(opcion)
                {
                case 1:
                    printf("Ingrese la nueva matricula del medico: ");
                    fflush(stdin);
                    while(scanf("%i",&ingresoAMod->ingreso.matricula) != 1 || ingresoAMod->ingreso.matricula > MAX_MATRICULA || ingresoAMod->ingreso.matricula < 10000)
                    {
                        printf("Matricula NO VALIDA\n Ingrese una matricula valida: ");
                        fflush(stdin);
                    }
                    break;
                case 2:
                    printf("Ingrese fecha de retiro con formato dd/mm/aaaa: ");
                    fflush(stdin);
                    fgets(ingresoAMod->ingreso.fechaRetiro, DIM_FECHA + 1, stdin);
                    ingresoAMod->ingreso.fechaRetiro[strcspn(ingresoAMod->ingreso.fechaRetiro, "\n")] = '\0';
                    while(getchar() != '\n');
                    while(!validarFechaPosterior(ingresoAMod->ingreso.fechaRetiro, ingresoAMod->ingreso.fechaIngreso)) //Valida que la sea sea posterior, no incluye mismo dia
                    {
                        printf("Fecha NO VALIDA \n-Ingrese una fecha valida con formato dd/mm/aaaa \n-Que sea posterior a hoy: ");
                        fflush(stdin);
                        fgets(ingresoAMod->ingreso.fechaRetiro, DIM_FECHA + 1, stdin);
                        ingresoAMod->ingreso.fechaRetiro[strcspn(ingresoAMod->ingreso.fechaRetiro, "\n")] = '\0';
                        while(getchar() != '\n');
                    }
                    break;
                case 00:
                    modificarArchivoIngresos(nombreArch, ingresoAMod->ingreso);
                    printf("Saliendo...\n");
                    break;
                default:
                    printf("Ingrese una opcion valida\n");
                }
            }
            while(opcion != 0);
            printf("Ingreso Modificado Exitosamente\n");
        }
        else
            printf("El Id no se encontro en los ingresos, volviendo al menu \n");
    }
    else
        printf("\nEl paciente no se encuentra en la base de datos o esta dado de baja\n\n");

    return arbol;
}

nodoPaciente * modificarPxI(nodoPaciente * arbol, char nombreArch[])
{
    printf("Ingrese dni del paciente a modificar: ");
    char * dni = leerDNI();
    nodoPaciente * pacienteAModificar = buscarPaciente(arbol, dni);

    if(pacienteAModificar)
    {
        printf("Se encontro el paciente, estos son sus ingresos: \n");
        mostrarIngresosPaciente(pacienteAModificar);
        printf("\n");
        if(!pacienteAModificar->listaIngresos)
            return arbol;

        int idAModificar;
        printf("Ingrese el Id de ingreso a modificar: ");
        fflush(stdin);
        while(scanf("%i",&idAModificar) != 1)
        {
            printf("Id NO VALIDO\n Ingrese Nuevamente: ");
            fflush(stdin);
        }
        nodoIngreso * ingresoAMod = buscarIngreso(pacienteAModificar->listaIngresos, idAModificar);
        if(ingresoAMod)
        {
            printf("Se encontro el ingreso, estas son sus praticas: \n");
            mostrarPracticasAsociadas(ingresoAMod);///No funciona correctamente
            int nroPract;
            printf("Ingrese el Nro de Practica a Modificar: ");
            fflush(stdin);
            while(scanf("%i", &nroPract) != 1)
            {
                printf("Nro de Practica NO VALIDO\n Ingrese nuevamente el nro de practica: ");
                fflush(stdin);
            }
            nodoPxI * pxiAMod = buscarPxI(ingresoAMod->listaPxI, nroPract);
            if(pxiAMod)
            {
                ///switch
            }
            else
                printf("La Practica que se quiere modificar no existe\n");
        }
        else
            printf("El Id no se encontro en los ingresos, volviendo al menu \n");
    }
    else
        printf("\nEl paciente no se encuentra en la base de datos o esta dado de baja\n\n");

    return arbol;
}

///-------------------------------------    MOSTRAR    ----------------------------------------------------------------------------------------------------------------------------------------

void mostrarIngresosArbol(nodoPaciente* arbol)
{
    mostrarIngresosArbol(arbol->izq);

    mostrarIngresosPaciente(arbol);

    mostrarIngresosArbol(arbol->der);

}

void mostrarIngresosPorDNI(nodoPaciente* arbol)
{
    char dni[DIM_DNI];
    printf("Ingrese el dni del paciente: ");
    strcpy(dni,leerDNI());
    nodoPaciente* paciente= buscarPaciente(arbol,dni);
    if(paciente)
        mostrarIngresosPaciente(paciente);
    else
        printf("ERROR-- No se encontro el paciente\n");
}


void mostrarIngreso(INGRESO x)
{
    printf("-------------------------------------\n");
    if(x.eliminado==1)
        printf("ID de Ingreso: %i |DADO DE BAJA|\n",x.ID);
    else
        printf("ID de Ingreso: %i\n",x.ID);
    printf("Fecha de Ingreso: %s\n",x.fechaIngreso);
    printf("Fecha de Retiro: %s\n",x.fechaRetiro);
    printf("Matricula: %i\n",x.matricula);
}

void mostrarIngresosPaciente(nodoPaciente * paciente)
{
    nodoIngreso * aux = paciente->listaIngresos;
    if(!aux)
        printf("\nEl paciente %s %s no tiene ingresos asignados\n\n", paciente->paciente.nombre, paciente->paciente.apellido);
    while(aux)
    {
        mostrarIngreso(aux->ingreso);
        aux = aux->sig;
    }
}

void mostrarPxi(PRACTICAxINGRESO pxi)
{
    printf("%c  Nro de practica: %i\n", 220,pxi.nroPractica);
    puts(obtenerNombrePractica(pxi.nroPractica, archivoPxI));
    printf("    Resultado: %s\n",pxi.resultado);
    printf("  ------------------------\n");
}

void mostrarIngresoYPracticas(nodoIngreso * x)
{
    nodoIngreso * aux = x;
    mostrarIngreso(aux->ingreso);
    nodoPxI * seg = aux->listaPxI;
    printf("Practicas asociadas:\n");
    printf("  ------------------------\n");
    while(seg)
    {
        mostrarPxi(seg->PxI);
        seg = seg->sig;
    }
}

void mostrarPxIPaciente(nodoPaciente * arbol)
{
    char dni[DIM_DNI];
    printf("Ingrese dni del paciente: ");
    strcpy(dni, leerDNI());
    nodoPaciente * aux = buscarPaciente(arbol, dni);
    nodoIngreso * seg = aux->listaIngresos;
    if(aux)
    {
        if(seg)
            printf("Todos los ingresos del paciente %s %s: \n", aux->paciente.nombre, aux->paciente.apellido);
        else
            printf("\nEl paciente %s %s no tiene ingresos asignados\n\n", aux->paciente.nombre, aux->paciente.apellido);
        while(seg)
        {
            mostrarIngresoYPracticas(seg);
            seg = seg->sig;
        }
    }
    else
        printf("El paciente no se encontro\n");
}

void mostrarIngresoArchivo(char nombreArchivo[])
{
    FILE* buffer = fopen(nombreArchivo, "rb");
    INGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(INGRESO), 1, buffer) == 1)
        {
            printf("DNI DE PACIENTE: %s\n", aux.dni);
            mostrarIngreso(aux);
        }
        fclose(buffer);
    }
}

void mostrarPxIArchivo(char nombreArchivo[])
{
    FILE* buffer = fopen(nombreArchivo, "rb");
    PRACTICAxINGRESO aux;
    if(buffer)
    {
        while(fread(&aux, sizeof(PRACTICAxINGRESO), 1, buffer) == 1)
        {
            printf("Id de ingreso: %i\n", aux.idIngreso);
            mostrarPxi(aux);
        }

        fclose(buffer);
    }
}

void mostrarPracticasAsociadas(nodoIngreso * ing)
{
    nodoPxI * aux = ing->listaPxI;
    int i = 1;
    while(aux)
    {
        printf("Practica %i: \n", i);
        mostrarPxi(aux->PxI);
        aux = aux->sig;
        i++;
    }
}

///-------------------------------------    ARCHIVO    --------------------------------------------------------------------------------------------------------------------------------------


void cambiarEliminadoIngreso(int valor, INGRESO x, char nombreArch[])
{
    FILE * buffer = fopen(nombreArch, "r+b");
    INGRESO aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 && fread(&aux, sizeof(INGRESO), 1, buffer) > 0)
        {
            if(aux.ID == x.ID)
            {
                x.eliminado = valor;
                fseek(buffer, (-1) * sizeof(INGRESO),1);
                fwrite(&x, sizeof(INGRESO), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}


void cargarArchivoIngresos(char nombreArch[],INGRESO x)
{
    FILE *buffer = fopen(nombreArch, "ab");
    if(buffer)
    {
        fwrite(&x, sizeof(INGRESO), 1, buffer);
        fclose(buffer);
    }
}

void cargarArchivoPxI(char nombreArch[],nodoPxI * lista)
{
    FILE *buffer = fopen(nombreArch, "ab");
    PRACTICAxINGRESO aux;
    nodoPxI * seg = lista;
    if(buffer)
    {
        while(seg)
        {
            aux = seg->PxI;
            fwrite(&aux, sizeof(PRACTICAxINGRESO), 1, buffer);
            seg = seg->sig;
        }
        fclose(buffer);
    }
}


void modificarArchivoIngresos(char nombreArch[], INGRESO x)
{
    FILE * buffer = fopen(nombreArch, "r+b");
    INGRESO aux;
    int flag = 0;
    if(buffer)
    {
        while(flag == 0 &&fread(&aux, sizeof(INGRESO), 1, buffer) == 1)
        {
            if(aux.ID == x.ID)
            {
                fseek(buffer, (-1) * sizeof(INGRESO), 1);
                fwrite(&x, sizeof(INGRESO), 1, buffer);
                flag = 1;
            }
        }
        fclose(buffer);
    }
}

///-------------------------------------    AUXILIARES    --------------------------------------------------------------------------------------------------------------------------------


INGRESO cargarIngreso(int id, char dni[])
{
    INGRESO x;

    x.ID = id;

    x.eliminado = 0;

    ///Matricula
    x.matricula = generarMatricula();
    printf("La matricula se completo con %i\n", x.matricula);

    ///Fecha de ingreso

    int dia,mes,anio;
    obtenerFechaActual(&dia, &mes, &anio);
    fflush(stdin);
    sprintf(x.fechaIngreso, "%i/%i/%i", dia, mes, anio);
    printf("La fecha de ingreso se completo con la del dia de hoy: %s\n", x.fechaIngreso);

    ///Fecha de retiro
    printf("Ingrese fecha de retiro con formato dd/mm/aaaa: ");
    fflush(stdin);
    fgets(x.fechaRetiro, DIM_FECHA + 1, stdin);
    x.fechaRetiro[strcspn(x.fechaRetiro, "\n")] = '\0';
    while(getchar() != '\n');
    while(!validarFechaPosterior(x.fechaRetiro, x.fechaIngreso)) //Valida que la sea sea posterior, no incluye mismo dia
    {
        printf("Fecha NO VALIDA \n-Ingrese una fecha valida con formato dd/mm/aaaa \n-Que sea posterior a hoy: ");
        fflush(stdin);
        fgets(x.fechaRetiro, DIM_FECHA + 1, stdin);
        x.fechaRetiro[strcspn(x.fechaRetiro, "\n")] = '\0';
        while(getchar() != '\n');
    }
    printf("\n");

    fflush(stdin);
    strcpy(x.dni, dni);

    return x;
}

nodoIngreso * crearNodoIngreso(INGRESO ing)
{
    nodoIngreso * nodo = (nodoIngreso*) malloc(sizeof(nodoIngreso));
    nodo->ant = NULL;
    nodo->sig = NULL;
    nodo->ingreso = ing;
    nodo->listaPxI = NULL;
    return nodo;
}

nodoIngreso * agregarPpioIngreso(nodoIngreso * lista, nodoIngreso * nodo)
{
    if(!lista)
        return nodo;
    else
    {
        nodo->sig = lista;
        lista->ant = nodo;
        return nodo;
    }
}


nodoIngreso * altaListaIngreso(nodoIngreso * lista, char dni[],char nombreArchivo[])
{
    int nuevoId = obternerIdIngresoArchivo(nombreArchivo);
    INGRESO aux = cargarIngreso(nuevoId, dni);
    lista = agregarPpioIngreso(lista, crearNodoIngreso(aux)); //añadimos ingreso a la lista
    return lista;
}

int obternerIdIngresoArchivo(char nombreArchivo[])
{
    FILE* buffer=fopen(nombreArchivo,"rb");
    INGRESO aux;
    int id = 1;
    if(buffer)
    {
        fseek(buffer,(-1)*sizeof(INGRESO),SEEK_END);
        if(fread(&aux,sizeof(INGRESO),1,buffer)==1)
            id=aux.ID+1;
        fclose(buffer);
    }
    return id;
}

nodoIngreso * buscarIngreso(nodoIngreso * lista, int id)
{
    nodoIngreso * aux = lista;
    while(aux)
    {
        if(aux->ingreso.ID == id)
            return aux;

        aux = aux->sig;
    }
    return NULL;
}

nodoIngreso * eliminarNodoIngreso(nodoIngreso * lista, nodoIngreso * nodo)
{
    nodoIngreso * aux = lista;
    if(!lista)
        return NULL;
    if(lista->ingreso.ID == nodo->ingreso.ID)
    {
        lista = lista->sig;
        if (lista)
        {
            lista->ant = NULL;
            lista->listaPxI = liberarListaPxI(lista->listaPxI);
        }
        free(aux);
        return lista;
    }

    while(aux)
    {
        if(aux->ingreso.ID == nodo->ingreso.ID)
        {
            aux->ant->sig = aux->sig;
            aux->sig->ant = aux->ant;
            aux->listaPxI = liberarListaPxI(aux->listaPxI);
            free(aux);
        }
        aux = aux->sig;
    }
    return lista;
}

nodoPxI* liberarListaPxI(nodoPxI* lista)
{
    nodoPxI * proximo;
    nodoPxI * seg = lista;
    while(seg != NULL)
    {
        proximo = seg->sig;  //tomo la dir del siguiente.
        free(seg);                 //borro el actual.
        seg = proximo;             //actualizo el actual con la dir del
        //siguiente, para avanzar.
    }
    return seg;
}


PRACTICAxINGRESO cargarPxI(int idIngreso)
{
    PRACTICAxINGRESO pxi;
    pxi.idIngreso = idIngreso; //cargamos id de ingreso

    printf("Ingrese el id de practica que desea: ");
    fflush(stdin);
    scanf("%i", &pxi.nroPractica);
    while(!validarExistenciaPracticaActiva(pxi.nroPractica, archivoPracticas)) //buscamos la practica en el archivo
    {
        mostrarPracticasArch(archivoPracticas);
        printf("ID NO VALIDO\n Por favor ingrese uno de los mostrados en pantalla: ");
        fflush(stdin);
        scanf("%i", &pxi.nroPractica);
    }
    strcpy(pxi.resultado, "Pendiente"); //Ponemos resultado en pendiente por defecto para luego completar
    return pxi;
}

nodoPxI * altaListaPxI(nodoPxI * lista, int idIngreso)
{
    int seguir = 1;
    mostrarPracticasArch(archivoPracticas);
    while(seguir == 1)
    {
        PRACTICAxINGRESO aux = cargarPxI(idIngreso);
        lista = agregarPpioPxI(lista, crearNodoPxI(aux));
        printf("1. Ingresar otra practica\n");
        printf("00. Confirmar practicas\n");
        printf("--> ");
        fflush(stdin);
        scanf("%i", &seguir);
        while(seguir != 0 && seguir != 1)
        {
            printf("Ingrese una opcion valida\n");
            printf("--> ");
            fflush(stdin);
            scanf("%i", &seguir);
        }
    }
    return lista;
}

nodoPxI * crearNodoPxI(PRACTICAxINGRESO pxi)
{
    nodoPxI *nodo = (nodoPxI *) malloc(sizeof(nodoPxI));
    nodo->sig = NULL;
    nodo->PxI = pxi;
    return nodo;
}

nodoPxI * agregarPpioPxI(nodoPxI * lista, nodoPxI * nodo)
{
    if(lista)
        nodo->sig = lista;
    return nodo;
}



