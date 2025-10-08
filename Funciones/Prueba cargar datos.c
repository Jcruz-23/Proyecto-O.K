#include <stdio.h>
#include <stdlib.h>
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

typedef struct Nodo {
  Matricula matricula;
  struct Nodo *sig;
  struct Nodo *ant;
} NodoMatricula;

typedef struct Nodo {
  Trayectoria trayectoria;
  struct Nodo *sig;
  struct Nodo *ant;
} NodoTrayectoria;
void main() {
  Menu();
  return 0;
}
void Menu() {
  Nodo *p = NULL;
  Nodo *p2 = NULL;
  char opcion = ' ';
  char volver = 's';
  int bandera = 0;
  // A ver todo los datos guardados en orden de mas viejo a mas nuevo en años
  // B ver la comparativa de estos datos(alumnos egresados , repitentes , demas
  // ) C Buscar por año los datos que se deseen ver S salir del menu
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

void InsertarNodoTrayectoria(NodoTrayectoria **p2) {

  for (int i = 0; i < 3; i++) {

    if (i == 0) {
      NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
      if (nuevo != NULL) {
        FILE *archivo;
        archivo = fopen("trayectoria2019.csv", "r");
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
          analizaremos el de 2021*/
          fclose(archivo);
        } else {
          printf("Error al leer el archivo\n");
          return;
        }
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        *p2 = nuevo;
      }else{
        printf("Error al crear nuevo nodo\n");
      }
    }
      if (i == 1) {
          NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            FILE *archivo;
            archivo = fopen("trayectoria2020.csv", "r");
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
              y luego al siguiente sonde analizaremos el de 2021*/
              fclose(archivo);
            } else {
              printf("Error al leer el archivo\n");
              return;
            }
        nuevo->sig = NULL;
        NodoTrayectoria *aux = *p2;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
      } else {
        printf("Error al crear nuevo nodo\n");
      }
    }if (i == 2) {
          NodoTrayectoria *nuevo = (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            FILE *archivo;
            archivo = fopen("trayectoria2021.csv", "r");
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
              y luego al siguiente sonde analizaremos el de 2021*/
              fclose(archivo);
            } else {
              printf("Error al leer el archivo\n");
              return;
            }
        nuevo->sig = NULL;
        NodoTrayectoria *aux = *p;
        while(aux->sig != NULL){
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
          analizaremos el de 2021*/
          fclose(archivo);
        } else {
          printf("Error al leer el archivo\n");
          return;
        }
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        *p = nuevo;
      }else{
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
              y luego al siguiente sonde analizaremos el de 2021*/
              fclose(archivo);
            } else {
              printf("Error al leer el archivo\n");
              return;
            }
        nuevo->sig = NULL;
        NodoMatricula *aux = *p;
        while(aux->sig != NULL){
            aux = aux->sig;
        }
        nuevo->ant = aux;
        aux->sig = nuevo;
      } else {
        printf("Error al crear nuevo nodo\n");
      }
    }if (i == 2) {
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
              y luego al siguiente sonde analizaremos el de 2021*/
              fclose(archivo);
            } else {
              printf("Error al leer el archivo\n");
              return;
            }
        nuevo->sig = NULL;
        NodoMatricula *aux = *p;
        while(aux->sig != NULL){
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

