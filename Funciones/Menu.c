// Esta funcion tiene que mostrar por consola una lista de opciones a, b, c, etc. Con el siguiente formato:
// ------- MENU -------
// a. Mostrar nodo
// b. Mostrar datos de todas las provincias
// c. Mostrar datos de todos los anios(2019, 2020, 2021)
// d. Mostrar datos de educacion publica y privada
// e. Buscar por provincia
// f. Buscar por anio
// g. Buscar por tipo
// s. Salir
// Tener en cuenta que al mostrar las ultimas tres opciones, hay que ofrecer si se quiere combinar el filtro que se elija con algun otro.

void Menu(Matricula *mat, NodoTrayectoria *tr)
{
    char opcion = '\0';
    Matricula *tempM = NULL;
    NodoTrayectoria *tempT = NULL;
    int cont = 0;

    do
    {
        printf("\n-------------- MENU --------------\n a. Mostrar nodo\n b. Mostrar datos de todas las provincias\n c. Mostrar datos de educacion publica y privada\n d. Buscar por provincia\n e. Buscar por anio\n f. Buscar por tipo\n s. Salir");
        printf("\nIngrese la opcion que desea realizar:\n");
        scanf(" %c", &opcion);

        switch (opcion)
        {
        case 'A':
        case 'a':
            MostrarNodo(mat, tr);
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