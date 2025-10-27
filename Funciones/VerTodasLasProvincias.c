// #include "../Cabeceras/Prototipos.h"
// #include <stdlib.h>

// int main()
// {
//     NodoTrayectoria *RegistroTrayectoria = NULL;
//     NodoMatricula *matricula = NULL;
//     InsertarNodoTrayectoria(&RegistroTrayectoria);
//     LecturaNodoMatricula(&matricula);
//     VerTodasLasProvincias(matricula, RegistroTrayectoria);
//     //ImprimirLista(RegistroTrayectoria, Matricula);
//     return 0;
// }

// void InsertarMatricula(NodoMatricula **m, Matricula rM, int id,
//                                char provincia[20], char tipo[10])
// {
//     NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
//     nuevo->sig = NULL;
//     nuevo->id = id;
//     strcpy(nuevo->provincia, provincia);
//     strcpy(nuevo->sector, tipo);
//     nuevo->reg = rM;
//     if (*m == NULL)
//     {
//         *m = nuevo;
//     }
//     else
//     {
//         NodoMatricula *aux = *m;
//         while (aux->sig != NULL)
//         {
//             aux = aux->sig;
//         }
//         aux->sig = nuevo;
//     }
// }

// void ImprimirListaNodoMatricula(NodoMatricula *m)
// {
//     NodoMatricula *aux = m;
//     printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//            "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
//            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
//            "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
//     while (aux != NULL)
//     {
//         printf(
//             "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//             "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
//             aux->provincia, aux->sector, aux->reg.repitentes[0],
//             aux->reg.repitentes[1], aux->reg.repitentes[2], aux->reg.repitentes[3],
//             aux->reg.repitentes[4], aux->reg.repitentes[5], aux->reg.matricula[0],
//             aux->reg.matricula[1], aux->reg.matricula[2], aux->reg.matricula[3],
//             aux->reg.matricula[4], aux->reg.matricula[5], aux->id);
//         aux = aux->sig;
//     }
// }

// void LecturaNodoMatricula(NodoMatricula **matricula)
// {
//     NodoMatricula *temp = NULL;
//     int id = 0;
//     char provincia[31];
//     char tipo[10];
//     Matricula rM;
//     id = 2019;
//     SubirNodoMatricula("2019_NodoMatricula.csv", &temp, rM, id, provincia, tipo);
//     id = 2020;
//     SubirNodoMatricula("2020_NodoMatricula.csv", &temp, rM, id, provincia, tipo);
//     id = 2021;
//     SubirNodoMatricula("2021_NodoMatricula.csv", &temp, rM, id, provincia, tipo);

//     ClasificacionNodoMatricula(temp, matricula);
// }

// void SubirNodoMatricula(char *archivo, NodoMatricula **matricula,
//                     Matricula rM, int id, char provincia[20],
//                     char tipo[10])
// {
//     FILE *a;
//     char cabecera[300];

//     a = fopen(archivo, "r");
//     if (a == NULL)
//     {
//         printf("\nError al abrir archivo.csv\n");
//     }
//     else
//     {
//         fgets(cabecera, sizeof(cabecera), a);
//         while (fscanf(a, " %30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
//                       provincia, tipo, &rM.repitentes[0], &rM.repitentes[1],
//                       &rM.repitentes[2], &rM.repitentes[3], &rM.repitentes[4],
//                       &rM.repitentes[5], &rM.matricula[0], &rM.matricula[1],
//                       &rM.matricula[2], &rM.matricula[3], &rM.matricula[4],
//                       &rM.matricula[5]) == 14)
//         {
//             InsertarMatricula(matricula, rM, id, provincia, tipo);
//         }
//         fclose(a);
//     }
// }

// void ClasificacionNodoMatricula(NodoMatricula *temp, NodoMatricula **Matricula)
// {
//     NodoMatricula *tempo = temp;

//     while (tempo != NULL)
//     {

//         int bandera = 0;
//         NodoMatricula *aux = *Matricula;

