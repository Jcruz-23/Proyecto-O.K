#include "Prototipos.h"

void Menu(NodoMatricula *mat, NodoTrayectoria *tr)
{
  char opcion = '\0';
  NodoMatricula *tempM = NULL;
  NodoTrayectoria *tempT = NULL;
  int cont = 0;

  do
  {
    printf("\n-------------- MENU --------------\n"
           " a. Mostrar lista\n"
           " b. Mostrar datos de todas las provincias\n"
           " c. Mostrar datos de educacion publica y privada\n"
           " d. Buscar por provincia\n"
           " e. Buscar por anio\n"
           " f. Buscar por tipo\n"
           " s. Salir");
    printf("\nIngrese la opcion que desea realizar:\n");
    scanf(" %c", &opcion);

    switch (opcion)
    {
    case 'A':
    case 'a':
      ImprimirLista(tr, mat);
      break;
    case 'B':
    case 'b':
      VerTodasLasProvincias(mat, tr);
      break;
    case 'C':
    case 'c':
      VerSector(tr, mat);
      break;
    case 'D':
    case 'd':
      BuscarPorProvincia(mat, tr, &tempM, &tempT, &cont);
      break;
    case 'E':
    case 'e':
      BuscarPorAnio(mat, tr, &tempM, &tempT, &cont);
      break;
    case 'F':
    case 'f':
      BuscarPorTipo(mat, tr, &tempM, &tempT, &cont);
      break;
    case 'S':
    case 's':
      printf("Saliendo del programa...\n");
      break;
    default:
      printf("Opcion invalida.\n");
      break;
    }
  } while (opcion != 's' && opcion != 'S');
}

// Implementación CORREGIDA de VerTodasLasProvincias
void RegistrarProvincias(NodoMatricula *listaMatriculas, NodoTrayectoria *listaTrayectorias)
{
  FILE *archivo = fopen("REGISTRO_PROVINCIAS.txt","w");
  NodoMatricula *auxM = listaMatriculas; // Usamos el NodoMatricula

  // Recorremos todas las provincias que existan en la listaMatriculas
  while (auxM != NULL)
  {
    char provinciaActual[30];
    strcpy(provinciaActual, auxM->provincia);

    fprintf(archivo,"                  MATRICULAS %s\n", provinciaActual);
    fprintf(archivo,"********************************************************************\n");

    int encontradoM = 0;
    int encontradoT = 0;

    NodoMatricula *m = listaMatriculas; // Recorremos desde el inicio para ver todos los años/sectores
    NodoTrayectoria *t = listaTrayectorias;

    // Bucle para MATRÍCULA
    while (m != NULL)
    {
      if (strcmp(m->provincia, provinciaActual) == 0)
      {
        fprintf(archivo,"\n  Registro MATRICULA AÑO %d (Sector: %s)\n", m->id, m->sector);
        for (int i = 0; i < 6; i++)
        {
          fprintf(archivo,"  Año escolaridad %d: Matriculas=%d, Repitentes=%d\n",
                 i + 1, m->reg.matricula[i], m->reg.repitentes[i]);
        }
        encontradoM = 1;
      }
      m = m->sig;
    }

    if (!encontradoM)
      fprintf(archivo,"  No se encontraron registros de matrícula para %s.\n", provinciaActual);

    // Bucle para TRAYECTORIA
    fprintf(archivo,"\n********************************************************************\n");
    fprintf(archivo,"                  TRAYECTORIAS %s\n", provinciaActual);
    fprintf(archivo,"********************************************************************\n");
    while (t != NULL)
    {
      if (strcmp(t->provincia, provinciaActual) == 0)
      {
        fprintf(archivo,"\n  Registro TRAYECTORIA AÑO %d (Sector: %s)\n", t->id, t->sector);
        for (int i = 0; i < 6; i++)
        {
          // Nota: La lógica de tu impresión original mezclaba t->trayectoria.secundariaEgresados
          // con el bucle de 6 años, y usaba nopromovidos para "sobreEdad". Muestro los 6 grados.
          fprintf(archivo,"  Año escolaridad %d: Promovidos=%d, No Promovidos=%d\n",
                 i + 1, t->trayectoria.promovidos[i], t->trayectoria.nopromovidos[i]);
        }
        fprintf(archivo,"  Total Egresados Secundaria: %d\n", t->trayectoria.secundariaEgresados);
        encontradoT = 1;
      }
      t = t->sig;
    }

    if (!encontradoT)
      fprintf(archivo,"  No se encontraron registros de trayectoria para %s.\n", provinciaActual);

    fprintf(archivo,"\n********************************************************************\n");

    // Bucle para avanzar a la siguiente PROVINCIA ÚNICA (la lógica del bucle sigue siendo correcta)
    char provinciaAnterior[30];
    strcpy(provinciaAnterior, provinciaActual);
    while (auxM != NULL && strcmp(auxM->provincia, provinciaAnterior) == 0)
    {
      auxM = auxM->sig;
    }
  }
  fclose(archivo);
}
void VerTodasLasProvincias(NodoMatricula *listaMatriculas, NodoTrayectoria *listaTrayectorias)
{
  RegistrarProvincias(listaMatriculas ,listaTrayectorias);//
  // ⚠️ ATENCIÓN: El prototipo de la función tiene Nodos, no solo la estructura Matricula.
  // Usaremos los punteros que recibimos (listaMatriculas, listaTrayectorias).

  if (listaMatriculas == NULL && listaTrayectorias == NULL)
  {
    printf("No hay datos disponibles.\n");
    return;
  }

  NodoMatricula *auxM = listaMatriculas; // Usamos el NodoMatricula

  // Recorremos todas las provincias que existan en la listaMatriculas
  while (auxM != NULL)
  {
    char provinciaActual[30];
    strcpy(provinciaActual, auxM->provincia);

    printf("                  MATRICULAS %s\n", provinciaActual);
    printf("********************************************************************\n");

    int encontradoM = 0;
    int encontradoT = 0;

    NodoMatricula *m = listaMatriculas; // Recorremos desde el inicio para ver todos los años/sectores
    NodoTrayectoria *t = listaTrayectorias;

    // Bucle para MATRÍCULA
    while (m != NULL)
    {
      if (strcmp(m->provincia, provinciaActual) == 0)
      {
        printf("\n  Registro MATRICULA AÑO %d (Sector: %s)\n", m->id, m->sector);
        for (int i = 0; i < 6; i++)
        {
          printf("  Año escolaridad %d: Matriculas=%d, Repitentes=%d\n",
                 i + 1, m->reg.matricula[i], m->reg.repitentes[i]);
        }
        encontradoM = 1;
      }
      m = m->sig;
    }

    if (!encontradoM)
      printf("  No se encontraron registros de matrícula para %s.\n", provinciaActual);

    // Bucle para TRAYECTORIA
    printf("\n********************************************************************\n");
    printf("                  TRAYECTORIAS %s\n", provinciaActual);
    printf("********************************************************************\n");
    while (t != NULL)
    {
      if (strcmp(t->provincia, provinciaActual) == 0)
      {
        printf("\n  Registro TRAYECTORIA AÑO %d (Sector: %s)\n", t->id, t->sector);
        for (int i = 0; i < 6; i++)
        {
          // Nota: La lógica de tu impresión original mezclaba t->trayectoria.secundariaEgresados
          // con el bucle de 6 años, y usaba nopromovidos para "sobreEdad". Muestro los 6 grados.
          printf("  Año escolaridad %d: Promovidos=%d, No Promovidos=%d\n",
                 i + 1, t->trayectoria.promovidos[i], t->trayectoria.nopromovidos[i]);
        }
        printf("  Total Egresados Secundaria: %d\n", t->trayectoria.secundariaEgresados);
        encontradoT = 1;
      }
      t = t->sig;
    }

    if (!encontradoT)
      printf("  No se encontraron registros de trayectoria para %s.\n", provinciaActual);

    printf("\n********************************************************************\n");

    // Bucle para avanzar a la siguiente PROVINCIA ÚNICA (la lógica del bucle sigue siendo correcta)
    char provinciaAnterior[30];
    strcpy(provinciaAnterior, provinciaActual);
    while (auxM != NULL && strcmp(auxM->provincia, provinciaAnterior) == 0)
    {
      auxM = auxM->sig;
    }
  }
}

