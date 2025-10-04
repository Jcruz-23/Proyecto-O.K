#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

//********ACLARACION , SE DEBERA MANEJAR CON PILA ES DECIR MEMORIA DINAMICA , RESERVANDO Y LIBERANDO MEMORIA ************/

// Estructura de datos que guarda la información

// csv MATRICULA

typedef struct
{
    int anio;       // años de escolaridad.
    int matriculas; // matrícula.
    int repitentes; // cantidad de repitentes.
} registroMatricula;

typedef struct Nodo
{
    int id;             // año
    char provincia[20]; // provincias
    char tipo[10];      // publico / privado
    registroMatricula reg;
    struct Nodo *ant;
    struct Nodo *sig;
} Matricula;

// csv TRAYECTORIA
typedef struct
{
    int anio;                // años de escolaridad.
    int secundariaEgresados; // cantidad de egresos.
    int sobreEdad;           // cantidad de alumnos con sobre edad.

} registroTrayecto;

// Nodo de la lista doblemente enlazada
typedef struct Nodo
{
    int id;             // año
    char provincia[20]; // provincia
    char tipo[10];      // publico / privado

    registroTrayecto reg;
    struct Nodo *ant;
    struct Nodo *sig;
} Registro;

//--------->Objetivo de funciones<--------

//Funcion menu de opciones

//******Para ambos nodos*******
//--------->Mostrar nodo(debe mostrar la lista)
//--------->ver todas las provincias
//--------->ver todas los años(a los 3)
//--------->ver todas los tipos

//--------->Buscador por provincia(ofrecer la opcion de combinar con mas filtros)
//--------->Buscador por año(ofrecer la opcion de combinar con mas filtros)
//--------->Buscador por tipo(ofrecer la opcion de combinar con mas filtros)

//###################FUNCION LIBERAR MEMORIA###################//


#endif