//         while (aux != NULL && bandera == 0)
//         {
//             if (strcmp(tempo->provincia, aux->provincia) == 0 &&
//                 strcmp(tempo->sector, aux->sector) == 0 &&
//                 tempo->id == aux->id)
//             { // Buscar nodo en la lista nueva primero
//                 bandera = 1;
//             }
//             else
//             {
//                 aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
//             }
//         }
//         if (bandera)
//         { // Si encuentra coincidencias las suma a nuestro nodo
//             for (int i = 0; i < 6; i++)
//             {
//                 aux->reg.matricula[i] += tempo->reg.matricula[i];
//                 aux->reg.repitentes[i] += tempo->reg.repitentes[i];
//             }
//         }
//         else
//         { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
//           // nueva
//             NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
//             if (nuevo != NULL)
//             {
//                 nuevo->sig = NULL;
//                 strcpy(nuevo->provincia, tempo->provincia);
//                 strcpy(nuevo->sector, tempo->sector);
//                 nuevo->id = tempo->id;

//                 for (int i = 0; i < 6; i++)
//                 {
//                     nuevo->reg.matricula[i] = tempo->reg.matricula[i];
//                     nuevo->reg.repitentes[i] = tempo->reg.repitentes[i];
//                 }

//                 // Agregando a la lista nueva
//                 if (*Matricula == NULL)
//                 {
//                     *Matricula = nuevo;
//                 }
//                 else
//                 {
//                     NodoMatricula *aux2 = *Matricula;
//                     while (aux2->sig != NULL)
//                     {
//                         aux2 = aux2->sig;
//                     }
//                     aux2->sig = nuevo;
//                 }
//             }
//             else
//             {
//                 printf("\nNo se ha podido crear el nodo\n");
//             }
//         }
//         tempo = tempo->sig;
//     }
// }

// void InsertarNodoTrayectoria(NodoTrayectoria **RegistroTrayectoria)
// {
//     char provincia[25];
//     char sector[10];
//     NodoTrayectoria *temp = NULL;
//     Trayectoria trayectoria = {0};

//     for (int i = 0; i < 3; i++)
//     {

//         if (i == 0)
//         {
//             char basura[20000];
//             FILE *archivo;
//             printf("Abriendo archivo para lectura\n");
//             archivo = fopen("2019_Trayectoria.csv", "r");
//             if (archivo == NULL)
//             {
//                 printf("\nNo se pudo leer el archivo\n");
//             }
//             else
//             {
//                 fgets(basura, 20000, archivo);
//                 while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
//                 {
//                     NodoTrayectoria *nuevo =
//                         (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
//                     if (nuevo != NULL)
//                     {
//                         Carga(&nuevo, trayectoria, provincia, sector);
//                         nuevo->id = 2019;
//                         if (temp == NULL)
//                         {
//                             temp = nuevo;
//                         }
//                         else
//                         {
//                             NodoTrayectoria *aux = temp;
//                             while (aux->sig != NULL)
//                             {
//                                 aux = aux->sig;
//                             }
//                             aux->sig = nuevo;
//                         }
//                     }
//                     else
//                     {
//                         printf("Error al crear nuevo nodo\n");
//                     }
//                 }
//                 fclose(archivo);
//             }
//             printf("\nArchivo leido con exito\n");
//         }

//         if (i == 1)
//         {
//             char basura[20000];
//             FILE *archivo;
//             printf("Abriendo archivo para lectura\n");
//             archivo = fopen("2020_Trayectoria.csv", "r");
//             if (archivo == NULL)
//             {
//                 printf("\nNo se pudo leer el archivo\n");
//             }
//             else
//             {
//                 fgets(basura, 20000, archivo);
//                 while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
//                 {
//                     NodoTrayectoria *nuevo =
//                         (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
//                     if (nuevo != NULL)
//                     {
//                         Carga(&nuevo, trayectoria, provincia, sector);
//                         nuevo->id = 2020;
//                         if (temp == NULL)
//                         {
//                             temp = nuevo;
//                         }
//                         else
//                         {
//                             NodoTrayectoria *aux = temp;
//                             while (aux->sig != NULL)
//                             {
//                                 aux = aux->sig;
//                             }
                
