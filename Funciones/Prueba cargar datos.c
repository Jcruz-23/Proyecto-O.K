#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int secundariaEgresados; // cantidad de egresos.
  int promovidos[6];       // aprobados
  int nopromovidos[6];     // no aprobados
  char provincia[25];      // provincia del dato
  char sector[10];         // estatal o privado
} Trayectoria;

typedef struct NodoTrayectoria {
  Trayectoria trayectoria;
  int id;
  struct NodoTrayectoria *sig;
  struct NodoTrayectoria *ant;
} NodoTrayectoria;

void InsertarNodoTrayectoria(NodoTrayectoria **, Trayectoria);
void ImprimirLista(NodoTrayectoria *);
void Liberar(NodoTrayectoria **);
int Lectura(Trayectoria *, FILE *);
void Carga(NodoTrayectoria **, Trayectoria);

int main() {
  NodoTrayectoria *registro = NULL;
  Trayectoria trayectoria = {0};
  InsertarNodoTrayectoria(&registro, trayectoria);
  ImprimirLista(registro);
  Liberar(&registro);
  return 0;
}

void InsertarNodoTrayectoria(NodoTrayectoria **registro, Trayectoria trayectoria) {

  for (int i = 0; i < 3; i++) {
    
    if (i == 0) {
      char basura[20000];
      FILE *archivo;
      archivo = fopen("2019_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria);
            nuevo->id = 2019;
            if (*registro == NULL) {
              *registro = nuevo;
              nuevo->ant = NULL;
            } else {
              NodoTrayectoria *aux = *registro;
              while (aux->sig != NULL) {
                aux = aux->sig;
              }
              nuevo->ant = aux;
              aux->sig = nuevo;
            }
          } else {
            printf("Error al crear nuevo nodo\n");
          }
        }
      }
      fclose(archivo);
      printf("\nArchivo leido con exito\n");
    }

    if (i == 1) {
      char basura[20000];
      FILE *archivo;
      archivo = fopen("2020_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria);
            nuevo->id = 2020;
            if (*registro == NULL) {
              *registro = nuevo;
              nuevo->ant = NULL;
            } else {
              NodoTrayectoria *aux = *registro;
              while (aux->sig != NULL) {
                aux = aux->sig;
              }
              nuevo->ant = aux;
              aux->sig = nuevo;
            }
          } else {
            printf("Error al crear nuevo nodo\n");
          }
        }
      }
      fclose(archivo);
      printf("\nArchivo leido con exito\n");
    }
    if (i == 2) {
      char basura[20000];
      FILE *archivo;
      archivo = fopen("2021_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria);
            nuevo->id = 2021;
            if (*registro == NULL) {
              *registro = nuevo;
              nuevo->ant = NULL;
            } else {
              NodoTrayectoria *aux = *registro;
              while (aux->sig != NULL) {
                aux = aux->sig;
              }
              nuevo->ant = aux;
              aux->sig = nuevo;
            }
          } else {
            printf("Error al crear nuevo nodo\n");
          }
        }
      }
      fclose(archivo);
      printf("\nArchivo leido con exito\n");
    }
  }
}

int Lectura(Trayectoria *trayectoria, FILE *archivo) {
  int cant = 0;
  printf("Abriendo archivo para lectura\n");
  cant = (fscanf(
      archivo, "%25[^,],%15[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      trayectoria->provincia, trayectoria->sector, &trayectoria->promovidos[0],
      &trayectoria->promovidos[1], &trayectoria->promovidos[2],
      &trayectoria->promovidos[3], &trayectoria->promovidos[4],
      &trayectoria->promovidos[5], &trayectoria->nopromovidos[0],
      &trayectoria->nopromovidos[1], &trayectoria->nopromovidos[2],
      &trayectoria->nopromovidos[3], &trayectoria->nopromovidos[4],
      &trayectoria->nopromovidos[5], &trayectoria->secundariaEgresados));
  return cant;
}

void Carga(NodoTrayectoria **nuevo, Trayectoria trayectoria){
            (*nuevo)->sig = NULL;
            strcpy((*nuevo)->trayectoria.provincia, trayectoria.provincia);
            strcpy((*nuevo)->trayectoria.sector, trayectoria.sector);
            (*nuevo)->trayectoria.promovidos[0] = trayectoria.promovidos[0];
            (*nuevo)->trayectoria.promovidos[1] = trayectoria.promovidos[1];
            (*nuevo)->trayectoria.promovidos[2] = trayectoria.promovidos[2];
            (*nuevo)->trayectoria.promovidos[3] = trayectoria.promovidos[3];
            (*nuevo)->trayectoria.promovidos[4] = trayectoria.promovidos[4];
            (*nuevo)->trayectoria.promovidos[5] = trayectoria.promovidos[5];
            (*nuevo)->trayectoria.nopromovidos[0] = trayectoria.nopromovidos[0];
            (*nuevo)->trayectoria.nopromovidos[1] = trayectoria.nopromovidos[1];
            (*nuevo)->trayectoria.nopromovidos[2] = trayectoria.nopromovidos[2];
            (*nuevo)->trayectoria.nopromovidos[3] = trayectoria.nopromovidos[3];
            (*nuevo)->trayectoria.nopromovidos[4] = trayectoria.nopromovidos[4];
            (*nuevo)->trayectoria.nopromovidos[5] = trayectoria.nopromovidos[5];
            (*nuevo)->trayectoria.secundariaEgresados =
                trayectoria.secundariaEgresados;
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