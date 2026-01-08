#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validaciones.h"

int main(int argc, char *argv[])
{
    int count = 0;
    char entrada[50];
    char busqueda[50];
    int opc1;

    // Creacion del archivo
    FILE *archivo;
    archivo = fopen("inventario.txt", "r");

    if (archivo != NULL)
    {
        fclose(archivo);
    }
    else
    {
        fclose(archivo);
        archivo = fopen("inventario.txt", "a");

        if (archivo == NULL)
        {
            perror("\nError al crear el archivo.");
            return 1;
        }

        fprintf(archivo, "%-20s %-10s %-10s %-10s %-10s %-10s\n", "Marca", "Tipo", "Modelo", "Estado", "Anio", "Precio");
        fclose(archivo);
        printf("\nEl archivo fue creado con exito!");
    }

    do
    {
        int opcValida = 0;
        do
        {
            printf("\nElija una opcion: ");
            printf("\n1) Ingreso de nuevo vehiculo");
            printf("\n2) Busqueda de vehiculo");
            printf("\n3) Salir");
            printf("\n>>> ");
            // LimpiarBuffer();

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
            FILE *file = fopen("inventario.txt", "a");
            if (count == 10)
            {
                printf("\nSolo se pueden ingresar 10 vehiculos, regresando al menu principal");
                break;
            }

            IngresarProducto(entrada, file);

            // Aumentar la cantidad de productos ingresados
            count++;
            break;

        case 2:

            // Verificacion de busqueda
            int busquedaValida = 0;
            do
            {
                printf("\nIngrese la busqueda que desea realizar: ");
                if (fgets(entrada, 50, stdin) == NULL)
                {
                    LimpiarBuffer();
                    continue;
                }

                // Eliminar el salto de línea al final de la cadena
                entrada[strcspn(entrada, "\n")] = '\0';

                if (VerificacionChar(entrada) == 1)
                {
                    strcpy(busqueda, entrada);
                    busquedaValida = 1;
                }
                else
                {
                    printf("\nSolo se permiten letras. Intentelo de nuevo.");
                    busquedaValida = 0;
                }

            } while (busquedaValida == 0);

            Busqueda(busqueda, "inventario.txt");

            break;

        case 3:
            printf("\nGracias por usar nuestro sistema. Saliendo!!");
            break;

        default:
            printf("\nOpcion invalida, intentelo de nuevo...");
            break;
        }
    } while (opc1 != 3);

    return 0;
}