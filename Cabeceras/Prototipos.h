#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

//********ACLARACION , SE DEBERA MANEJAR CON PILA ES DECIR MEMORIA DINAMICA , RESERVANDO Y LIBERANDO MEMORIA ************/

// Estructura de datos que guarda la información
typedef struct
{
    int id;
    char descripcion[50];
    // se debe agregar los campos a analizar , por ahora un id por cada dato analizado y una descripcion pero son solo ejemplos
} Educacion;

// Nodo de la lista doblemente enlazada
typedef struct nodo
{
    Educacion info;   // cada nodo guarda un registro de tipo Educacion
    struct nodo *ant; // referencia al nodo anterior
    struct nodo *sig; // referencia al nodo siguiente
} Nodo;

// Prototipos de funciones
void menu(Nodo **f, Educacion registro); // esta funcion deberia mostrar el menu de opciones que serian en un principio ,
// A ver todo los datos guardados en orden de mas viejo a mas nuevo en años
// B ver la comparativa de estos datos(alumnos egresados , repitentes , demas )
// C Buscar por año los datos que se deseen ver
// S salir del menu
void insertarNodo(Nodo **f, Educacion dato);
void mostrarLista(Nodo *f); // Se muestran los datos ordenados

void leerArchivo(Nodo **f, void (*insertar)(Nodo **f, Educacion)); // leer archivos, pasar como parametro la funcion de insertar nodo. Ejemplo de como usarla/llamarla en main "leerArchivo(&lista, insertarNodo);"
// datos de archivos por año , por un lado => Base matrícula. Educación Común. Matrícula total y por sexo, Repetidores, Alumnos con Sobreedad y Secciones, por Establecimiento, Jurisdicción, Sector de Gestión, Ámbito e Información de Oferta.
// por otro lado =>Base Trayectoria. Educación Común. Alumnos Promovidos, No Promovidos y Salidos con y sin pase por Establecimiento, Jurisdicción, Sector de Gestión, Ámbito, Información de Oferta y Sexo.

void comparacionDatos(Nodo *f); // analizar y mostrar la comparativa de estos datos de mayor a menor en cantidad, por ej. año que tuvo la mayor cantidad de egresados, y su cantidad
// buscador de datos en especifico
void menuBuscar(Nodo *f); //Despues nos ponemos de acuerdo en que opciones de datos buscar, por ej. buscar cantidad de egreso de mujeres por año

#endif
