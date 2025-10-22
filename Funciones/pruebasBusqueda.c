#include "../Cabeceras/Prototipos.h"

int main() {
  NodoTrayectoria *RegistroTrayectoria = NULL;
  Matricula *RegistroMatricula = NULL;
  Matricula *tempM = NULL;
  NodoTrayectoria *tempT = NULL;
  int cont = 0;
  InsertarNodoTrayectoria(&RegistroTrayectoria);
  LecturaMatricula(&RegistroMatricula);
  ImprimirLista(RegistroTrayectoria, RegistroMatricula);
  printf("\n--- Filtro 1: Buscar por provincia ---\n");
  BuscarPorProvincia(RegistroMatricula, RegistroTrayectoria, &tempM, &tempT,
                     &cont);
  printf("\n--- Filtro 2: Buscar por tipo ---\n");
  BuscarPorTipo(RegistroMatricula, RegistroTrayectoria, &tempM, &tempT, &cont);
  printf("\n--- Filtro 3: Buscar por año ---\n");
  BuscarPorAnio(RegistroMatricula, RegistroTrayectoria, &tempM, &tempT, &cont);

  return 0;
}

void InsertarRegistroMatricula(Matricula **m, registroMatricula rM, int id,
                               char provincia[20], char tipo[10]) {
  Matricula *nuevo = (Matricula *)malloc(sizeof(Matricula));
  nuevo->sig = NULL;

  nuevo->id = id;
  strcpy(nuevo->provincia, provincia);
  strcpy(nuevo->sector, tipo);
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
        aux->provincia, aux->sector, aux->reg.repitentes[0],
        aux->reg.repitentes[1], aux->reg.repitentes[2], aux->reg.repitentes[3],
        aux->reg.repitentes[4], aux->reg.repitentes[5], aux->reg.matriculas[0],
        aux->reg.matriculas[1], aux->reg.matriculas[2], aux->reg.matriculas[3],
        aux->reg.matriculas[4], aux->reg.matriculas[5], aux->id);
    aux = aux->sig;
  }
}

void LecturaMatricula(Matricula **RegistroMatricula) {
  Matricula *temp = NULL;
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
    while (fscanf(a, " %30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
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
          strcmp(tempo->sector, aux->sector) == 0 &&
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

        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->sector, tempo->sector);
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
      archivo, " %25[^,],%10[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
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

  fprintf(archivo,
          "\n\n%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s "
          "| %-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
          "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
          "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
          "Anio");
  while (aux2 != NULL) {
    fprintf(archivo,
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matriculas[0],
            aux2->reg.matriculas[1], aux2->reg.matriculas[2],
            aux2->reg.matriculas[3], aux2->reg.matriculas[4],
            aux2->reg.matriculas[5], aux2->id);
    aux2 = aux2->sig;
  }
  fclose(archivo);
  printf("\n\n");

  aux2 = matricula;

  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
  while (aux2 != NULL) {
    printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
           "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
           aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
           aux2->reg.repitentes[1], aux2->reg.repitentes[2],
           aux2->reg.repitentes[3], aux2->reg.repitentes[4],
           aux2->reg.repitentes[5], aux2->reg.matriculas[0],
           aux2->reg.matriculas[1], aux2->reg.matriculas[2],
           aux2->reg.matriculas[3], aux2->reg.matriculas[4],
           aux2->reg.matriculas[5], aux2->id);
    aux2 = aux2->sig;
  }
}

