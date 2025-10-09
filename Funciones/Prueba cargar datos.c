#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// librerias propias con los prototipos de las funciones.

/*PROPUESTA ESTRUCTURAS PARA EL ANALISIS
typedef stuct{
--> cantidad en cada nivel educativo;
    int secundaria;
    int estatal;
    int privado; --> cantidad en cada sector;
    int repitencia; --> cantidad de repitentes;
}Matricula;

typedef struct{
    int primero;
    int segundo;
    int tercero; --> deberia ser una variable para contar cada grado o año que
vayamos a analizar; int cuarto; int sobreedad; --> con este se compararan si
aumentaron o no los alumnos con sobreedad; int egresecu; int egrepim; -->
cantidad de egresados en la segundaria y cantidad de egresados de primaria;
}Trayectoria;
*/
/*typedef struct {
  int anio[6];        // años de escolaridad.
  int matriculas[6];  // matrícula.
  int repitentes[6];  // cantidad de repitentes.
  char provincia[25]; // provincia del dato
  char sector[25];    // estatal o privado
} Matricula;*/

typedef struct {
  int anio[6];                // años de escolaridad.
  int secundariaEgresados[6]; // cantidad de egresos.
  int promovidos[6];          // aprobados
  int nopromovidos[6];        // no aprobados
  char provincia[25];         // provincia del dato
  char sector[25];            // estatal o privado
} Trayectoria;

/*typedef struct Nodo {
  Matricula matricula;
  int id;
  struct Nodo *sig;
  struct Nodo *ant;
} NodoMatricula;*/

typedef struct NodoTrayectoria {
  Trayectoria trayectoria;
  int id;
  struct NodoTrayectoria *sig;
  struct NodoTrayectoria *ant;
} NodoTrayectoria;

void InsertarNodoTrayectoria(NodoTrayectoria **);
void ImprimirLista(NodoTrayectoria *);
void Liberar(NodoTrayectoria **);