void InsertarMatricula(NodoMatricula **m, Matricula rM, int id,
                       char provincia[20], char tipo[10])
{
  NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
  nuevo->sig = NULL;

  nuevo->id = id;
  strcpy(nuevo->provincia, provincia);
  strcpy(nuevo->sector, tipo);
  nuevo->reg = rM;
  if (*m == NULL)
  {
    *m = nuevo;
  }
  else
  {
    NodoMatricula *aux = *m;
    while (aux->sig != NULL)
    {
      aux = aux->sig;
    }
    aux->sig = nuevo;
  }
}

void ImprimirListaNodoMatricula(NodoMatricula *m)
{
  NodoMatricula *aux = m;
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
  while (aux != NULL)
  {
    printf(
        "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
        "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
        aux->provincia, aux->sector, aux->reg.repitentes[0],
        aux->reg.repitentes[1], aux->reg.repitentes[2], aux->reg.repitentes[3],
        aux->reg.repitentes[4], aux->reg.repitentes[5], aux->reg.matricula[0],
        aux->reg.matricula[1], aux->reg.matricula[2], aux->reg.matricula[3],
        aux->reg.matricula[4], aux->reg.matricula[5], aux->id);
    aux = aux->sig;
  }
}

void LecturaMatricula(NodoMatricula **matricula)
{
  NodoMatricula *temp = NULL;
  int id = 0;
  char provincia[31];
  char tipo[10];
  Matricula rM = {0};
  id = 2019;
  SubirNodoMatricula("Otros/2019_Matricula.csv", &temp, rM, id, provincia, tipo);
  id = 2020;
  SubirNodoMatricula("Otros/2020_Matricula.csv", &temp, rM, id, provincia, tipo);
  id = 2021;
  SubirNodoMatricula("Otros/2021_Matricula.csv", &temp, rM, id, provincia, tipo);

  ClasificacionMatricula(temp, matricula);
}

