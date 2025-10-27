#include <stdio.h>
#include <stdlib.h>
#include "Prototipos.h"
// #include "Funciones.c"


int main() {
    NodoMatricula *listaMatriculas = NULL;
    NodoTrayectoria *listaTrayectorias = NULL;

    printf("Cargando datos...\n");

    LecturaMatricula(&listaMatriculas);
    InsertarNodoTrayectoria(&listaTrayectorias);

    printf("Datos cargados exitosamente.\n");

    // Mostrar menú principal
    Menu(listaMatriculas, listaTrayectorias);

    // Liberar memoria al salir
    // LiberarListaMatricula(&listaMatriculas);
    // LiberarListaTrayectoria(&listaTrayectorias);

    printf("\nMemoria liberada. Programa finalizado.\n");
    return 0;
}
