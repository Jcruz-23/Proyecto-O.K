#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <limits.h>

int main(){
    char linea[200000];
    FILE *archivo;
    printf("Abriendo archivo para lectura\n");
    archivo = fopen("2019_Matricula.csv", "r");
    if(archivo != NULL){
        while(fgets(linea, 200, archivo) != NULL){
            printf("%s", linea);
        }
        fclose(archivo);
    }else{
        printf("\nNo se ha podido abrir el archivo\n");
    }
}


