#include <stdio.h>
#include <stdlib.h>
#include "Prototipos.h"
// #include "Funciones.c"

int main()
{
    NodoMatricula *listaMatriculas = NULL;
    NodoTrayectoria *listaTrayectorias = NULL;

    printf("Cargando datos...\n");

    LecturaMatricula(&listaMatriculas);
    InsertarNodoTrayectoria(&listaTrayectorias);

    printf("Datos cargados exitosamente.\n");

    // Mostrar menú principal
    Menu(listaMatriculas, listaTrayectorias);

    // Liberar memoria al salir
    LiberarM(&listaMatriculas);   // Pasa la dirección del puntero
    LiberarT(&listaTrayectorias); // Pasa la dirección del puntero

    printf("\nMemoria liberada. Programa finalizado.\n");
    return 0;
}
