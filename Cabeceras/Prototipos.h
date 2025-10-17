#ifndef PROTOTIPOS_H
#define PROTOTIPOS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//********ACLARACION , SE DEBERA MANEJAR CON LISTA DOBLEMENTE ENTRELAZADA , RESERVANDO Y LIBERANDO MEMORIA ************/

// Estructura de datos que guarda la información

// csv MATRICULA


typedef struct {
  int secundariaEgresados; // cantidad de egresos.
  int promovidos[6];       // aprobados
  int nopromovidos[6];     // no aprobados
} Trayectoria;

typedef struct {
  int matriculas[6]; // matrícula.
  int repitentes[6]; // cantidad de repitentes.
} registroMatricula;

typedef struct NodoTrayectoria {
  Trayectoria trayectoria;
  char provincia[25]; // provincia del dato
  char sector[10];    // estatal o privado
  int id;
  struct NodoTrayectoria *sig;
  struct NodoTrayectoria *ant;
} NodoTrayectoria;

typedef struct Nodo {
  int id;             // año
  char provincia[30]; // provincias
  char sector[10];      // publico / privado
  registroMatricula reg;
  struct Nodo *ant;
  struct Nodo *sig;
} Matricula;

//--------->Objetivo de funciones<--------

//-------->Funcion menu de opciones

//******Para ambos nodos*******
//--------->Mostrar nodo(debe mostrar la lista)
//--------->ver todas las provincias
//--------->ver todas los años(a los 3)
//--------->ver todas los tipos

//--------->Buscador por provincia(ofrecer la opcion de combinar con mas filtros)
//--------->Buscador por año(ofrecer la opcion de combinar con mas filtros)
//--------->Buscador por tipo(ofrecer la opcion de combinar con mas filtros)

// ###################FUNCION LIBERAR MEMORIA###################//

// prototipo de funciones


void InsertarRegistroMatricula(Matricula **, registroMatricula, int, char[20], char[10]);
void LecturaMatricula(Matricula **);
void SubirMatricula(char *, Matricula **, registroMatricula, int, char[20], char[10]);
void ClasificacionMatricula(Matricula *, Matricula **);
void InsertarNodoTrayectoria(NodoTrayectoria **);
int Lectura(Trayectoria *, FILE *, char[25], char[10]);
void Carga(NodoTrayectoria **, Trayectoria, char[25], char[10]);
void Clasificacion(NodoTrayectoria *, NodoTrayectoria **);
void ImprimirLista(NodoTrayectoria *, Matricula *);
void Liberar(NodoTrayectoria**, NodoTrayectoria**, Matricula**, Matricula**);


