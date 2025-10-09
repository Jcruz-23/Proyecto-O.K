#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int secundariaEgresados; // cantidad de egresos.
  int promovidos[6];       // aprobados
  int nopromovidos[6];     // no aprobados
  char provincia[25];      // provincia del dato
  char sector[15];         // estatal o privado
} Trayectoria;

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
  NodoTrayectoria *registro = NULL;
  InsertarNodoTrayectoria(&registro);
  ImprimirLista(registro);
  Liberar(&registro);
  return 0;
}

void InsertarNodoTrayectoria(NodoTrayectoria **registro) {

  for (int i = 0; i < 3; i++) {

    if (i == 0) {
      char basura[20000];
      char linea[20000];
      FILE *archivo;
      archivo = fopen("2019_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        fgets(basura, 20000, archivo);
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
            char *dato = strtok(linea, ",");
            if (dato != NULL) {
              strcpy(nuevo->trayectoria.provincia, dato);
            }
            if ((dato = strtok(NULL, ",")) != NULL) {
              strcpy(nuevo->trayectoria.sector, dato);
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.nopromovidos[i] = atoi(dato);
              }
            }

            if ((dato = strtok(NULL, ",")) != NULL) {
              nuevo->trayectoria.secundariaEgresados = atoi(dato);
            }

            nuevo->id = 2019;
          }
          if (*registro == NULL) {
            *registro = nuevo;
          } else {
            NodoTrayectoria *aux = *registro;
            while (aux->sig != NULL) {
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
      char basura[20000];
      FILE *archivo;
      archivo = fopen("2020_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        fgets(basura, 20000, archivo);
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
            char *dato = strtok(linea, ",");
            if (dato != NULL) {
              strcpy(nuevo->trayectoria.provincia, dato);
            }
            if ((dato = strtok(NULL, ",")) != NULL) {
              strcpy(nuevo->trayectoria.sector, dato);
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.nopromovidos[i] = atoi(dato);
              }
            }
            if ((dato = strtok(NULL, ",")) != NULL) {
              nuevo->trayectoria.secundariaEgresados = atoi(dato);
            }

            nuevo->id = 2020;
          }
          if (*registro == NULL) {
            *registro = nuevo;
          } else {
            NodoTrayectoria *aux = *registro;
            while (aux->sig != NULL) {
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
      char basura[20000];
      FILE *archivo;
      archivo = fopen("2021_Trayectoria.csv", "r");
      if (archivo != NULL) {
        printf("Abriendo archivo para lectura\n");
        fgets(basura, 20000, archivo);
        while (fgets(linea, 20000, archivo) != NULL) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            nuevo->sig = NULL;
            char *dato = strtok(linea, ",");
            if (dato != NULL) {
              strcpy(nuevo->trayectoria.provincia, dato);
            }
            if ((dato = strtok(NULL, ",")) != NULL) {
              strcpy(nuevo->trayectoria.sector, dato);
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.promovidos[i] = atoi(dato);
              }
            }
            for (int i = 0; i < 6; i++) {
              if ((dato = strtok(NULL, ",")) != NULL) {
                nuevo->trayectoria.nopromovidos[i] = atoi(dato);
              }
            }
            if ((dato = strtok(NULL, ",")) != NULL) {
              nuevo->trayectoria.secundariaEgresados = atoi(dato);
            }
            nuevo->id = 2021;
          }
          if (*registro == NULL) {
            *registro = nuevo;
          } else {
            NodoTrayectoria *aux = *registro;
            while (aux->sig != NULL) {
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

void ImprimirLista(NodoTrayectoria *registro) {
  NodoTrayectoria *aux = registro;
  printf("%-25s | %-25s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | "
         "%-4s | %-4s | %-4s | %-4s | %-4s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");
  while (aux != NULL) {
    printf("%-25s | %-25s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | "
           "%-4d | %-4d | %-4d | %-4d | %-4d | %-9d | %d\n",
           aux->trayectoria.provincia, aux->trayectoria.sector,
           aux->trayectoria.promovidos[0], aux->trayectoria.promovidos[1],
           aux->trayectoria.promovidos[2], aux->trayectoria.promovidos[3],
           aux->trayectoria.promovidos[4], aux->trayectoria.promovidos[5],
           aux->trayectoria.nopromovidos[0], aux->trayectoria.nopromovidos[1],
           aux->trayectoria.nopromovidos[2], aux->trayectoria.nopromovidos[3],
           aux->trayectoria.nopromovidos[4], aux->trayectoria.nopromovidos[5],
           aux->trayectoria.secundariaEgresados, aux->id);
    aux = aux->sig;
  }
  aux = registro;

  FILE *archivo = fopen("Registro Trayectoria.txt", "w");
  if (archivo == NULL) {
    printf("Error al abrir archivo de salida\n");
    return;
  }

  fprintf(archivo,
          "%-25s | %-25s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | %-4s | "
          "%-4s | %-4s | %-4s | %-4s | %-4s | %-9s | %s\n",
          "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
          "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

  while (aux != NULL) {
    fprintf(archivo,
            "%-25s | %-25s | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | %-4d | "
            "%-4d | %-4d | %-4d | %-4d | %-4d | %-9d | %d\n",
            aux->trayectoria.provincia, aux->trayectoria.sector,
            aux->trayectoria.promovidos[0], aux->trayectoria.promovidos[1],
            aux->trayectoria.promovidos[2], aux->trayectoria.promovidos[3],
            aux->trayectoria.promovidos[4], aux->trayectoria.promovidos[5],
            aux->trayectoria.nopromovidos[0], aux->trayectoria.nopromovidos[1],
            aux->trayectoria.nopromovidos[2], aux->trayectoria.nopromovidos[3],
            aux->trayectoria.nopromovidos[4], aux->trayectoria.nopromovidos[5],
            aux->trayectoria.secundariaEgresados, aux->id);
    aux = aux->sig;
  }
  fclose(archivo);
  printf("Datos guardados correctamente\n");
}

void Liberar(NodoTrayectoria **registro) {
  while (*registro != NULL) {
    NodoTrayectoria *prox = (*registro)->sig;
    free(*registro);
    *registro = prox;
  }
  printf("\nLa lista se ha eliminado con exito\n");
}