int main() {
  // Menu();
  NodoTrayectoria *registro = NULL;
  InsertarNodoTrayectoria(&registro);
  ImprimirLista(registro);
  Liberar(&registro);
  return 0;
}
/*void Menu() {
  NodoMatricula *regimat = NULL;
  NodoTrayectoria *regitray = NULL;
  char opcion = ' ';
  char volver = 's';
  int bandera = 0;

  do {
    printf("Ingrese la opcion que desee ejecutar:\n");
    printf(
        "a. Datos de trayectoria obtenidos (del mas antiguo al mas actual)\n");
    printf(
        "b. Datos de matriculacion obtenidos (del mas antiguo al mas nuevo)\n");
    printf("c. Crear estadistica en porcentaje con comparativa entre anios\n");
    printf("d. Buscar datos por anio (2019, 2020 o 2021)\n");
    printf("e. Salir del menu\n");
    scanf(" %c", &opcion);

    switch (opcion) {
    case 'a':
    case 'A':
      break;
    case 'b':
    case 'B':
      break;
    case 'c':
    case 'C':
      break;
    case 'd':
    case 'D':
      break;
    case 'e':
    case 'E':
      bandera = 1;
      break;
    default:
      printf("\nNo se ha ingresado una opcion valida\n") : break;
    }
    if (opcion != 'e' && opcion != 'E') {
      printf("Desea volver al menu\?: Si(s), No(n)\n");
      scanf(" %c", &volver);
    }
  } while (volver == 's' || volver == 'S');
  if (bandera == 0) {
    Liberar(&p, &p2);
  }
  bandera = 0;
}
*/
void InsertarNodoTrayectoria(NodoTrayectoria **registro) {

  for (int i = 0; i < 3; i++) {

    if (i == 0) {
      char linea[20000];
      FILE *archivo;
      archivo = fopen("2019_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
              char *dato = strtok(linea, ",");
              if(dato != NULL){ 
                strcpy(nuevo->trayectoria.provincia, dato);
              }
              if((dato = strtok(NULL, ",")) != NULL){
                strcpy(nuevo->trayectoria.sector, dato);
              }
              for(int i = 0; i < 6; i++){
              if((dato = strtok(NULL, ",")) != NULL){
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.nopromovidos[i] = atoi(dato);
                }
              }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.secundariaEgresados[i] = atoi(dato);
                }
              }
              nuevo->id = 2019;
              for(int i = 0; i < 6; i++){
                nuevo->trayectoria.anio[i] = i+1;
              }
            }
            if(*registro == NULL){
              *registro = nuevo;
            }else{
              NodoTrayectoria *aux = *registro;
              while(aux->sig != NULL){
                aux->ant = aux;
                aux = aux->sig;
              }
              aux->sig = nuevo;
            }
          }
        } else {
          printf("Error al crear nuevo nodo\n");
        }
            fclose(archivo);
            printf("\nEl archivo fue leido con exito\n");
          } else {
            printf("\nNo se ha podido abrir el archivo\n");
          }
    if (i == 1) {
      char linea[20000];
      FILE *archivo;
      archivo = fopen("2020_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
              char *dato = strtok(linea, ",");
              if(dato != NULL){ 
                strcpy(nuevo->trayectoria.provincia, dato);
              }
              if((dato = strtok(NULL, ",")) != NULL){
                strcpy(nuevo->trayectoria.sector, dato);
              }
              for(int i = 0; i < 6; i++){
              if((dato = strtok(NULL, ",")) != NULL){
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.nopromovidos[i] = atoi(dato);
                }
              }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.secundariaEgresados[i] = atoi(dato);
                }
              }
              nuevo->id = 2020;
              for(int i = 0; i < 6; i++){
                nuevo->trayectoria.anio[i] = i+1;
              }
            }
            if(*registro == NULL){
              *registro = nuevo;
            }else{
              NodoTrayectoria *aux = *registro;
              while(aux->sig != NULL){
                aux->ant = aux;
                aux = aux->sig;
              }
              aux->sig = nuevo;
            }
          }
        } else {
          printf("Error al crear nuevo nodo\n");
        }
            fclose(archivo);
            printf("\nEl archivo fue leido con exito\n");
          } else {
            printf("\nNo se ha podido abrir el archivo\n");
          }
   if (i == 2) {
      char linea[20000];
      FILE *archivo;
      archivo = fopen("2021_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
              char *dato = strtok(linea, ",");
              if(dato != NULL){ 
                strcpy(nuevo->trayectoria.provincia, dato);
              }
              if((dato = strtok(NULL, ",")) != NULL){
                strcpy(nuevo->trayectoria.sector, dato);
              }
              for(int i = 0; i < 6; i++){
              if((dato = strtok(NULL, ",")) != NULL){
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.nopromovidos[i] = atoi(dato);
                }
              }
              for(int i = 0; i < 6; i++){
                if((dato = strtok(NULL, ",")) != NULL){
                  nuevo->trayectoria.secundariaEgresados[i] = atoi(dato);
                }
              }
              nuevo->id = 2021;
              for(int i = 0; i < 6; i++){
                nuevo->trayectoria.anio[i] = i+1;
              }
            }
            if(*registro == NULL){
              *registro = nuevo;
            }else{
              NodoTrayectoria *aux = *registro;
              while(aux->sig != NULL){
                aux->ant = aux;
                aux = aux->sig;
              }
              aux->sig = nuevo;
            }
          }
        } else {
          printf("Error al crear nuevo nodo\n");
        }
            fclose(archivo);
            printf("\nEl archivo fue leido con exito\n");
          } else {
            printf("\nNo se ha podido abrir el archivo\n");
          }
        }
      }

void ImprimirLista(NodoTrayectoria *registro){
  NodoTrayectoria *aux = registro;
  printf("%-5s | %-25s | %-25s | %-9s | %-11s | %s\n", "Anio", "Provincia", "Sector", "Promovidos", "NoPromovidos", "Egresados");
  while(aux != NULL){
    for(int i = 0; i < 6; i++){
  printf("%-5d | %-25s | %-25s | %-9d | %-11d | %d\n", aux->trayectoria.anio[i], aux->trayectoria.provincia, aux->trayectoria.sector, 
    aux->trayectoria.promovidos[i], aux->trayectoria.nopromovidos[i], aux->trayectoria.secundariaEgresados[i]);
  }
  aux = aux->sig;
  }
}