void SubirNodoMatricula(char *archivo, NodoMatricula **matricula,
                        Matricula rM, int id, char provincia[20],
                        char tipo[10])
{
  FILE *a;
  char cabecera[300];

  a = fopen(archivo, "r");
  if (a == NULL)
  {
    printf("\nError al abrir archivo.csv\n");
  }
  else
  {
    fgets(cabecera, sizeof(cabecera), a);
    while (fscanf(a, " %30[^,],%9[^,],%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d",
                  provincia, tipo, &rM.repitentes[0], &rM.repitentes[1],
                  &rM.repitentes[2], &rM.repitentes[3], &rM.repitentes[4],
                  &rM.repitentes[5], &rM.matricula[0], &rM.matricula[1],
                  &rM.matricula[2], &rM.matricula[3], &rM.matricula[4],
                  &rM.matricula[5]) == 14)
    {
      InsertarMatricula(matricula, rM, id, provincia, tipo);
    }
    fclose(a);
  }
}

void ClasificacionMatricula(NodoMatricula *temp, NodoMatricula **matricula)
{
  NodoMatricula *tempo = temp;

  while (tempo != NULL)
  {

    int bandera = 0;
    NodoMatricula *aux = *matricula;

    while (aux != NULL && bandera == 0)
    {
      if (strcmp(tempo->provincia, aux->provincia) == 0 &&
          strcmp(tempo->sector, aux->sector) == 0 &&
          tempo->id == aux->id)
      { // Buscar nodo en la lista nueva primero
        bandera = 1;
      }
      else
      {
        aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
      }
    }
    if (bandera)
    { // Si encuentra coincidencias las suma a nuestro nodo
      for (int i = 0; i < 6; i++)
      {
        aux->reg.matricula[i] += tempo->reg.matricula[i];
        aux->reg.repitentes[i] += tempo->reg.repitentes[i];
      }
    }
    else
    { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
      // nueva
      NodoMatricula *nuevo = (NodoMatricula *)malloc(sizeof(NodoMatricula));
      if (nuevo != NULL)
      {

        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->sector, tempo->sector);
        nuevo->id = tempo->id;

        for (int i = 0; i < 6; i++)
        {
          nuevo->reg.matricula[i] = tempo->reg.matricula[i];
          nuevo->reg.repitentes[i] = tempo->reg.repitentes[i];
        }

        // Agregando a la lista nueva
        if (*matricula == NULL)
        {
          *matricula = nuevo;
        }
        else
        {
          NodoMatricula *aux2 = *matricula;
          while (aux2->sig != NULL)
          {
            aux2 = aux2->sig;
          }

          aux2->sig = nuevo;
        }
      }
      else
      {
        printf("\nNo se ha podido crear el nodo\n");
      }
    }
    tempo = tempo->sig;
  }
}

