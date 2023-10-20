#ifndef INGRESOS_H_INCLUDED
#define INGRESOS_H_INCLUDED

typedef struct{
    int ID;
    char DNI[9];
    ///fecha
}INGRESO;

typedef struct nodoIngreso{
    struct nodoIngreso* ant;
    struct nodoIngreso* sig;
    struct nodoPractica* practicas;
    INGRESO ingreso;
}nodoIngreso;



#endif // INGRESOS_H_INCLUDED
