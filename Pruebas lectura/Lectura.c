#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
    int anio[6];       // años de escolaridad.
    int matriculas[6]; // matrícula.
    int repitentes[6]; // cantidad de repitentes.
} registroMatricula;

typedef struct Nodo
{
    int id;             // año
    char provincia[20]; // provincias
    char tipo[10];      // publico / privado
    registroMatricula reg;
    struct Nodo *ant;
    struct Nodo *sig;
} Matricula;

void agregar(Matricula**, registroMatricula, int, char[20], char[10]);
//void lectura(Matricula*, registroMatricula, int, char[20], char[10]);

int main(){
    FILE* archivo;
    Matricula* m;
    int id = 0;
    char provincia[20];
    char tipo[10];
    registroMatricula rM;
    char linea[200];
    char cabecera[100];
    fopen("2019_Matricula.csv", "r");
    if(archivo==NULL){
        printf("\nError al abrir archivo\n");
        return 1;
    }
    fgets(cabecera, sizeof(cabecera), archivo);

    while(fscanf(archivo, "%19[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",provincia, tipo, rM.repitentes[0],rM.repitentes[1],rM.repitentes[2],rM.repitentes[3],rM.repitentes[4],rM.repitentes[5],rM.matriculas[0],rM.matriculas[1],rM.matriculas[2],rM.matriculas[3],rM.matriculas[4],rM.matriculas[5]) == 14){
        agregar(&m, )
    }
    return 0;
}

void agregar(Matricula** m, registroMatricula rM, int id, char provincia[20], char tipo[10]){
    Matricula* nuevo = (Matricula*) malloc(sizeof(Matricula));
    nuevo->id = id;
    strcpy(provincia, nuevo->provincia);
    strcpy(tipo, nuevo->tipo);
    for(int i=0;i<6-1;i++){
        nuevo->reg.matriculas[i] = rM.matriculas[i];
        nuevo->reg.repitentes[i] = rM.repitentes[i];
    }
    
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