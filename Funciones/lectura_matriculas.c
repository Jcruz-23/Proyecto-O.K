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

void agregar(Matricula**, registroMatricula, int, char[20], char[10]);
void mostrar(Matricula*);
void liberar(Matricula**);
void lectura(Matricula**, Matricula**, Matricula**);

int main(){
    Matricula* m_2019 = NULL;
    Matricula* m_2020 = NULL;
    Matricula* m_2021 = NULL;

    lectura(&m_2019, &m_2020, &m_2021);
    
    mostrar(m_2019);

    liberar(&m_2019);
    liberar(&m_2020);
    liberar(&m_2021);
    return 0;
}

void agregar(Matricula** m, registroMatricula rM, int id, char provincia[20], char tipo[10]){
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

void mostrar(Matricula* m){
    Matricula* aux = m;
    while(aux != NULL){
        printf(" %s | %s | %d ", aux->provincia, aux->tipo, aux->id);
    for(int i=0; i<6; i++){
        printf("| %d anio | %d | %d",i+1, aux->reg.matriculas[i], aux->reg.repitentes[i]);
    }
    printf("\n");
        aux = aux->sig;
    }
}

void lectura(Matricula** m_2019, Matricula** m_2020, Matricula** m_2021){
    FILE* matricula2019;
    FILE* matricula2020;
    FILE* matricula2021;
    FILE* salida;

    int id = 0;
    char provincia[31]; 
    char tipo[10];
    registroMatricula rM;
    char cabecera[200];

    salida = fopen("Salida.txt", "w");
    if(salida == NULL){
        printf("\nError al abrir salida\n");
        return;
    }

// -------- MATRÍCULA 2019 --------
    matricula2019 = fopen("2019_Matricula.csv", "r");
    if(matricula2019 == NULL){
        printf("\nError al abrir 2019_Matricula.csv\n");
    } else {
        fgets(cabecera, sizeof(cabecera), matricula2019);
        id = 2019;
        fprintf(salida, "\n--- DATOS %d ---\n", id);
        while(fscanf(matricula2019, "%30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                    provincia, tipo,
                    &rM.repitentes[0],&rM.repitentes[1],&rM.repitentes[2],
                    &rM.repitentes[3],&rM.repitentes[4],&rM.repitentes[5],
                    &rM.matriculas[0],&rM.matriculas[1],&rM.matriculas[2],
                    &rM.matriculas[3],&rM.matriculas[4],&rM.matriculas[5]) == 14){
            agregar(m_2019, rM, id, provincia, tipo);
            fprintf(salida, "%s | %s | %d", provincia, tipo, id);
            for(int i = 0; i < 6; i++){
                fprintf(salida, " | %d anio | %d | %d", i+1, rM.matriculas[i], rM.repitentes[i]);
            }
            fprintf(salida, "\n");
        }
        fclose(matricula2019);
    }
// -------- MATRÍCULA 2020 --------
    matricula2020 = fopen("2020_Matricula.csv", "r");
    if(matricula2020 == NULL){
        printf("\nError al abrir 2020_Matricula.csv\n");
    } else {
        fgets(cabecera, sizeof(cabecera), matricula2020);
        id = 2020;
        fprintf(salida, "\n--- DATOS %d ---\n", id);
        while(fscanf(matricula2020, "%30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                    provincia, tipo,
                    &rM.repitentes[0],&rM.repitentes[1],&rM.repitentes[2],
                    &rM.repitentes[3],&rM.repitentes[4],&rM.repitentes[5],
                    &rM.matriculas[0],&rM.matriculas[1],&rM.matriculas[2],
                    &rM.matriculas[3],&rM.matriculas[4],&rM.matriculas[5]) == 14){
            agregar(m_2020, rM, id, provincia, tipo);
            fprintf(salida, "%s | %s | %d", provincia, tipo, id);
            for(int i = 0; i < 6; i++){
                fprintf(salida, " | %d anio | %d | %d", i+1, rM.matriculas[i], rM.repitentes[i]);
            }
            fprintf(salida, "\n");
        }
        fclose(matricula2020);
    }
// -------- MATRÍCULA 2021 --------
    matricula2021 = fopen("2021_Matricula.csv", "r");
    if(matricula2021 == NULL){
        printf("\nError al abrir 2021_Matricula.csv\n");
    } else {
        fgets(cabecera, sizeof(cabecera), matricula2021);
        id = 2021;
        fprintf(salida, "\n--- DATOS %d ---\n", id);
        while(fscanf(matricula2021, "%30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                    provincia, tipo,
                    &rM.repitentes[0],&rM.repitentes[1],&rM.repitentes[2],
                    &rM.repitentes[3],&rM.repitentes[4],&rM.repitentes[5],
                    &rM.matriculas[0],&rM.matriculas[1],&rM.matriculas[2],
                    &rM.matriculas[3],&rM.matriculas[4],&rM.matriculas[5]) == 14){
            agregar(m_2021, rM, id, provincia, tipo);
            fprintf(salida, "%s | %s | %d", provincia, tipo, id);
            for(int i = 0; i < 6; i++){
                fprintf(salida, " | %d anio | %d | %d", i+1, rM.matriculas[i], rM.repitentes[i]);
            }
            fprintf(salida, "\n");
        }
        fclose(matricula2021);
    }

    fclose(salida);
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