//                             aux->sig = nuevo;
//                         }
//                     }
//                     else
//                     {
//                         printf("Error al crear nuevo nodo\n");
//                     }
//                 }
//                 fclose(archivo);
//             }
//             printf("\nArchivo leido con exito\n");
//         }
//         if (i == 2)
//         {
//             char basura[20000];
//             FILE *archivo;
//             printf("Abriendo archivo para lectura\n");
//             archivo = fopen("2021_Trayectoria.csv", "r");
//             if (archivo == NULL)
//             {
//                 printf("\nNo se pudo leer el archivo\n");
//             }
//             else
//             {
//                 fgets(basura, 20000, archivo);
//                 while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
//                 {
//                     NodoTrayectoria *nuevo =
//                         (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
//                     if (nuevo != NULL)
//                     {
//                         Carga(&nuevo, trayectoria, provincia, sector);
//                         nuevo->id = 2021;
//                         if (temp == NULL)
//                         {
//                             temp = nuevo;
//                         }
//                         else
//                         {
//                             NodoTrayectoria *aux = temp;
//                             while (aux->sig != NULL)
//                             {
//                                 aux = aux->sig;
//                             }
                           
//                             aux->sig = nuevo;
//                         }
//                     }
//                     else
//                     {
//                         printf("Error al crear nuevo nodo\n");
//                     }
//                 }
//                 fclose(archivo);
//             }
//             printf("\nArchivo leido con exito\n");
//         }
//     }

//     Clasificacion(temp, RegistroTrayectoria);
// }

// int Lectura(Trayectoria *trayectoria, FILE *archivo, char provincia[25],
//             char sector[10])
// {
//     int cant = 0;
//     cant = (fscanf(
//         archivo, " %25[^,],%10[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
//         provincia, sector, &trayectoria->promovidos[0],
//         &trayectoria->promovidos[1], &trayectoria->promovidos[2],
//         &trayectoria->promovidos[3], &trayectoria->promovidos[4],
//         &trayectoria->promovidos[5], &trayectoria->nopromovidos[0],
//         &trayectoria->nopromovidos[1], &trayectoria->nopromovidos[2],
//         &trayectoria->nopromovidos[3], &trayectoria->nopromovidos[4],
//         &trayectoria->nopromovidos[5], &trayectoria->secundariaEgresados));
//     return cant;
// }

// void Carga(NodoTrayectoria **nuevo, Trayectoria trayectoria, char provincia[25],
//            char sector[10])
// {

    
//     (*nuevo)->sig = NULL;
//     strcpy((*nuevo)->provincia, provincia);
//     strcpy((*nuevo)->sector, sector);
//     for (int i = 0; i < 6; i++)
//     {
//         (*nuevo)->trayectoria.promovidos[i] = trayectoria.promovidos[i];
//         (*nuevo)->trayectoria.nopromovidos[i] = trayectoria.nopromovidos[i];
//     }
//     (*nuevo)->trayectoria.secundariaEgresados = trayectoria.secundariaEgresados;
// }

// void Clasificacion(NodoTrayectoria *temp,
//                    NodoTrayectoria **RegistroTrayectoria)
// {
//     NodoTrayectoria *tempo = temp;

//     while (tempo != NULL)
//     {

//         int bandera = 0;
//         NodoTrayectoria *aux = *RegistroTrayectoria;

//         while (aux != NULL && bandera == 0)
//         {
//             if (strcmp(tempo->provincia, aux->provincia) == 0 &&
//                 strcmp(tempo->sector, aux->sector) == 0 &&
//                 tempo->id == aux->id)
//             { // Buscar nodo en la lista nueva primero
//                 bandera = 1;
//             }
//             else
//             {
//                 aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
//             }
//         }
//         if (bandera)
//         { // Si encuentra coincidencias las suma a nuestro nodo
//             for (int i = 0; i < 6; i++)
//             {
//                 aux->trayectoria.nopromovidos[i] += tempo->trayectoria.nopromovidos[i];
//                 aux->trayectoria.promovidos[i] += tempo->trayectoria.promovidos[i];
//             }
//             aux->trayectoria.secundariaEgresados +=
//                 tempo->trayectoria.secundariaEgresados;
//         }
//         else
//         { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
//           // nueva
//             NodoTrayectoria *nuevo =
//                 (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
//             if (nuevo != NULL)
//             {
               
