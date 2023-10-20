#ifndef PRACTICAS_H_INCLUDED
#define PRACTICAS_H_INCLUDED

typedef struct{
    int ID;
    char estudio[20];
    char Resultado[40];
}PRACTICA;

typedef struct nodoPractica{
    PRACTICA practica;
    struct nodoPractica* sig;
}nodoPractica;


#endif // PRACTICAS_H_INCLUDED
