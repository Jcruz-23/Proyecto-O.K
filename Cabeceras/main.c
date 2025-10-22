#include "../Cabeceras/Prototipos.h"

int main() {
  NodoTrayectoria *RegistroTrayectoria = NULL;
  NodoMatricula *Matricula = NULL;
  NodoMatricula *tempM = NULL;
  NodoTrayectoria *tempT = NULL;
  int cont = 0;
  InsertarNodoTrayectoria(&RegistroTrayectoria);
  LecturaMatricula(&Matricula);
  ImprimirLista(RegistroTrayectoria, Matricula);
  printf("\n--- Filtro 1: Buscar por provincia ---\n");
  BuscarPorProvincia(Matricula, RegistroTrayectoria, &tempM, &tempT,
                     &cont);
  printf("\n--- Filtro 2: Buscar por tipo ---\n");
  BuscarPorTipo(Matricula, RegistroTrayectoria, &tempM, &tempT, &cont);
  printf("\n--- Filtro 3: Buscar por año ---\n");
  BuscarPorAnio(Matricula, RegistroTrayectoria, &tempM, &tempT, &cont);

  return 0;
}