void BuscarPorProvincia(Matricula *RegistroMatricula,
                        NodoTrayectoria *RegistroTrayectoria, Matricula **tempM,
                        NodoTrayectoria **tempT, int *cont) {
  if (*(cont) < 3) {    //Lo hara hasta que el contador sea 3, esto es para controlar que luego de pasar por los 3 filtros no continue preguntando 
    (*cont)++;
    char provincia[25];
    char provincia_normalizada[25];
    char opcion = ' ';
    int bandera = 0;

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria;    //Inicializamos una lista auxiliar que determinara cual lista filtramos, si una que ya haya sido filtrada o si filtramos la lista original
    Matricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : RegistroMatricula;    //Es una lista por cada registro

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    Matricula *nuevo_tempM = NULL;
    Matricula *lista_tempM = NULL;

   /* if (*tempT != NULL) { /* LiberarListaTrayectoria(tempT); 
      *tempT = NULL;
    }
    if (*tempM != NULL) { /* LiberarListaMatricula(tempM); 
      *tempM = NULL;
    }
      Se deben liberar las memorias de las listas temporales luego de haber aplicado todos los filtros o de que la persona no quuiera aplicar mas, es decir, en el menu cuando sale de las funciones de busqueda
    */

    printf("\nIngrese el nombre de la provincia que desee buscar: ");
    scanf(" %24[^\n]", provincia);

    
      int j = 0;
      for (int i = 0; provincia[i] != '\0' && j < 24; i++) {
        if (provincia[i] != ' ' && provincia[i] != '\t') {
          provincia_normalizada[j] = tolower((unsigned char)provincia[i]);
          j++;
        }
      }
      provincia_normalizada[j] = '\0';
    

    printf("\nLos datos encontrados son:\n");
    printf("\n\n");
    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    NodoTrayectoria *aux = lista_a_filtrar_T;

    while (aux != NULL) {
      char aux_provincia_normalizada[25];

      
        int j = 0;
        for (int i = 0; aux->provincia[i] != '\0' && j < 24; i++) {
          if (aux->provincia[i] != ' ' && aux->provincia[i] != '\t') {
            aux_provincia_normalizada[j] =
                tolower((unsigned char)aux->provincia[i]);
            j++;
          }
        }
        aux_provincia_normalizada[j] = '\0';
      

      if (strcmp(aux_provincia_normalizada, provincia_normalizada) == 0) {
        bandera = 1;
        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
            aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
            aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
            aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
            aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
            aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
            aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
            aux->trayectoria.nopromovidos[5],
            aux->trayectoria.secundariaEgresados, aux->id);
        NodoTrayectoria *nuevo =
            (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
        if (nuevo != NULL) {
          nuevo->sig = NULL;
          strcpy(nuevo->provincia, aux->provincia);
          strcpy(nuevo->sector, aux->sector);
          nuevo->id = aux->id;
          for (int i = 0; i < 6; i++) {
            nuevo->trayectoria.nopromovidos[i] =
                aux->trayectoria.nopromovidos[i];
            nuevo->trayectoria.promovidos[i] = aux->trayectoria.promovidos[i];
          }
          nuevo->trayectoria.secundariaEgresados =
              aux->trayectoria.secundariaEgresados;

          if (nuevo_tempT == NULL) {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          } else {
            lista_tempT->sig = nuevo;
            lista_tempT = nuevo;
          }
        } else {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux = aux->sig;
    }

    *tempT = nuevo_tempT;

    if (bandera == 0) {
      printf("\nNo se ha encontrado trayectoria en la provincia ingresada\n");
    }
    bandera = 0;
    printf("\n\n");
    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    Matricula *aux2 = lista_a_filtrar_M;

    while (aux2 != NULL) {
      char aux2_provincia_normalizada[25];
      {
        int j = 0;
        for (int i = 0; aux2->provincia[i] != '\0' && j < 24; i++) {
          if (aux2->provincia[i] != ' ' && aux2->provincia[i] != '\t') {
            aux2_provincia_normalizada[j] =
                tolower((unsigned char)aux2->provincia[i]);
            j++;
          }
        }
        aux2_provincia_normalizada[j] = '\0';
      }

      if (strcmp(aux2_provincia_normalizada, provincia_normalizada) == 0) {
        bandera = 1;
        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matriculas[0],
            aux2->reg.matriculas[1], aux2->reg.matriculas[2],
            aux2->reg.matriculas[3], aux2->reg.matriculas[4],
            aux2->reg.matriculas[5], aux2->id);
        Matricula *nuevo2 = (Matricula *)malloc(sizeof(Matricula));
        if (nuevo2 != NULL) {
          nuevo2->sig = NULL;
          strcpy(nuevo2->provincia, aux2->provincia);
          strcpy(nuevo2->sector, aux2->sector);
          nuevo2->id = aux2->id;
          for (int i = 0; i < 6; i++) {
            nuevo2->reg.matriculas[i] = aux2->reg.matriculas[i];
            nuevo2->reg.repitentes[i] = aux2->reg.repitentes[i];
          }

          if (nuevo_tempM == NULL) {
            nuevo_tempM = nuevo2;
            lista_tempM = nuevo2;
          } else {
            lista_tempM->sig = nuevo2;
            lista_tempM = nuevo2;
          }
        } else {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux2 = aux2->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0) {
      printf("\nNo se han encontrado datos de la provincia ingresada\n");
    }
    bandera = 0;

    if ((*cont) < 3) {
      printf("\nDesea agregar otro filtro\?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S') {
        opcion = ' ';
        printf("\nLos filtros que puede agregar son:\n");
        printf("a) Buscar por año\n");
        printf("b) Buscar por sector\n");
        scanf(" %c", &opcion);

        switch (opcion) {
        case 'a':
          BuscarPorAnio(RegistroMatricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        case 'b':
          BuscarPorTipo(RegistroMatricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nNo ha ingresado una opcion valida\n");
        }
      }
    }
  }
  if((*cont) > 3){
  cont = 0;
  }
}

void BuscarPorAnio(Matricula *RegistroMatricula,
                   NodoTrayectoria *RegistroTrayectoria, Matricula **tempM,
                   NodoTrayectoria **tempT, int *cont) {
  if (*(cont) < 3) {
    (*cont)++;
    int anio = 0, bandera = 0;
    char opcion = ' ';

    printf("\nIngrese el año que desee buscar: ");
    scanf("%d", &anio);

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria;
    Matricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : RegistroMatricula;

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    Matricula *nuevo_tempM = NULL;
    Matricula *lista_tempM = NULL;

    /* if (*tempT != NULL) { /* LiberarListaTrayectoria(tempT); 
      *tempT = NULL;
    }
    if (*tempM != NULL) { /* LiberarListaMatricula(tempM); 
      *tempM = NULL;
    }
      Se deben liberar las memorias de las listas temporales luego de haber aplicado todos los filtros o de que la persona no quuiera aplicar mas, es decir, en el menu cuando sale de las funciones de busqueda
    */

    NodoTrayectoria *auxT = lista_a_filtrar_T;

    printf("\nDatos encontrados del año %d:\n\n", anio);
    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    while (auxT != NULL) {
      if (auxT->id == anio) {
        bandera = 1;
        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
            auxT->provincia, auxT->sector, auxT->trayectoria.promovidos[0],
            auxT->trayectoria.promovidos[1], auxT->trayectoria.promovidos[2],
            auxT->trayectoria.promovidos[3], auxT->trayectoria.promovidos[4],
            auxT->trayectoria.promovidos[5], auxT->trayectoria.nopromovidos[0],
            auxT->trayectoria.nopromovidos[1],
            auxT->trayectoria.nopromovidos[2],
            auxT->trayectoria.nopromovidos[3],
            auxT->trayectoria.nopromovidos[4],
            auxT->trayectoria.nopromovidos[5],
            auxT->trayectoria.secundariaEgresados, auxT->id);

        NodoTrayectoria *nuevo = malloc(sizeof(NodoTrayectoria));
        if (nuevo != NULL) {
          *nuevo = *auxT;
          nuevo->sig = NULL;

          if (nuevo_tempT == NULL) {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          } else {

            lista_tempT->sig = nuevo;
            lista_tempT = nuevo;
          }
        }
      }
      auxT = auxT->sig;
    }

    *tempT = nuevo_tempT;

    if (!bandera)
      printf("\nNo se encontraron trayectorias en el año ingresado.\n");

    bandera = 0;
    printf("\n\n");

    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    Matricula *auxM = lista_a_filtrar_M;

    while (auxM != NULL) {
      if (auxM->id == anio) {
        bandera = 1;
        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            auxM->provincia, auxM->sector, auxM->reg.repitentes[0],
            auxM->reg.repitentes[1], auxM->reg.repitentes[2],
            auxM->reg.repitentes[3], auxM->reg.repitentes[4],
            auxM->reg.repitentes[5], auxM->reg.matriculas[0],
            auxM->reg.matriculas[1], auxM->reg.matriculas[2],
            auxM->reg.matriculas[3], auxM->reg.matriculas[4],
            auxM->reg.matriculas[5], auxM->id);

        Matricula *nuevoM = malloc(sizeof(Matricula));
        if (nuevoM != NULL) {
          *nuevoM = *auxM;
          nuevoM->sig = NULL;

          if (nuevo_tempM == NULL) {
            nuevo_tempM = nuevoM;
            lista_tempM = nuevoM;
          } else {
            lista_tempM->sig = nuevoM;
            lista_tempM = nuevoM;
          }
        }
      }
      auxM = auxM->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0){
      printf("\nNo se encontraron datos de matrícula en el año ingresado\n");
    }

    if ((*cont) < 3) {
      printf("\n¿Desea agregar otro filtro?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S') {
        printf("\nFiltros disponibles:\n");
        printf("a) Buscar por provincia\n");
        printf("b) Buscar por sector\n");
        scanf(" %c", &opcion);

        switch (opcion) {
        case 'a':
          BuscarPorProvincia(RegistroMatricula, RegistroTrayectoria, tempM,
                             tempT, cont);
          break;
        case 'b':
          BuscarPorTipo(RegistroMatricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nOpción no válida.\n");
        }
      }
    }
  }
  if((*cont) > 3){
  cont = 0;
  }
}

void BuscarPorTipo(Matricula *RegistroMatricula,
                   NodoTrayectoria *RegistroTrayectoria, Matricula **tempM,
                   NodoTrayectoria **tempT, int *cont) {
  if (*(cont) < 3) {
    (*cont)++;
    char tipo[25];
    char tipo_normalizado[25];
    char opcion = ' ';
    int bandera = 0;

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria;
    Matricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : RegistroMatricula;

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    Matricula *nuevo_tempM = NULL;
    Matricula *lista_tempM = NULL;

    /* if (*tempT != NULL) { /* LiberarListaTrayectoria(tempT); 
      *tempT = NULL;
    }
    if (*tempM != NULL) { /* LiberarListaMatricula(tempM); 
      *tempM = NULL;
    }
      Se deben liberar las memorias de las listas temporales luego de haber aplicado todos los filtros o de que la persona no quuiera aplicar mas, es decir, en el menu cuando sale de las funciones de busqueda
    */

    printf("\nIngrese el tipo que desee buscar: ");
    scanf(" %24[^\n]", tipo);

    
      int j = 0;
      for (int i = 0; tipo[i] != '\0' && j < 10; i++) {
        if (tipo[i] != ' ' && tipo[i] != '\t') {
          tipo_normalizado[j] = tolower((unsigned char)tipo[i]);
          j++;
        }
      }
      tipo_normalizado[j] = '\0';
    

    printf("\nLos datos encontrados son:\n");
    printf("\n\n");
    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    NodoTrayectoria *aux = lista_a_filtrar_T;

    while (aux != NULL) {
      char aux_sector_normalizado[25];

      {
        int j = 0;
        for (int i = 0; aux->sector[i] != '\0' && j < 10; i++) {
          if (aux->sector[i] != ' ' && aux->sector[i] != '\t') {
            aux_sector_normalizado[j] = tolower((unsigned char)aux->sector[i]);
            j++;
          }
        }
        aux_sector_normalizado[j] = '\0';
      }

      if (strcmp(aux_sector_normalizado, tipo_normalizado) == 0) {
        bandera = 1;

        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
            aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
            aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
            aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
            aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
            aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
            aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
            aux->trayectoria.nopromovidos[5],
            aux->trayectoria.secundariaEgresados, aux->id);

        NodoTrayectoria *nuevo =
            (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
        if (nuevo != NULL) {
          nuevo->sig = NULL;
          strcpy(nuevo->sector, aux->sector);
          strcpy(nuevo->provincia, aux->provincia);
          nuevo->id = aux->id;
          for (int i = 0; i < 6; i++) {
            nuevo->trayectoria.nopromovidos[i] =
                aux->trayectoria.nopromovidos[i];
            nuevo->trayectoria.promovidos[i] = aux->trayectoria.promovidos[i];
          }
          nuevo->trayectoria.secundariaEgresados =
              aux->trayectoria.secundariaEgresados;

          if (nuevo_tempT == NULL) {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          } else {
            lista_tempT->sig = nuevo;
            lista_tempT = nuevo;
          }
        } else {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux = aux->sig;
    }

    *tempT = nuevo_tempT;

    if (bandera == 0) {
      printf("\nNo se ha encontrado el tipo ingresado\n");
    }
    bandera = 0;
    printf("\n\n");
    printf("%-15s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    Matricula *aux2 = lista_a_filtrar_M;

    while (aux2 != NULL) {
      char aux2_sector_normalizado[25];

      {
        int j = 0;
        for (int i = 0; aux2->sector[i] != '\0' && j < 24; i++) {
          if (aux2->sector[i] != ' ' && aux2->sector[i] != '\t') {
            aux2_sector_normalizado[j] =
                tolower((unsigned char)aux2->sector[i]);
            j++;
          }
        }
        aux2_sector_normalizado[j] = '\0';
      }

      if (strcmp(aux2_sector_normalizado, tipo_normalizado) == 0) {
        bandera = 1;
        printf(
            "%-15s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matriculas[0],
            aux2->reg.matriculas[1], aux2->reg.matriculas[2],
            aux2->reg.matriculas[3], aux2->reg.matriculas[4],
            aux2->reg.matriculas[5], aux2->id);

        Matricula *nuevo2 = (Matricula *)malloc(sizeof(Matricula));
        if (nuevo2 != NULL) {
          nuevo2->sig = NULL;
          strcpy(nuevo2->sector, aux2->sector);
          strcpy(nuevo2->provincia, aux2->provincia);
          nuevo2->id = aux2->id;
          for (int i = 0; i < 6; i++) {
            nuevo2->reg.matriculas[i] = aux2->reg.matriculas[i];
            nuevo2->reg.repitentes[i] = aux2->reg.repitentes[i];
          }

          if (nuevo_tempM == NULL) {
            nuevo_tempM = nuevo2;
            lista_tempM = nuevo2;
          } else {
            lista_tempM->sig = nuevo2;
            lista_tempM = nuevo2;
          }
        } else {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux2 = aux2->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0) {
      printf("\nNo se ha encontrado el tipo ingresado\n");
    }
    bandera = 0;

    if ((*cont) < 3) {
      printf("\nDesea agregar otro filtro\?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S') {
        printf("\nFiltros disponibles:\n");
        printf("a) Buscar por provincia\n");
        printf("b) Buscar por anio\n");
        scanf(" %c", &opcion);

        switch (opcion) {
        case 'a':
          BuscarPorProvincia(RegistroMatricula, RegistroTrayectoria, tempM,
                             tempT, cont);
          break;
        case 'b':
          BuscarPorAnio(RegistroMatricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nOpción no válida.\n");
        }
      }
    }
  }
  if((*cont) > 3){
  cont = 0;
  }
}