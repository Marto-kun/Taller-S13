#include <stdio.h>
#include "validaciones.h"
#include <string.h>

typedef struct
{
    int anio;
    float precio;
    char marca[30];
    char modelo[30];
    char estado[5];
    char tipo[25];
} Auto;

int main(int argc, char *argv[])
{
    char entrada[40];
    int opc1;
    FILE *archivo;
    archivo = fopen("inventario.txt", "w");

    if (archivo == NULL)
    {
        printf("\nError, no se pudo abrir el archivo");
        return 1;
    }

    int opcValida = 0;
    do
    {
        printf("\nElija una opción: ");
        printf("\n1) Ingreso de nuevo vehículo");
        printf("\n2) Busqueda de vehiculo por Marca");
        printf("\3) Busqueda de vehiculo por Tipo");
        printf("\n4) Busqueda de vehiculo por Modelo");
        printf("\n5) Busqueda de vehiculo por Estado");
        printf("\n6) Busqueda de vehiculo por Anio de Fabricacion");
        printf("\n7) Busqueda de vehiculo por Precio");
        printf("\n8) Salir");
        printf("\n>>> ");

        if (fgets(entrada, 25, stdin) == NULL)
        {
            LimpiarBuffer();
            continue;
        }

        // Eliminar el salto de línea al final de la cadena
        entrada[strcspn(entrada, "\n")] = '\0';

        if (VerificacionDigitos(entrada))
        {
            opc1 = atoi(entrada);
            opcValida = 1;
        }
        else
        {
            printf("\nSolo se permiten numeros enteros");
        }

    } while (opcValida == 0);

    switch (opc1)
    {
    case 1:
        Auto nuevo;
        int marcaValida = 0;
        do
        {
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionChar(entrada) == 1)
            {
                strcpy(nuevo.marca, entrada);
                marcaValida = 1;
            }
            else
            {
                printf("\nSolo se permiten letras. Intentelo de nuevo.");
                marcaValida = 0;
            }

        } while (marcaValida == 0);

        break;

    default:
        break;
    }

    fclose(archivo);

    return 0;
}