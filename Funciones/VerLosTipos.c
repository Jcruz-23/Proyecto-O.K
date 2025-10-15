#include "../Cabeceras/Prototipos.h"

int main(){
       // --- Lista Trayectoria ---
    NodoTrayectoria* Tr1 = malloc(sizeof(NodoTrayectoria));
    NodoTrayectoria* Tr2 = malloc(sizeof(NodoTrayectoria));
    NodoTrayectoria* Tr3 = malloc(sizeof(NodoTrayectoria));

    strcpy(Tr1->provincia, "Cordoba");
    strcpy(Tr1->sector, "Estatal");
    Tr1->id = 2023;
    for(int i=0; i<6; i++){
        Tr1->trayectoria.promovidos[i] = 80 + i;
        Tr1->trayectoria.nopromovidos[i] = 10 + i;
    }
    Tr1->trayectoria.secundariaEgresados = 200;
    Tr1->ant = NULL; Tr1->sig = Tr2;

    strcpy(Tr2->provincia, "Santa Fe");
    strcpy(Tr2->sector, "Privado");
    Tr2->id = 2023;
    for(int i=0; i<6; i++){
        Tr2->trayectoria.promovidos[i] = 90 + i;
        Tr2->trayectoria.nopromovidos[i] = 5 + i;
    }
    Tr2->trayectoria.secundariaEgresados = 150;
    Tr2->ant = Tr1; Tr2->sig = Tr3;

    strcpy(Tr3->provincia, "Mendoza");
    strcpy(Tr3->sector, "Estatal");
    Tr3->id = 2022;
    for(int i=0; i<6; i++){
        Tr3->trayectoria.promovidos[i] = 75 + i;
        Tr3->trayectoria.nopromovidos[i] = 12 + i;
    }
    Tr3->trayectoria.secundariaEgresados = 180;
    Tr3->ant = Tr2; Tr3->sig = NULL;

    NodoTrayectoria* Tr = Tr1; // cabeza de lista


    // --- Lista Matricula ---
    Matricula* M1 = malloc(sizeof(Matricula));
    Matricula* M2 = malloc(sizeof(Matricula));

    strcpy(M1->provincia, "Cordoba");
    strcpy(M1->sector, "Estatal");
    M1->id = 2023;
    for(int i=0; i<6; i++){
        M1->reg.repitentes[i] = 3 + i;
        M1->reg.matriculas[i] = 100 + i * 5;
    }
    M1->ant = NULL; M1->sig = M2;

    strcpy(M2->provincia, "Santa Fe");
    strcpy(M2->sector, "Privado");
    M2->id = 2023;
    for(int i=0; i<6; i++){
        M2->reg.repitentes[i] = 2 + i;
        M2->reg.matriculas[i] = 90 + i * 4;
    }
    M2->ant = M1; M2->sig = NULL;

    Matricula* Mtr = M1; // cabeza de lista


    // --- Probar función ---
    VerSector(Tr, Mtr);

    // Liberar memoria
    free(Tr1); free(Tr2); free(Tr3);
    free(M1); free(M2);

}

void VerSector(NodoTrayectoria* Tr, Matricula* Mtr){
    NodoTrayectoria* auxTr = Tr;
    Matricula* auxMtr = Mtr;
    char op = ' ';

    printf( "Que sector desea ver?\n"
            "a)Estatal\n"
            "b)Privado\n"
            "opcion: ");scanf(" %c", &op);
    
    switch(op){
        case 'A':
        case 'a': 
        printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

        while(auxTr != NULL){
            if(strcmp(auxTr->sector, "Estatal")==0){
                printf( "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
                        "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
                        auxTr->provincia, auxTr->sector, auxTr->trayectoria.promovidos[0],
                        auxTr->trayectoria.promovidos[1], auxTr->trayectoria.promovidos[2],
                        auxTr->trayectoria.promovidos[3], auxTr->trayectoria.promovidos[4],
                        auxTr->trayectoria.promovidos[5], auxTr->trayectoria.nopromovidos[0],
                        auxTr->trayectoria.nopromovidos[1], auxTr->trayectoria.nopromovidos[2],
                        auxTr->trayectoria.nopromovidos[3], auxTr->trayectoria.nopromovidos[4],
                        auxTr->trayectoria.nopromovidos[5],
                        auxTr->trayectoria.secundariaEgresados, auxTr->id);
            }
            auxTr = auxTr->sig;
        }
        printf("\n\n");
        printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
        while(auxMtr != NULL){
            if(strcmp(auxMtr->sector, "Estatal")==0){
                printf( "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
                        "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
                        auxMtr->provincia, auxMtr->sector, auxMtr->reg.repitentes[0],
                        auxMtr->reg.repitentes[1], auxMtr->reg.repitentes[2], auxMtr->reg.repitentes[3],
                        auxMtr->reg.repitentes[4], auxMtr->reg.repitentes[5], auxMtr->reg.matriculas[0],
                        auxMtr->reg.matriculas[1], auxMtr->reg.matriculas[2], auxMtr->reg.matriculas[3],
                        auxMtr->reg.matriculas[4], auxMtr->reg.matriculas[5], auxMtr->id);            
            }
            auxMtr = auxMtr->sig;
        }
        break;
        case 'B':
        case 'b':
        printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

        while(auxTr != NULL){
            if(strcmp(auxTr->sector, "Privado")==0){
                printf( "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
                        "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
                        auxTr->provincia, auxTr->sector, auxTr->trayectoria.promovidos[0],
                        auxTr->trayectoria.promovidos[1], auxTr->trayectoria.promovidos[2],
                        auxTr->trayectoria.promovidos[3], auxTr->trayectoria.promovidos[4],
                        auxTr->trayectoria.promovidos[5], auxTr->trayectoria.nopromovidos[0],
                        auxTr->trayectoria.nopromovidos[1], auxTr->trayectoria.nopromovidos[2],
                        auxTr->trayectoria.nopromovidos[3], auxTr->trayectoria.nopromovidos[4],
                        auxTr->trayectoria.nopromovidos[5],
                        auxTr->trayectoria.secundariaEgresados, auxTr->id);
            }
            auxTr = auxTr->sig;
        }
        printf("\n\n");
        printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
        while(auxMtr != NULL){
            if(strcmp(auxMtr->sector, "Privado")==0){
                printf( "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
                        "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
                        auxMtr->provincia, auxMtr->sector, auxMtr->reg.repitentes[0],
                        auxMtr->reg.repitentes[1], auxMtr->reg.repitentes[2], auxMtr->reg.repitentes[3],
                        auxMtr->reg.repitentes[4], auxMtr->reg.repitentes[5], auxMtr->reg.matriculas[0],
                        auxMtr->reg.matriculas[1], auxMtr->reg.matriculas[2], auxMtr->reg.matriculas[3],
                        auxMtr->reg.matriculas[4], auxMtr->reg.matriculas[5], auxMtr->id);            
            }
            auxMtr = auxMtr->sig;
            
        break;
        default: break;
        }
    }
}