/*
void InsertarNodoMatricula(NodoMatricula **p) {

  for (int i = 0; i < 3; i++) {

    if (i == 0) {
      NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
      if (nuevo != NULL) {
        FILE *archivo;
        archivo = fopen("matricula2019.csv", "r");
        if (archivo != NULL) {
          fscanf(); // debe gusrdarse en nuevo.trayectoria;
          /*Con fscanf y fprintf debemos leer los datos del archivo para
          almacenarlos en cada mienbro de la estructura, el analisis deberia de
          ser de la primera columna y unificar las provincias ya que en el
          archivo estan repetidas porque lo hace por departamentos (si queremos
          tambbien contar los alumnos por departamento no hace falta), ya que no
          vamos a utilizar todas las columnas y las funciones fscanf y fprintf
          estan hechas para leer lineas, hay que ver como analizar solo las que
          queremos. una vez guardadas en un nodo pasaremos al siguiente donde
          analizaremos el archivo de 2020 y luego al siguiente sonde
          analizaremos el de 2021
          fclose(archivo);
        } else {
          printf("Error al leer el archivo\n");
          return;
        }
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        *p = nuevo;
      } else {
        printf("Error al crear nuevo nodo\n");
      }
    }
    if (i == 1) {
      NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
      if (nuevo != NULL) {
        FILE *archivo;
        archivo = fopen("matricula2020.csv", "r");
        if (archivo != NULL) {
          fscanf(); // debe gusrdarse en nuevo.trayectoria;
          /*Con fscanf y fprintf debemos leer los datos del archivo para
          almacenarlos en cada mienbro de la estructura, el analisis deberia
          de ser de la primera columna y unificar las provincias ya que en
          el archivo estan repetidas porque lo hace por departamentos (si
          queremos tambbien contar los alumnos por departamento no hace
          falta), ya que no vamos a utilizar todas las columnas y las
          funciones fscanf y fprintf estan hechas para leer lineas, hay que
          ver como analizar solo las que queremos. una vez guardadas en un
          nodo pasaremos al siguiente donde analizaremos el archivo de 2020
          y luego al siguiente sonde analizaremos el de 2021
          fclose(archivo);
        } else {
          printf("Error al leer el archivo\n");
          return;
        }
        nuevo->sig = NULL;
        NodoMatricula *aux = *p;
        while (aux->sig != NULL) {
          aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
      } else {
        printf("Error al crear nuevo nodo\n");
      }
    }
    if (i == 2) {
      NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
      if (nuevo != NULL) {
        FILE *archivo;
        archivo = fopen("matricula2021.csv", "r");
        if (archivo != NULL) {
          fscanf(); // debe gusrdarse en nuevo.trayectoria;
          /*Con fscanf y fprintf debemos leer los datos del archivo para
          almacenarlos en cada mienbro de la estructura, el analisis deberia
          de ser de la primera columna y unificar las provincias ya que en
          el archivo estan repetidas porque lo hace por departamentos (si
          queremos tambbien contar los alumnos por departamento no hace
          falta), ya que no vamos a utilizar todas las columnas y las
          funciones fscanf y fprintf estan hechas para leer lineas, hay que
          ver como analizar solo las que queremos. una vez guardadas en un
          nodo pasaremos al siguiente donde analizaremos el archivo de 2020
          y luego al siguiente sonde analizaremos el de 2021
          fclose(archivo);
        } else {
          printf("Error al leer el archivo\n");
          return;
        }
        nuevo->sig = NULL;
        NodoMatricula *aux = *p;
        while (aux->sig != NULL) {
          aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
      } else {
        printf("Error al crear nuevo nodo\n");
      }
    }
  }
}
*/

void Liberar(NodoTrayectoria **registro){
  while(*registro != NULL){
    NodoTrayectoria *prox = (*registro)->sig;
    free(*registro);
    *registro = prox;
  }
  printf("\nLa lista se ha eliminado con exito\n");
}
