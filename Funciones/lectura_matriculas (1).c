#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    int matriculas[6]; // matrícula.
    int repitentes[6]; // cantidad de repitentes.
} registroMatricula;

typedef struct Nodo
{
    int id;             // año
    char provincia[30]; // provincias
    char tipo[10];      // publico / privado
    registroMatricula reg;
    struct Nodo *ant;
    struct Nodo *sig;
} Matricula;

void InsertarRegistroMatricula(Matricula**, registroMatricula, int, char[20], char[10]);
void ImprimirListaMatricula(Matricula*);
void liberar(Matricula**);
void LecturaMatricula(Matricula**);
void SubirMatricula(char*, Matricula**,registroMatricula, int, char[20], char[10]);
void ClasificacionMatricula(Matricula*, Matricula**);

int main(){
    Matricula* RegistroMatricula = NULL;
    LecturaMatricula(&RegistroMatricula);
    ImprimirListaMatricula(RegistroMatricula);
    liberar(&RegistroMatricula);
    return 0;
}

void InsertarRegistroMatricula(Matricula** m, registroMatricula rM, int id, char provincia[20], char tipo[10]){
    Matricula* nuevo = (Matricula*) malloc(sizeof(Matricula));
    nuevo->sig = NULL;
    nuevo->ant = NULL;
    nuevo->id = id;
    strcpy(nuevo->provincia, provincia);
    strcpy(nuevo->tipo, tipo);
    nuevo->reg = rM;
    if(*m == NULL){
        *m = nuevo;
    }else{
        Matricula* aux = *m;
        while(aux ->sig != NULL){
            aux = aux->sig;
        }
        aux->sig = nuevo;
    }
}

void ImprimirListaMatricula(Matricula* m){
    Matricula* aux = m;
    printf("%-25s | %-10s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | "
            "%-7s | %-7s | %-7s | %-7s | %-7s | %s\n",
            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
    while(aux != NULL){
            printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
                    "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
                    aux->provincia, aux->tipo, aux->reg.repitentes[0],aux->reg.repitentes[1],aux->reg.repitentes[2],
                    aux->reg.repitentes[3],aux->reg.repitentes[4],aux->reg.repitentes[5],
                    aux->reg.matriculas[0],aux->reg.matriculas[1],aux->reg.matriculas[2],
                    aux->reg.matriculas[3],aux->reg.matriculas[4],aux->reg.matriculas[5], aux->id);
        aux = aux->sig;
    }
}

void LecturaMatricula(Matricula** RegistroMatricula){
    Matricula* temp = NULL;
    FILE* salida;
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

    Matricula* aux = temp;

    salida = fopen("Salida.txt", "w");

    if(salida == NULL){
        printf("\nError al abrir salida\n");
        return;
    }

    fprintf(salida, "%-25s | %-10s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | %-7s | "
            "%-7s | %-7s | %-7s | %-7s | %-7s | %s\n",
            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
    while(aux != NULL){
            fprintf(salida,
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux->provincia, aux->tipo, aux->reg.repitentes[0],aux->reg.repitentes[1],aux->reg.repitentes[2],
                    aux->reg.repitentes[3],aux->reg.repitentes[4],aux->reg.repitentes[5],
                    aux->reg.matriculas[0],aux->reg.matriculas[1],aux->reg.matriculas[2],
                    aux->reg.matriculas[3],aux->reg.matriculas[4],aux->reg.matriculas[5], aux->id);
        aux = aux->sig;
    }
   
    fclose(salida);

    ClasificacionMatricula(temp, RegistroMatricula);

}


void liberar(Matricula** m){
if (m == NULL || *m == NULL) return;
    Matricula* aux = *m;
    while (aux != NULL){
    Matricula* siguiente = aux->sig;
    free(aux);
    aux = siguiente;
}
*m = NULL;
}

void SubirMatricula(char* archivo, Matricula** RegistroMatricula, registroMatricula rM, int id, char provincia[20], char tipo[10]){
    FILE* a;
    char cabecera[300];

    a = fopen(archivo, "r");
    if(a == NULL){
        printf("\nError al abrir archivo.csv\n");
    } else {
        fgets(cabecera, sizeof(cabecera), a);
        while(fscanf(a, "%30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                    provincia, tipo,
                    &rM.repitentes[0],&rM.repitentes[1],&rM.repitentes[2],
                    &rM.repitentes[3],&rM.repitentes[4],&rM.repitentes[5],
                    &rM.matriculas[0],&rM.matriculas[1],&rM.matriculas[2],
                    &rM.matriculas[3],&rM.matriculas[4],&rM.matriculas[5]) == 14){
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
      Matricula *nuevo =
          (Matricula *)malloc(sizeof(Matricula));
      if (nuevo != NULL) {
        nuevo->ant = NULL;
        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->tipo, tempo->tipo);
        nuevo->id = tempo->id;

        for (int i = 0; i < 6; i++) {
          nuevo->reg.matriculas[i] =
              tempo->reg.matriculas[i];
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
  liberar(&temp);
}