void Menu(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// Esta funcion tiene que mostrar por consola una lista de opciones a, b, c, etc. Con el siguiente formato:
// ------- MENU -------
// a. Mostrar nodo
// b. Mostrar datos de todas las provincias
// c. Mostrar datos de todos los anios(2019, 2020, 2021)
// d. Mostrar datos de educacion publica y privada
// e. Buscar por provincia
// f. Buscar por anio
// g. Buscar por tipo
// s. Salir
// Tener en cuenta que al mostrar las ultimas tres opciones, hay que ofrecer si se quiere combinar el filtro que se elija con algun otro.

void MostrarNodo(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// En esta funcion se tiene que mostrar por consola en formato de tabla el conjunto de nodos con sus datos, haciendo una columna para matricula y otra columna para trayectoria. Ej:
//                      Matricula                                       Trayectoria
//                    Registro Num.1                                   Registro Num.1
//                        Año                                               Año
//                      Provincia                                        Provincia
//                        Tipo                                              Tipo
//                   Año de escolaridad                              Año de escolaridad
//                       Matricula                                     Cant. de egresos
//                       Repitentes                                       Sobre Edad

void VerTodasLasProvincias(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// Esta funcion deberia depender de la provincia , lo que se deberia lograr es recorrer todos los datos que tenga guardado el nodo por cada provincia , es decir, ej: cordoba mostraria todos los registros guardados de matricula y trayectoria de esa provincia ademas deberia mostrarse por consola como 2 tablas para discriminar cuando es matricula y cuando es trayectoria por cada año escolar.
// una validacion seria ir mostrando mismo año escolar y misma provincia y en caso de que algun nodo no tenga misma info que el otro mostrar en consola , contemplar el caso que alguno de los 2 puede no tener informacion de la provincia analizada o puede tener mas que el otro , en esos casos colocar un cartel que diga "no se encontraron registros" .
// ********EJEMPLO consola*********
//          matriculas cordoba                                              trayectorias cordoba
//.    Registro matricula numero 1                                         Registro trayectoria numero 1
//. año de escolaridad = 1 matriculas = 22 repitentes = 3        año de escolaridad = 1 secundariaEgresados = 22 sobreEdad = 5
//

void VerTodosLosAnios(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// Esta funcion deberia depender del año, lo que se deberia lograr es recorrer todos los datos que tenga guardado el nodo por cada año , es decir, ej: 2020 mostraria todos los registros guardados de matricula y trayectoria de esa año ademas deberia mostrarse por consola como 2 tablas para discriminar cuando es matricula y cuando es trayectoria por cada año escolar.
// una validacion seria ir mostrando mismo año escolar y misma año y en caso de que algun nodo no tenga misma info que el otro mostrar en consola , contemplar el caso que alguno de los 2 puede no tener informacion de la año analizada o puede tener mas que el otro , en esos casos colocar un cartel que diga "no se encontraron registros" .
// ********EJEMPLO consola*********
//                  matriculas 2020                                              trayectorias 2020
//.           Registro matricula numero 1                                         Registro trayectoria numero 1
//.         año de escolaridad = 1 matriculas = 22 repitentes = 3        año de escolaridad = 1 secundariaEgresados = 22 sobreEdad = 5
//

void VerSector(NodoTrayectoria *RegistroTrayectoria, Matricula *RegistroMatricula);
// Esta funcion deberia depender del tipo(estatal/privado) , lo que se deberia lograr es recorrer todos los datos que tenga guardado el nodo por cada tipo , es decir, ej: puclico mostraria todos los registros guardados de matricula y trayectoria de esa tipo ademas deberia mostrarse por consola como 2 tablas para discriminar cuando es matricula y cuando es trayectoria por cada año escolar.
// una validacion seria ir mostrando mismo año escolar y misma tipo y en caso de que algun nodo no tenga misma info que el otro mostrar en consola , contemplar el caso que alguno de los 2 puede no tener informacion de la tipo analizada o puede tener mas que el otro , en esos casos colocar un cartel que diga "no se encontraron registros" .
// ********EJEMPLO consola*********
//               matriculas puclico                                              trayectorias puclico
//.        Registro matricula numero 1                                         Registro trayectoria numero 1
//.         año de escolaridad = 1 matriculas = 22 repitentes = 3        año de escolaridad = 1 secundariaEgresados = 22 sobreEdad = 5





//*********************ACLARACION SOBRE LAS FUNCIONES DE BUSQUEDA ***********************
// la idea de poder combinar los filtros es que al tener 3 funciones de busqueda se deberia permitir al usuario combinar mas de una busqueda si asi lo desea, un ejemplo de uso seria , buscar por provincia , utilizar  nodos temporales(para matricula y trayectoria) para guardar el tipo de provincia que escribio el usuario , preguntar si desea filtrar por año o tipo , en caso de elegir alguna de estas opciones se deberia llamar a la funcion respectiva y pasar como parametro los nodos temporales ya que van a tener la informacion ya filtrada por provincia , filtrar de nuevo esa informacion por el caso que se solicita y mostrar o permitir combinar una vez mas , en caso de que no quiera realizar ninguna combinacion solo se muestra.
//*****************************************************************************************/

void BuscarPorProvincia(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// En esta funcion se tiene que pedir que se ingrese el nombre de la provincia cuyos datos se quiere ver, antes de empezar a mostrarlos, preguntar si se quiere añadir algun otro filtro. Por ej: Cordoba , una vez que ya filtramos los datos segun lo que se nos pide, mostramos la info por consola en un formato de tabla similar al de la funcion mostrarNodo.
// Hacemos dos nodos temporales, uno para Matricula, y otro para Trayectoria, guardando los datos filtrados en caso de que se pida combinar con otro filtro, asi podemos pasarlos como parametros al llamar a otra funcion para hacer el siguiente filtro
//                      Matricula                                       Trayectoria
//                    Registro Num.1                                   Registro Num.1
//                        Año                                               Año
//                      Provincia                                        Provincia
//                        Tipo                                              Tipo
//                   Año de escolaridad                              Año de escolaridad
//                       Matricula                                     Cant. de egresos
//                       Repitentes                                       Sobre Edad

void BuscarPorAnio(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// En esta funcion se tiene que pedir que se ingrese el año cuyos datos se quiere ver, antes de empezar a mostrarlos, preguntar si se quiere añadir algun otro filtro. Por ej: 2020 , una vez que ya filtramos los datos segun lo que se nos pide, mostramos la info por consola en un formato de tabla similar al de la funcion mostrarNodo.
// Hacemos dos nodos temporales, uno para Matricula, y otro para Trayectoria, guardando los datos filtrados en caso de que se pida combinar con otro filtro, asi podemos pasarlos como parametros al llamar a otra funcion para hacer el siguiente filtro
//                      Matricula                                       Trayectoria
//                    Registro Num.1                                   Registro Num.1
//                        Año                                               Año
//                      Provincia                                        Provincia
//                        Tipo                                              Tipo
//                   Año de escolaridad                              Año de escolaridad
//                       Matricula                                     Cant. de egresos
//                       Repitentes                                       Sobre Edad

void BuscarPorTipo(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// En esta funcion se tiene que pedir que se ingrese el tipo cuyos datos se quiere ver, antes de empezar a mostrarlos, preguntar si se quiere añadir algun otro filtro. Por ej: publico, una vez que ya filtramos los datos segun lo que se nos pide, mostramos la info por consola en un formato de tabla similar al de la funcion mostrarNodo.
// Hacemos dos nodos temporales, uno para Matricula, y otro para Trayectoria, guardando los datos filtrados en caso de que se pida combinar con otro filtro, asi podemos pasarlos como parametros al llamar a otra funcion para hacer el siguiente filtro
//                      Matricula                                       Trayectoria
//                    Registro Num.1                                   Registro Num.1
//                        Año                                               Año
//                      Provincia                                        Provincia
//                        Tipo                                              Tipo
//                   Año de escolaridad                              Año de escolaridad
//                       Matricula                                     Cant. de egresos
//                       Repitentes                                       Sobre Edad

void LiberarMemoria(Matricula *RegistroMatricula, NodoTrayectoria *RegistroTrayectoria);
// esta funcion debera recorrer al nodo con la condicion que mientras encuentre otro nodo no frena el bucle, luego por cada bucle libera memoria asegurandose de que esten todos los nodos liberados(se utiliza un puntero nodo temporal)

#endif
