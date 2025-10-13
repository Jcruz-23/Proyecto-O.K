#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  int secundariaEgresados; // cantidad de egresos.
  int promovidos[6];       // aprobados
  int nopromovidos[6];     // no aprobados
} Trayectoria;

typedef struct NodoTrayectoria {
  Trayectoria trayectoria;
  char provincia[25]; // provincia del dato
  char sector[10];    // estatal o privado
  int id;  
  struct NodoTrayectoria *sig;
  struct NodoTrayectoria *ant;
} NodoTrayectoria;

void InsertarNodoTrayectoria(NodoTrayectoria **);
void ImprimirLista(NodoTrayectoria *);
void Liberar(NodoTrayectoria **);
int Lectura(Trayectoria *, FILE *, char [25], char [10]);
void Carga(NodoTrayectoria **, Trayectoria, char [25], char [10]);
void Clasificacion(NodoTrayectoria *, NodoTrayectoria **);

int main() {
  NodoTrayectoria *RegistroTrayectoria = NULL;
  InsertarNodoTrayectoria(&RegistroTrayectoria);
  ImprimirLista(RegistroTrayectoria);
  Liberar(&RegistroTrayectoria);
  return 0;
}

void InsertarNodoTrayectoria(NodoTrayectoria **RegistroTrayectoria) {
  char provincia[25];
  char sector[10];
  NodoTrayectoria *temp = NULL;
  Trayectoria trayectoria = {0};
 
  for (int i = 0; i < 3; i++) {

    if (i == 0) {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("2019_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2019;
            if (temp == NULL) {
              temp = nuevo;    
            } else {
              NodoTrayectoria *aux = temp;
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
        fclose(archivo);
      }
      printf("\nArchivo leido con exito\n");
    }

    if (i == 1) {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("2020_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2020;
            if (temp == NULL) {
              temp = nuevo;
            } else {
              NodoTrayectoria *aux = temp;
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
        fclose(archivo);
      }
      printf("\nArchivo leido con exito\n");
    }
    if (i == 2) {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("2021_Trayectoria.csv", "r");
      if (archivo == NULL) {
        printf("\nNo se pudo leer el archivo\n");
      } else {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15) {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL) {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2021;
            if (temp == NULL) {
              temp = nuevo;
            } else {
              NodoTrayectoria *aux = temp;
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
        fclose(archivo);
      }
      printf("\nArchivo leido con exito\n");
    }
  }

  Clasificacion(temp, RegistroTrayectoria);
}

int Lectura(Trayectoria *trayectoria, FILE *archivo, char provincia[25], char sector[10]) {
  int cant = 0;
  cant = (fscanf(
      archivo, "%25[^,],%10[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
      provincia, sector, &trayectoria->promovidos[0],
      &trayectoria->promovidos[1], &trayectoria->promovidos[2],
      &trayectoria->promovidos[3], &trayectoria->promovidos[4],
      &trayectoria->promovidos[5], &trayectoria->nopromovidos[0],
      &trayectoria->nopromovidos[1], &trayectoria->nopromovidos[2],
      &trayectoria->nopromovidos[3], &trayectoria->nopromovidos[4],
      &trayectoria->nopromovidos[5], &trayectoria->secundariaEgresados));
  return cant;
}

void Carga(NodoTrayectoria **nuevo, Trayectoria trayectoria, char provincia[25], char sector[10]) {
  
  (*nuevo)->ant = NULL;
  (*nuevo)->sig = NULL;
  strcpy((*nuevo)->provincia, provincia);
  strcpy((*nuevo)->sector, sector);
  for (int i = 0; i < 6; i++) {
    (*nuevo)->trayectoria.promovidos[i] = trayectoria.promovidos[i];
    (*nuevo)->trayectoria.nopromovidos[i] = trayectoria.nopromovidos[i];
  }
  (*nuevo)->trayectoria.secundariaEgresados = trayectoria.secundariaEgresados;
}

void Clasificacion(NodoTrayectoria *temp, NodoTrayectoria **RegistroTrayectoria) {
  NodoTrayectoria *tempo = temp;

  while (tempo != NULL) {

    int bandera = 0;
    NodoTrayectoria *aux = *RegistroTrayectoria;

    while (aux != NULL && bandera == 0) {
      if (strcmp(tempo->provincia, aux->provincia) == 0 &&
          strcmp(tempo->sector, aux->sector) == 0 &&
          tempo->id == aux->id) { // Buscar nodo en la lista nueva primero
        bandera = 1;
      } else {
        aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
      }
    }
    if (bandera) { // Si encuentra coincidencias las suma a nuestro nodo
      for (int i = 0; i < 6; i++) {
        aux->trayectoria.nopromovidos[i] += tempo->trayectoria.nopromovidos[i];
        aux->trayectoria.promovidos[i] += tempo->trayectoria.promovidos[i];
      }
      aux->trayectoria.secundariaEgresados +=
          tempo->trayectoria.secundariaEgresados;

    } else { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
             // nueva
      NodoTrayectoria *nuevo =
          (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
      if (nuevo != NULL) {
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->sector, tempo->sector);
        nuevo->id = tempo->id;

        for (int i = 0; i < 6; i++) {
          nuevo->trayectoria.nopromovidos[i] =
              tempo->trayectoria.nopromovidos[i];
          nuevo->trayectoria.promovidos[i] = tempo->trayectoria.promovidos[i];
        }
        nuevo->trayectoria.secundariaEgresados =
            tempo->trayectoria.secundariaEgresados;
        // Agregando a la lista nueva
        if (*RegistroTrayectoria == NULL) {
          *RegistroTrayectoria = nuevo;
        } else {
          NodoTrayectoria *aux2 = *RegistroTrayectoria;
          while (aux2->sig != NULL) {
            aux2 = aux2->sig;
          }
          nuevo->ant = aux2;
          aux2->sig = nuevo;
        }
      } else {
        printf("\nNo se ha podido crear el nodo\n");
      }
    }
    tempo = tempo->sig;
  }
  Liberar(&temp);
}

void ImprimirLista(NodoTrayectoria *temp) {
  NodoTrayectoria *aux = temp;
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");
  while (aux != NULL) {
    printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
           "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
           aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
           aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
           aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
           aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
           aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
           aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
           aux->trayectoria.nopromovidos[5],
           aux->trayectoria.secundariaEgresados, aux->id);
    aux = aux->sig;
  }
  aux = temp;

  FILE *archivo = fopen("temp Trayectoria.txt", "w");
  if (archivo == NULL) {
    printf("Error al abrir archivo de salida\n");
    return;
  }

  fprintf(archivo,
          "%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
          "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
          "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
          "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

  while (aux != NULL) {
    fprintf(archivo,
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
            aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
            aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
            aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
            aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
            aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
            aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
            aux->trayectoria.nopromovidos[5],
            aux->trayectoria.secundariaEgresados, aux->id);
    aux = aux->sig;
  }
  fclose(archivo);
  printf("Datos guardados correctamente\n");
}

void Liberar(NodoTrayectoria **temp) {
  while (*temp != NULL) {
    NodoTrayectoria *prox = (*temp)->sig;
    free(*temp);
    *temp = prox;
  }
  printf("\nLa lista se ha eliminado con exito\n");
}