//                 nuevo->sig = NULL;
//                 strcpy(nuevo->provincia, tempo->provincia);
//                 strcpy(nuevo->sector, tempo->sector);
//                 nuevo->id = tempo->id;

//                 for (int i = 0; i < 6; i++)
//                 {
//                     nuevo->trayectoria.nopromovidos[i] =
//                         tempo->trayectoria.nopromovidos[i];
//                     nuevo->trayectoria.promovidos[i] = tempo->trayectoria.promovidos[i];
//                 }
//                 nuevo->trayectoria.secundariaEgresados =
//                     tempo->trayectoria.secundariaEgresados;
//                 // Agregando a la lista nueva
//                 if (*RegistroTrayectoria == NULL)
//                 {
//                     *RegistroTrayectoria = nuevo;
//                 }
//                 else
//                 {
//                     NodoTrayectoria *aux2 = *RegistroTrayectoria;
//                     while (aux2->sig != NULL)
//                     {
//                         aux2 = aux2->sig;
//                     }
                   
//                     aux2->sig = nuevo;
//                 }
//             }
//             else
//             {
//                 printf("\nNo se ha podido crear el nodo\n");
//             }
//         }
//         tempo = tempo->sig;
//     }
// }

// void ImprimirLista(NodoTrayectoria *trayectoria, NodoMatricula *matricula)
// {
//     NodoMatricula *aux2 = matricula;
//     NodoTrayectoria *aux = trayectoria;
//     printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//            "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
//            "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
//            "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");
//     while (aux != NULL)
//     {
//         printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//                "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
//                aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
//                aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
//                aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
//                aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
//                aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
//                aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
//                aux->trayectoria.nopromovidos[5],
//                aux->trayectoria.secundariaEgresados, aux->id);
//         aux = aux->sig;
//     }
//     aux = trayectoria;

//     FILE *archivo = fopen("Registro Completo.txt", "w");
//     if (archivo == NULL)
//     {
//         printf("Error al abrir archivo de salida\n");
//         return;
//     }

//     fprintf(archivo,
//             "%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//             "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
//             "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
//             "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

//     while (aux != NULL)
//     {
//         fprintf(archivo,
//                 "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//                 "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
//                 aux->provincia, aux->sector, aux->trayectoria.promovidos[0],
//                 aux->trayectoria.promovidos[1], aux->trayectoria.promovidos[2],
//                 aux->trayectoria.promovidos[3], aux->trayectoria.promovidos[4],
//                 aux->trayectoria.promovidos[5], aux->trayectoria.nopromovidos[0],
//                 aux->trayectoria.nopromovidos[1], aux->trayectoria.nopromovidos[2],
//                 aux->trayectoria.nopromovidos[3], aux->trayectoria.nopromovidos[4],
//                 aux->trayectoria.nopromovidos[5],
//                 aux->trayectoria.secundariaEgresados, aux->id);
//         aux = aux->sig;
//     }

//     fprintf(archivo, "\n\n%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
//             "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
//             "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
//     while (aux2 != NULL)
//     {
//         fprintf(archivo,
//                 "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
//                 aux2->provincia, aux2->sector, aux2->reg.repitentes[0], aux2->reg.repitentes[1], aux2->reg.repitentes[2],
//                 aux2->reg.repitentes[3], aux2->reg.repitentes[4], aux2->reg.repitentes[5],
//                 aux2->reg.matricula[0], aux2->reg.matricula[1], aux2->reg.matricula[2],
//                 aux2->reg.matricula[3], aux2->reg.matricula[4], aux2->reg.matricula[5], aux2->id);
//         aux2 = aux2->sig;
//     }
//     fclose(archivo);
//     printf("\n\n");