void InsertarNodoTrayectoria(NodoTrayectoria **RegistroTrayectoria)
{
  char provincia[25];
  char sector[10];
  NodoTrayectoria *temp = NULL;
  Trayectoria trayectoria = {0};

  for (int i = 0; i < 3; i++)
  {

    if (i == 0)
    {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("Otros/2019_Trayectoria.csv", "r");
      if (archivo == NULL)
      {
        printf("\nNo se pudo leer el archivo\n");
      }
      else
      {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
        {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL)
          {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2019;
            if (temp == NULL)
            {
              temp = nuevo;
            }
            else
            {
              NodoTrayectoria *aux = temp;
              while (aux->sig != NULL)
              {
                aux = aux->sig;
              }

              aux->sig = nuevo;
            }
          }
          else
          {
            printf("Error al crear nuevo nodo\n");
          }
        }
        fclose(archivo);
      }
      printf("\nArchivo leido con exito\n");
    }

    if (i == 1)
    {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("Otros/2020_Trayectoria.csv", "r");
      if (archivo == NULL)
      {
        printf("\nNo se pudo leer el archivo\n");
      }
      else
      {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
        {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL)
          {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2020;
            if (temp == NULL)
            {
              temp = nuevo;
            }
            else
            {
              NodoTrayectoria *aux = temp;
              while (aux->sig != NULL)
              {
                aux = aux->sig;
              }

              aux->sig = nuevo;
            }
          }
          else
          {
            printf("Error al crear nuevo nodo\n");
          }
        }
        fclose(archivo);
      }
      printf("\nArchivo leido con exito\n");
    }
    if (i == 2)
    {
      char basura[20000];
      FILE *archivo;
      printf("Abriendo archivo para lectura\n");
      archivo = fopen("Otros/2021_Trayectoria.csv", "r");
      if (archivo == NULL)
      {
        printf("\nNo se pudo leer el archivo\n");
      }
      else
      {
        fgets(basura, 20000, archivo);
        while ((Lectura(&trayectoria, archivo, provincia, sector)) == 15)
        {
          NodoTrayectoria *nuevo =
              (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
          if (nuevo != NULL)
          {
            Carga(&nuevo, trayectoria, provincia, sector);
            nuevo->id = 2021;
            if (temp == NULL)
            {
              temp = nuevo;
            }
            else
            {
              NodoTrayectoria *aux = temp;
              while (aux->sig != NULL)
              {
                aux = aux->sig;
              }

              aux->sig = nuevo;
            }
          }
          else
          {
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
            char sector[10])
{
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
           char sector[10])
{

  (*nuevo)->sig = NULL;
  strcpy((*nuevo)->provincia, provincia);
  strcpy((*nuevo)->sector, sector);
  for (int i = 0; i < 6; i++)
  {
    (*nuevo)->trayectoria.promovidos[i] = trayectoria.promovidos[i];
    (*nuevo)->trayectoria.nopromovidos[i] = trayectoria.nopromovidos[i];
  }
  (*nuevo)->trayectoria.secundariaEgresados = trayectoria.secundariaEgresados;
}

void Clasificacion(NodoTrayectoria *temp,
                   NodoTrayectoria **RegistroTrayectoria)
{
  NodoTrayectoria *tempo = temp;

  while (tempo != NULL)
  {

    int bandera = 0;
    NodoTrayectoria *aux = *RegistroTrayectoria;

    while (aux != NULL && bandera == 0)
    {
      if (strcmp(tempo->provincia, aux->provincia) == 0 &&
          strcmp(tempo->sector, aux->sector) == 0 &&
          tempo->id == aux->id)
      { // Buscar nodo en la lista nueva primero
        bandera = 1;
      }
      else
      {
        aux = aux->sig; // Avanza hasta encontrar el nodo con las coincidencias
      }
    }
    if (bandera)
    { // Si encuentra coincidencias las suma a nuestro nodo
      for (int i = 0; i < 6; i++)
      {
        aux->trayectoria.nopromovidos[i] += tempo->trayectoria.nopromovidos[i];
        aux->trayectoria.promovidos[i] += tempo->trayectoria.promovidos[i];
      }
      aux->trayectoria.secundariaEgresados +=
          tempo->trayectoria.secundariaEgresados;
    }
    else
    { // Si no las encuentra crea un nuevo nodo y lo agrega a la lista
      // nueva
      NodoTrayectoria *nuevo =
          (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
      if (nuevo != NULL)
      {

        nuevo->sig = NULL;
        strcpy(nuevo->provincia, tempo->provincia);
        strcpy(nuevo->sector, tempo->sector);
        nuevo->id = tempo->id;

        for (int i = 0; i < 6; i++)
        {
          nuevo->trayectoria.nopromovidos[i] =
              tempo->trayectoria.nopromovidos[i];
          nuevo->trayectoria.promovidos[i] = tempo->trayectoria.promovidos[i];
        }
        nuevo->trayectoria.secundariaEgresados =
            tempo->trayectoria.secundariaEgresados;
        // Agregando a la lista nueva
        if (*RegistroTrayectoria == NULL)
        {
          *RegistroTrayectoria = nuevo;
        }
        else
        {
          NodoTrayectoria *aux2 = *RegistroTrayectoria;
          while (aux2->sig != NULL)
          {
            aux2 = aux2->sig;
          }

          aux2->sig = nuevo;
        }
      }
      else
      {
        printf("\nNo se ha podido crear el nodo\n");
      }
    }
    tempo = tempo->sig;
  }
}

void ImprimirLista(NodoTrayectoria *trayectoria, NodoMatricula *matricula)
{
  NodoMatricula *aux2 = matricula;
  NodoTrayectoria *aux = trayectoria;
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");
  while (aux != NULL)
  {
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

  FILE *archivo = fopen("Cabeceras/Registro Completo.txt", "w");
  if (archivo == NULL)
  {
    printf("Error al abrir archivo de salida\n");
    return;
  }

  fprintf(archivo,
          "%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
          "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
          "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
          "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

  while (aux != NULL)
  {
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
  while (aux2 != NULL)
  {
    fprintf(archivo,
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matricula[0],
            aux2->reg.matricula[1], aux2->reg.matricula[2],
            aux2->reg.matricula[3], aux2->reg.matricula[4],
            aux2->reg.matricula[5], aux2->id);
    aux2 = aux2->sig;
  }
  fclose(archivo);
  printf("\n\n");

  aux2 = matricula;

  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");
  while (aux2 != NULL)
  {
    printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
           "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
           aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
           aux2->reg.repitentes[1], aux2->reg.repitentes[2],
           aux2->reg.repitentes[3], aux2->reg.repitentes[4],
           aux2->reg.repitentes[5], aux2->reg.matricula[0],
           aux2->reg.matricula[1], aux2->reg.matricula[2],
           aux2->reg.matricula[3], aux2->reg.matricula[4],
           aux2->reg.matricula[5], aux2->id);
    aux2 = aux2->sig;
  }
}

void BuscarPorProvincia(NodoMatricula *matricula,
                        NodoTrayectoria *RegistroTrayectoria, NodoMatricula **tempM,
                        NodoTrayectoria **tempT, int *cont)
{
  if (*(cont) < 3)
  { // Lo hara hasta que el contador sea 3, esto es para controlar que luego de pasar por los 3 filtros no continue preguntando
    (*cont)++;
    char provincia[25];
    char provincia_normalizada[25];
    char opcion = ' ';
    int bandera = 0;

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria; // Inicializamos una lista auxiliar que determinara cual lista filtramos, si una que ya haya sido filtrada o si filtramos la lista original
    NodoMatricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : matricula; // Es una lista por cada registro

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    NodoMatricula *nuevo_tempM = NULL;
    NodoMatricula *lista_tempM = NULL;

    printf("\nIngrese el nombre de la provincia que desee buscar: ");
    scanf(" %24[^\n]", provincia);

    int j = 0;
    for (int i = 0; provincia[i] != '\0' && j < 24; i++)
    {
      if (provincia[i] != ' ' && provincia[i] != '\t')
      {
        provincia_normalizada[j] = tolower((unsigned char)provincia[i]); // Deberia permitirnos escribir el nombre de la provincia sin mayus ni tilde y encontrarlo igual (no lo hace con el tilde)
        j++;
      }
    }
    provincia_normalizada[j] = '\0';

    printf("\nLos datos encontrados son:\n");
    printf("\n\n");
    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    NodoTrayectoria *aux = lista_a_filtrar_T;

    while (aux != NULL)
    {
      char aux_provincia_normalizada[25];

      int j = 0;
      for (int i = 0; aux->provincia[i] != '\0' && j < 24; i++)
      {
        if (aux->provincia[i] != ' ' && aux->provincia[i] != '\t')
        {
          aux_provincia_normalizada[j] =
              tolower((unsigned char)aux->provincia[i]); // Deberia permitirnos escribir el nombre de la provincia sin mayus ni tilde y encontrarlo igual (no lo hace con el tilde)
          j++;
        }
      }
      aux_provincia_normalizada[j] = '\0';

      if (strcmp(aux_provincia_normalizada, provincia_normalizada) == 0)
      { // Compara si la provincia ingresada es igual a la provincia de algun nodo, si lo es agrega el nodo completo a la nueva lista filtrada
        bandera = 1;
        printf(
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
        NodoTrayectoria *nuevo =
            (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
        if (nuevo != NULL)
        {
          nuevo->sig = NULL;
          strcpy(nuevo->provincia, aux->provincia);
          strcpy(nuevo->sector, aux->sector);
          nuevo->id = aux->id;
          for (int i = 0; i < 6; i++)
          {
            nuevo->trayectoria.nopromovidos[i] =
                aux->trayectoria.nopromovidos[i];
            nuevo->trayectoria.promovidos[i] = aux->trayectoria.promovidos[i];
          }
          nuevo->trayectoria.secundariaEgresados =
              aux->trayectoria.secundariaEgresados;

          if (nuevo_tempT == NULL)
          {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          }
          else
          {
            lista_tempT->sig = nuevo;
            lista_tempT = nuevo;
          }
        }
        else
        {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux = aux->sig;
    }

    *tempT = nuevo_tempT;

    if (bandera == 0)
    {
      printf("\nNo se ha encontrado trayectoria en la provincia ingresada\n"); // Si no se encontraron coincidencias
    }
    bandera = 0;
    printf("\n\n");
    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    NodoMatricula *aux2 = lista_a_filtrar_M;

    while (aux2 != NULL)
    {
      char aux2_provincia_normalizada[25]; // Hace la misma comparacion con la trayectoria
      {
        int j = 0;
        for (int i = 0; aux2->provincia[i] != '\0' && j < 24; i++)
        {
          if (aux2->provincia[i] != ' ' && aux2->provincia[i] != '\t')
          {
            aux2_provincia_normalizada[j] =
                tolower((unsigned char)aux2->provincia[i]);
            j++;
          }
        }
        aux2_provincia_normalizada[j] = '\0';
      }

      if (strcmp(aux2_provincia_normalizada, provincia_normalizada) == 0)
      {
        bandera = 1;
        printf(
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matricula[0],
            aux2->reg.matricula[1], aux2->reg.matricula[2],
            aux2->reg.matricula[3], aux2->reg.matricula[4],
            aux2->reg.matricula[5], aux2->id);
        NodoMatricula *nuevo2 = (NodoMatricula *)malloc(sizeof(NodoMatricula));
        if (nuevo2 != NULL)
        {
          nuevo2->sig = NULL;
          strcpy(nuevo2->provincia, aux2->provincia);
          strcpy(nuevo2->sector, aux2->sector);
          nuevo2->id = aux2->id;
          for (int i = 0; i < 6; i++)
          {
            nuevo2->reg.matricula[i] = aux2->reg.matricula[i];
            nuevo2->reg.repitentes[i] = aux2->reg.repitentes[i];
          }

          if (nuevo_tempM == NULL)
          {
            nuevo_tempM = nuevo2;
            lista_tempM = nuevo2;
          }
          else
          {
            lista_tempM->sig = nuevo2;
            lista_tempM = nuevo2;
          }
        }
        else
        {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux2 = aux2->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0)
    {
      printf("\nNo se han encontrado datos de la provincia ingresada\n");
    }
    bandera = 0;

    if ((*cont) < 3)
    { // Si el contador aun es menor a 3 consulta si la persona quiere agregar un filtro mas
      printf("\nDesea agregar otro filtro\?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S')
      {
        opcion = ' ';
        printf("\nLos filtros que puede agregar son:\n");
        printf("a) Buscar por año\n");
        printf("b) Buscar por sector\n");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'a':
          BuscarPorAnio(matricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        case 'b':
          BuscarPorTipo(matricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nNo ha ingresado una opcion valida\n");
        }
      }
      else
      {

        while (*tempM != NULL)
        {
          NodoMatricula *proxM = (*tempM)->sig;
          free(*tempM);
          *tempM = proxM;
        }

        while (*tempT != NULL)
        {
          NodoTrayectoria *proxT = (*tempT)->sig;
          free(*tempT);
          *tempT = proxT;
        }
        (*cont) = 0;
      }
    }
  }
  if ((*cont) > 3)
  {
    cont = 0;
  }
}

void BuscarPorAnio(NodoMatricula *Matricula,
                   NodoTrayectoria *RegistroTrayectoria, NodoMatricula **tempM,
                   NodoTrayectoria **tempT, int *cont)
{
  if (*(cont) < 3)
  {
    (*cont)++;
    int anio = 0, bandera = 0;
    char opcion = ' ';

    printf("\nIngrese el año que desee buscar: ");
    scanf("%d", &anio);

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria;
    NodoMatricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : Matricula;

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    NodoMatricula *nuevo_tempM = NULL;
    NodoMatricula *lista_tempM = NULL;

    NodoTrayectoria *auxT = lista_a_filtrar_T;

    printf("\nDatos encontrados del año %d:\n\n", anio);
    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    while (auxT != NULL)
    {
      if (auxT->id == anio)
      {
        bandera = 1;
        printf(
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
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
        if (nuevo != NULL)
        {
          *nuevo = *auxT;
          nuevo->sig = NULL;

          if (nuevo_tempT == NULL)
          {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          }
          else
          {

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

    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    NodoMatricula *auxM = lista_a_filtrar_M;

    while (auxM != NULL)
    {
      if (auxM->id == anio)
      {
        bandera = 1;
        printf(
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            auxM->provincia, auxM->sector, auxM->reg.repitentes[0],
            auxM->reg.repitentes[1], auxM->reg.repitentes[2],
            auxM->reg.repitentes[3], auxM->reg.repitentes[4],
            auxM->reg.repitentes[5], auxM->reg.matricula[0],
            auxM->reg.matricula[1], auxM->reg.matricula[2],
            auxM->reg.matricula[3], auxM->reg.matricula[4],
            auxM->reg.matricula[5], auxM->id);

        NodoMatricula *nuevoM = malloc(sizeof(NodoMatricula));
        if (nuevoM != NULL)
        {
          *nuevoM = *auxM;
          nuevoM->sig = NULL;

          if (nuevo_tempM == NULL)
          {
            nuevo_tempM = nuevoM;
            lista_tempM = nuevoM;
          }
          else
          {
            lista_tempM->sig = nuevoM;
            lista_tempM = nuevoM;
          }
        }
      }
      auxM = auxM->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0)
    {
      printf("\nNo se encontraron datos de matrícula en el año ingresado\n");
    }

    if ((*cont) < 3)
    {
      printf("\n¿Desea agregar otro filtro?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S')
      {
        printf("\nFiltros disponibles:\n");
        printf("a) Buscar por provincia\n");
        printf("b) Buscar por sector\n");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'a':
          BuscarPorProvincia(Matricula, RegistroTrayectoria, tempM,
                             tempT, cont);
          break;
        case 'b':
          BuscarPorTipo(Matricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nOpción no válida.\n");
        }
      }
      else
      {

        while (*tempM != NULL)
        {
          NodoMatricula *proxM = (*tempM)->sig;
          free(*tempM);
          *tempM = proxM;
        }

        while (*tempT != NULL)
        {
          NodoTrayectoria *proxT = (*tempT)->sig;
          free(*tempT);
          *tempT = proxT;
        }
        (*cont) = 0;
      }
    }
  }
  if ((*cont) > 3)
  {
    cont = 0;
  }
}

void BuscarPorTipo(NodoMatricula *Matricula,
                   NodoTrayectoria *RegistroTrayectoria, NodoMatricula **tempM,
                   NodoTrayectoria **tempT, int *cont)
{
  if (*(cont) < 3)
  {
    (*cont)++;
    char tipo[25];
    char tipo_normalizado[25];
    char opcion = ' ';
    int bandera = 0;

    NodoTrayectoria *lista_a_filtrar_T =
        (*tempT != NULL) ? *tempT : RegistroTrayectoria;
    NodoMatricula *lista_a_filtrar_M =
        (*tempM != NULL) ? *tempM : Matricula;

    NodoTrayectoria *nuevo_tempT = NULL;
    NodoTrayectoria *lista_tempT = NULL;
    NodoMatricula *nuevo_tempM = NULL;
    NodoMatricula *lista_tempM = NULL;

    printf("\nIngrese el tipo que desee buscar: ");
    scanf(" %24[^\n]", tipo);

    int j = 0;
    for (int i = 0; tipo[i] != '\0' && j < 10; i++)
    {
      if (tipo[i] != ' ' && tipo[i] != '\t')
      {
        tipo_normalizado[j] = tolower((unsigned char)tipo[i]);
        j++;
      }
    }
    tipo_normalizado[j] = '\0';

    printf("\nLos datos encontrados son:\n");
    printf("\n\n");
    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
           "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
           "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

    NodoTrayectoria *aux = lista_a_filtrar_T;

    while (aux != NULL)
    {
      char aux_sector_normalizado[25];

      {
        int j = 0;
        for (int i = 0; aux->sector[i] != '\0' && j < 10; i++)
        {
          if (aux->sector[i] != ' ' && aux->sector[i] != '\t')
          {
            aux_sector_normalizado[j] = tolower((unsigned char)aux->sector[i]);
            j++;
          }
        }
        aux_sector_normalizado[j] = '\0';
      }

      if (strcmp(aux_sector_normalizado, tipo_normalizado) == 0)
      {
        bandera = 1;

        printf(
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

        NodoTrayectoria *nuevo =
            (NodoTrayectoria *)malloc(sizeof(NodoTrayectoria));
        if (nuevo != NULL)
        {
          nuevo->sig = NULL;
          strcpy(nuevo->sector, aux->sector);
          strcpy(nuevo->provincia, aux->provincia);
          nuevo->id = aux->id;
          for (int i = 0; i < 6; i++)
          {
            nuevo->trayectoria.nopromovidos[i] =
                aux->trayectoria.nopromovidos[i];
            nuevo->trayectoria.promovidos[i] = aux->trayectoria.promovidos[i];
          }
          nuevo->trayectoria.secundariaEgresados =
              aux->trayectoria.secundariaEgresados;

          if (nuevo_tempT == NULL)
          {
            nuevo_tempT = nuevo;
            lista_tempT = nuevo;
          }
          else
          {
            lista_tempT->sig = nuevo;
            lista_tempT = nuevo;
          }
        }
        else
        {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux = aux->sig;
    }

    *tempT = nuevo_tempT;

    if (bandera == 0)
    {
      printf("\nNo se ha encontrado el tipo ingresado\n");
    }
    bandera = 0;
    printf("\n\n");
    printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
           "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
           "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
           "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR",
           "Anio");

    NodoMatricula *aux2 = lista_a_filtrar_M;

    while (aux2 != NULL)
    {
      char aux2_sector_normalizado[25];

      {
        int j = 0;
        for (int i = 0; aux2->sector[i] != '\0' && j < 24; i++)
        {
          if (aux2->sector[i] != ' ' && aux2->sector[i] != '\t')
          {
            aux2_sector_normalizado[j] =
                tolower((unsigned char)aux2->sector[i]);
            j++;
          }
        }
        aux2_sector_normalizado[j] = '\0';
      }

      if (strcmp(aux2_sector_normalizado, tipo_normalizado) == 0)
      {
        bandera = 1;
        printf(
            "%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
            "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
            aux2->provincia, aux2->sector, aux2->reg.repitentes[0],
            aux2->reg.repitentes[1], aux2->reg.repitentes[2],
            aux2->reg.repitentes[3], aux2->reg.repitentes[4],
            aux2->reg.repitentes[5], aux2->reg.matricula[0],
            aux2->reg.matricula[1], aux2->reg.matricula[2],
            aux2->reg.matricula[3], aux2->reg.matricula[4],
            aux2->reg.matricula[5], aux2->id);

        NodoMatricula *nuevo2 = (NodoMatricula *)malloc(sizeof(NodoMatricula));
        if (nuevo2 != NULL)
        {
          nuevo2->sig = NULL;
          strcpy(nuevo2->sector, aux2->sector);
          strcpy(nuevo2->provincia, aux2->provincia);
          nuevo2->id = aux2->id;
          for (int i = 0; i < 6; i++)
          {
            nuevo2->reg.matricula[i] = aux2->reg.matricula[i];
            nuevo2->reg.repitentes[i] = aux2->reg.repitentes[i];
          }

          if (nuevo_tempM == NULL)
          {
            nuevo_tempM = nuevo2;
            lista_tempM = nuevo2;
          }
          else
          {
            lista_tempM->sig = nuevo2;
            lista_tempM = nuevo2;
          }
        }
        else
        {
          printf("\nError al crear lista auxiliar\n");
        }
      }
      aux2 = aux2->sig;
    }

    *tempM = nuevo_tempM;

    if (bandera == 0)
    {
      printf("\nNo se ha encontrado el tipo ingresado\n");
    }
    bandera = 0;

    if ((*cont) < 3)
    {
      printf("\nDesea agregar otro filtro\?: Si(s), No(n)\n");
      scanf(" %c", &opcion);

      if (opcion == 's' || opcion == 'S')
      {
        printf("\nFiltros disponibles:\n");
        printf("a) Buscar por provincia\n");
        printf("b) Buscar por anio\n");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'a':
          BuscarPorProvincia(Matricula, RegistroTrayectoria, tempM,
                             tempT, cont);
          break;
        case 'b':
          BuscarPorAnio(Matricula, RegistroTrayectoria, tempM, tempT,
                        cont);
          break;
        default:
          printf("\nOpción no válida.\n");
        }
      }
      else
      {

        while (*tempM != NULL)
        {
          NodoMatricula *proxM = (*tempM)->sig;
          free(*tempM);
          *tempM = proxM;
        }

        while (*tempT != NULL)
        {
          NodoTrayectoria *proxT = (*tempT)->sig;
          free(*tempT);
          *tempT = proxT;
        }
        (*cont) = 0;
      }
    }
  }
  if ((*cont) > 3)
  {
    cont = 0;
  }
}

void VerSector(NodoTrayectoria *Tr, NodoMatricula *Mtr)
{
  NodoTrayectoria *auxTr = Tr;
  NodoMatricula *auxMtr = Mtr;

  // ---- SECTOR ESTATAL ----
  printf("TRAYECTORIA ESTATAL: \n");
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

  // Muestra solo los datos de escuelas estatales
  while (auxTr != NULL)
  {
    if (strcmp(auxTr->sector, "Estatal") == 0)
    {
      printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
             "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
             auxTr->provincia, auxTr->sector,
             auxTr->trayectoria.promovidos[0], auxTr->trayectoria.promovidos[1],
             auxTr->trayectoria.promovidos[2], auxTr->trayectoria.promovidos[3],
             auxTr->trayectoria.promovidos[4], auxTr->trayectoria.promovidos[5],
             auxTr->trayectoria.nopromovidos[0], auxTr->trayectoria.nopromovidos[1],
             auxTr->trayectoria.nopromovidos[2], auxTr->trayectoria.nopromovidos[3],
             auxTr->trayectoria.nopromovidos[4], auxTr->trayectoria.nopromovidos[5],
             auxTr->trayectoria.secundariaEgresados, auxTr->id);
    }
    auxTr = auxTr->sig;
  }

  printf("\n\nMATRICULA ESTATAL: \n");
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");

  // Muestra las matrículas de las escuelas estatales
  while (auxMtr != NULL)
  {
    if (strcmp(auxMtr->sector, "Estatal") == 0)
    {
      printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
             "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
             auxMtr->provincia, auxMtr->sector,
             auxMtr->reg.repitentes[0], auxMtr->reg.repitentes[1],
             auxMtr->reg.repitentes[2], auxMtr->reg.repitentes[3],
             auxMtr->reg.repitentes[4], auxMtr->reg.repitentes[5],
             auxMtr->reg.matricula[0], auxMtr->reg.matricula[1],
             auxMtr->reg.matricula[2], auxMtr->reg.matricula[3],
             auxMtr->reg.matricula[4], auxMtr->reg.matricula[5],
             auxMtr->id);
    }
    auxMtr = auxMtr->sig;
  }

  // Reinicio para mostrar la parte privada
  auxTr = Tr;
  auxMtr = Mtr;

  printf("\n\nTRAYECTORIA PRIVADO: \n");
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %-9s | %s\n",
         "Provincia", "Sector", "1_P", "2_P", "3_P", "4_P", "5_P", "6_P",
         "1_NP", "2_NP", "3_NP", "4_NP", "5_NP", "6_NP", "Egresados", "Anio");

  // Datos del sector privado
  while (auxTr != NULL)
  {
    if (strcmp(auxTr->sector, "Privado") == 0)
    {
      printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
             "%-6d | %-6d | %-6d | %-6d | %-6d | %-9d | %d\n",
             auxTr->provincia, auxTr->sector,
             auxTr->trayectoria.promovidos[0], auxTr->trayectoria.promovidos[1],
             auxTr->trayectoria.promovidos[2], auxTr->trayectoria.promovidos[3],
             auxTr->trayectoria.promovidos[4], auxTr->trayectoria.promovidos[5],
             auxTr->trayectoria.nopromovidos[0], auxTr->trayectoria.nopromovidos[1],
             auxTr->trayectoria.nopromovidos[2], auxTr->trayectoria.nopromovidos[3],
             auxTr->trayectoria.nopromovidos[4], auxTr->trayectoria.nopromovidos[5],
             auxTr->trayectoria.secundariaEgresados, auxTr->id);
    }
    auxTr = auxTr->sig;
  }

  printf("\n\nMATRICULA PRIVADO: \n");
  printf("%-25s | %-10s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | %-6s | "
         "%-6s | %-6s | %-6s | %-6s | %-6s | %s\n",
         "Provincia", "Sector", "1_REP", "2_REP", "3_REP", "4_REP", "5_REP",
         "6_REP", "1_MTR", "2_MTR", "3_MTR", "4_MTR", "5_MTR", "6_MTR", "Anio");

  // Muestra la matrícula privada
  while (auxMtr != NULL)
  {
    if (strcmp(auxMtr->sector, "Privado") == 0)
    {
      printf("%-25s | %-10s | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | %-6d | "
             "%-6d | %-6d | %-6d | %-6d | %-6d | %d\n",
             auxMtr->provincia, auxMtr->sector,
             auxMtr->reg.repitentes[0], auxMtr->reg.repitentes[1],
             auxMtr->reg.repitentes[2], auxMtr->reg.repitentes[3],
             auxMtr->reg.repitentes[4], auxMtr->reg.repitentes[5],
             auxMtr->reg.matricula[0], auxMtr->reg.matricula[1],
             auxMtr->reg.matricula[2], auxMtr->reg.matricula[3],
             auxMtr->reg.matricula[4], auxMtr->reg.matricula[5],
             auxMtr->id);
    }
    auxMtr = auxMtr->sig;
  }
}
