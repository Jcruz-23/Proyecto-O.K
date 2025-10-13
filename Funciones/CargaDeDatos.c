#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
  char tipo[10];      // publico / privado
  registroMatricula reg;
  struct Nodo *ant;
  struct Nodo *sig;
} Matricula;

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

int main() {
  NodoTrayectoria *RegistroTrayectoria = NULL;
  Matricula *RegistroMatricula = NULL;
  InsertarNodoTrayectoria(&RegistroTrayectoria);
  LecturaMatricula(&RegistroMatricula);
  ImprimirLista(RegistroTrayectoria, RegistroMatricula);
  //void Liberar(NodoTrayectoria** registro1, NodoTrayectoria** registro2, Matricula** registro3, Matricula** registro4);
  return 0;
}

void InsertarRegistroMatricula(Matricula **m, registroMatricula rM, int id,
                               char provincia[20], char tipo[10]) {
  Matricula *nuevo = (Matricula *)malloc(sizeof(Matricula));
  nuevo->sig = NULL;
  nuevo->ant = NULL;
  nuevo->id = id;
  strcpy(nuevo->provincia, provincia);
  strcpy(nuevo->tipo, tipo);
  nuevo->reg = rM;
  if (*m == NULL) {
    *m = nuevo;
  } else {
    Matricula *aux = *m;
    while (aux->sig != NULL) {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
}

void ImprimirListaMatricula(Matricula *m) {
  Matricula *aux = m;
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
  while (aux != NULL) {
    printf(
        "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
        "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
        aux->provincia, aux->tipo, aux->reg.repitentes[0],
        aux->reg.repitentes[1], aux->reg.repitentes[2], aux->reg.repitentes[3],
        aux->reg.repitentes[4], aux->reg.repitentes[5], aux->reg.matriculas[0],
        aux->reg.matriculas[1], aux->reg.matriculas[2], aux->reg.matriculas[3],
        aux->reg.matriculas[4], aux->reg.matriculas[5], aux->id);
    aux = aux->sig;
  }
}

void LecturaMatricula(Matricula **RegistroMatricula) {
  Matricula *temp = NULL;
  FILE *salida;
  int id = 0;
  char provincia[31];
  char tipo[10];
  registroMatricula rM;
  id = 2019;
  SubirMatricula("2019_Matricula.csv", &temp, rM, id, provincia, tipo);
  id = 2020;
  SubirMatricula("2020_Matricula.csv", &temp, rM, id, provincia, tipo);
  id = 2021;
  SubirMatricula("2021_Matricula.csv", &temp, rM, id, provincia, tipo);

  Matricula *aux = temp;

  salida = fopen("Salida.txt", "w");

  if (salida == NULL) {
    printf("\nError al abrir salida\n");
    return;
  }
  ClasificacionMatricula(temp, RegistroMatricula);
}


void SubirMatricula(char *archivo, Matricula **RegistroMatricula,
                    registroMatricula rM, int id, char provincia[20],
                    char tipo[10]) {
  FILE *a;
  char cabecera[300];

  a = fopen(archivo, "r");
  if (a == NULL) {
    printf("\nError al abrir archivo.csv\n");
  } else {
    fgets(cabecera, sizeof(cabecera), a);
    while (fscanf(a, "%30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                  provincia, tipo, &rM.repitentes[0], &rM.repitentes[1],
                  &rM.repitentes[2], &rM.repitentes[3], &rM.repitentes[4],
                  &rM.repitentes[5], &rM.matriculas[0], &rM.matriculas[1],
                  &rM.matriculas[2], &rM.matriculas[3], &rM.matriculas[4],
                  &rM.matriculas[5]) == 14) {
      InsertarRegistroMatricula(RegistroMatricula, rM, id, provincia, tipo);
    }
    fclose(a);
  }
}

void ClasificacionMatricula(Matricula *temp, Matricula **RegistroMatricula) {
  Matricula *tempo = temp;

  while (tempo != NULL) {

    int bandera = 0;
    Matricula *aux = *RegistroMatricula;

    while (aux != NULL && bandera == 0) {
      if (strcmp(tempo->provincia, aux->provincia) == 0 &&
          strcmp(tempo->tipo, aux->tipo) == 0 &&
          tempo->id == aux->id) { // Buscar nodo en la lista nueva primero
        bandera = 1;
      } else {
        aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
      }
    }
    if (bandera) { // Si encuentra coincidencias las suma a nuestro nodo
      for (int i = 0; i < 6; i++) {
        aux->reg.matriculas[i] += tempo->reg.matriculas[i];
        aux->reg.repitentes[i] += tempo->reg.repitentes[i];
      }

    } else { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
             // nueva
      Matricula *nuevo = (Matricula *)malloc(sizeof(Matricula));
      if (nuevo != NULL) {
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->tipo, tempo->tipo);
        nuevo->id = tempo->id;

        for (int i = 0; i < 6; i++) {
          nuevo->reg.matriculas[i] = tempo->reg.matriculas[i];
          nuevo->reg.repitentes[i] = tempo->reg.repitentes[i];
        }

        // Agregando a la lista nueva
        if (*RegistroMatricula == NULL) {
          *RegistroMatricula = nuevo;
        } else {
          Matricula *aux2 = *RegistroMatricula;
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

int Lectura(Trayectoria *trayectoria, FILE *archivo, char provincia[25],
            char sector[10]) {
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

void Carga(NodoTrayectoria **nuevo, Trayectoria trayectoria, char provincia[25],
           char sector[10]) {

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

void Clasificacion(NodoTrayectoria *temp,
                   NodoTrayectoria **RegistroTrayectoria) {
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
}


void ImprimirLista(NodoTrayectoria *trayectoria, Matricula *matricula) {
  Matricula *aux2 = matricula;
  NodoTrayectoria *aux = trayectoria;
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
  aux = trayectoria;
  
  
  FILE *archivo = fopen("Registro Completo.txt", "w");
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

  fprintf(archivo, "\n\n%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
    while(aux2 != NULL){
            fprintf(archivo,
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->tipo, aux2->reg.repitentes[0],aux2->reg.repitentes[1],aux2->reg.repitentes[2],
                    aux2->reg.repitentes[3],aux2->reg.repitentes[4],aux2->reg.repitentes[5],
                    aux2->reg.matriculas[0],aux2->reg.matriculas[1],aux2->reg.matriculas[2],
                    aux2->reg.matriculas[3],aux2->reg.matriculas[4],aux2->reg.matriculas[5], aux2->id);
        aux2 = aux2->sig;
    }
  fclose(archivo);
  printf("Datos guardados correctamente\n");

  aux2 = matricula;

  printf( "%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
            "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
    while(aux2 != NULL){
            printf(
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->tipo, aux2->reg.repitentes[0],aux2->reg.repitentes[1],aux2->reg.repitentes[2],
                    aux2->reg.repitentes[3],aux2->reg.repitentes[4],aux2->reg.repitentes[5],
                    aux2->reg.matriculas[0],aux2->reg.matriculas[1],aux2->reg.matriculas[2],
                    aux2->reg.matriculas[3],aux2->reg.matriculas[4],aux2->reg.matriculas[5], aux2->id);
        aux2 = aux2->sig;
    }
}

/*void Liberar(NodoTrayectoria** registro1, NodoTrayectoria** registro2, Matricula** registro3, Matricula** registro4) {
  while (*registro1 != NULL) {
    NodoTrayectoria *prox = (*registro1)->sig;
    free(*registro1);
    *registro2 = prox;
  }
  while (*registro2 != NULL) {
    NodoTrayectoria *prox = (*registro2)->sig;
    free(*registro2);
    *registro1 = prox;
  }
  while (*registro3 != NULL) {
    Matricula *prox = (*registro3)->sig;
    free(*registro3);
    *registro3 = prox;
  }
  while (*registro4 != NULL) {
    Matricula *prox = (*registro4)->sig;
    free(*registro4);
    *registro4 = prox;
  }
  printf("\nLa lista se ha eliminado con exito\n");
}*/