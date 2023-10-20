#ifndef CLIENTES_H_INCLUDED
#define CLIENTES_H_INCLUDED

typedef struct{
    char DNI[9];
    char Apellido[20];
    char Nombre[20];
    char mail[40];
    ///char FechaNac[];
}CLIENTE;

typedef struct nodoCliente{
    struct nodoCliente* izq;
    struct nodoCliente* der;
    struct nodoIngreso* ingresos;
    CLIENTE cliente;
}nodoCliente;



nodoCliente* crearNodoCliente(CLIENTE x);
CLIENTE cargarCliente();




#endif // CLIENTES_H_INCLUDED