//     aux2 = matricula;

//     printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//            "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
//            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
//            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
//     while (aux2 != NULL)
//     {
//         printf(
//             "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//             "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
//             aux2->provincia, aux2->sector, aux2->reg.repitentes[0], aux2->reg.repitentes[1], aux2->reg.repitentes[2],
//             aux2->reg.repitentes[3], aux2->reg.repitentes[4], aux2->reg.repitentes[5],
//             aux2->reg.matricula[0], aux2->reg.matricula[1], aux2->reg.matricula[2],
//             aux2->reg.matricula[3], aux2->reg.matricula[4], aux2->reg.matricula[5], aux2->id);
//         aux2 = aux2->sig;
//     }
// }



// void VerTodasLasProvincias(NodoMatricula *matricula, NodoTrayectoria *trayectoria) {
//     // --- VALIDACIÓN INICIAL ---
//     if (matricula == NULL && trayectoria == NULL) {
//         printf("No hay datos disponibles en ninguna lista.\n");
//         return;
//     }

//     // --- PEDIR PROVINCIA ---
//     char provinciaBuscada[30];
//     printf("Ingrese la provincia que desea visualizar: ");
//     fgets(provinciaBuscada,sizeof(provinciaBuscada),stdin);
//     provinciaBuscada[strcspn(provinciaBuscada,"\n")]='\0';

//     int encontradoM = 0, encontradoT = 0;

//     // --- TABLA DE TRAYECTORIAS ---
//     printf("\n================ TRAYECTORIAS DE %s ================\n", provinciaBuscada);
//     printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//            "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
//            "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
//            "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Año");

//     NodoTrayectoria *auxT = trayectoria;
//     while (auxT != NULL) {
//         if (strcmp(auxT->provincia, provinciaBuscada) == 0) {
//             printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//                    "%-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
//                    auxT->provincia, auxT->sector,
//                    auxT->trayectoria.promovidos[0], auxT->trayectoria.promovidos[1],
//                    auxT->trayectoria.promovidos[2], auxT->trayectoria.promovidos[3],
//                    auxT->trayectoria.promovidos[4], auxT->trayectoria.promovidos[5],
//                    auxT->trayectoria.nopromovidos[0], auxT->trayectoria.nopromovidos[1],
//                    auxT->trayectoria.nopromovidos[2], auxT->trayectoria.nopromovidos[3],
//                    auxT->trayectoria.nopromovidos[4], auxT->trayectoria.nopromovidos[5],
//                    auxT->trayectoria.secundariaEgresados, auxT->id);
//             encontradoT = 1;
//         }
//         auxT = auxT->sig;
//     }
//     if (!encontradoT)
//         printf("No se encontraron registros de trayectoria para %s.\n", provinciaBuscada);

//     // --- TABLA DE MATRÍCULAS ---
//     printf("\n================ MATRÍCULAS DE %s ================\n", provinciaBuscada);
//     printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
//            "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
//            "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP", "6_REP",
//            "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Año");

//     NodoMatricula *auxM = matricula;
//     while (auxM != NULL) {
//         if (strcmp(auxM->provincia, provinciaBuscada) == 0) {
//             printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
//                    "%-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
//                    auxM->provincia,
//                    auxM->sector,
//                    auxM->reg.repitentes[0], auxM->reg.repitentes[1],
//                    auxM->reg.repitentes[2], auxM->reg.repitentes[3],
//                    auxM->reg.repitentes[4], auxM->reg.repitentes[5],
//                    auxM->reg.matricula[0], auxM->reg.matricula[1],
//                    auxM->reg.matricula[2], auxM->reg.matricula[3],
//                    auxM->reg.matricula[4], auxM->reg.matricula[5],
//                    auxM->id);
//             encontradoM = 1;
//         }
//         auxM = auxM->sig;
//     }
//     if (!encontradoM)
//         printf("No se encontraron registros de matrícula para %s.\n", provinciaBuscada);

//     printf("\n========================================================\n");
// }

