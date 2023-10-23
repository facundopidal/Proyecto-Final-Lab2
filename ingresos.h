#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED

typedef struct{
    int ID;
    char fechaIngreso[10];
    char fechaRetiro[10];
    char dni[9];
    int matricula;
    int eliminado;
}INGRESO;

typedef struct nodoIngreso{
    struct nodoIngreso* ant;
    struct nodoIngreso* sig;
    INGRESO ingreso;
}nodoIngreso;



#endif // INGRESOS_H_INCLUDED
