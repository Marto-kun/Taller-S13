#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "validaciones.h"

typedef struct
{
    int anio;
    float precio;
    char marca[30];
    char modelo[30];
    char estado[5];
    char tipo[30];
} Auto;

int main(int argc, char *argv[])
{
    Auto nuevo[10];
    int count = 0;
    char entrada[40];
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

        if(archivo == NULL){
            perror("\nError al crear el archivo.");
            return 1;
        }

        fprintf(archivo, "%-20s %-10s %-10s %-10s %-10s %-10s\n", "Marca", "Tipo", "Modelo", "Estado", "Anio", "Precio");
        fclose(archivo);
        printf("\nEl archivo fue creado con exito!");
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
        //LimpiarBuffer();

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
        if (count == 10)
        {
            printf("\nSolo se pueden ingresar 10 vehiculos, regresando al menu principal");
            break;
        }
        // Marca de vehiculo
        int marcaValida = 0;
        do
        {
            printf("\nIngrese la marca del auto: ");
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionChar(entrada) == 1)
            {
                strcpy(nuevo[count].marca, entrada);
                marcaValida = 1;
            }
            else
            {
                printf("\nSolo se permiten letras. Intentelo de nuevo.");
                marcaValida = 0;
            }

        } while (marcaValida == 0);


        // Tipo de vehiculo
        int tipoValido = 0;
        do
        {
            printf("\nIngrese el tipo del auto: ");
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionChar(entrada) == 1)
            {
                strcpy(nuevo[count].tipo, entrada);
                tipoValido = 1;
            }
            else
            {
                printf("\nSolo se permiten letras. Intentelo de nuevo.");
                tipoValido = 0;
            }

        } while (tipoValido == 0);


        // Modelo del vehiculo
        int modeloValido = 0;
        do
        {
            printf("\nIngrese el modelo del auto: ");
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionChar(entrada) == 1)
            {
                strcpy(nuevo[count].modelo, entrada);
                modeloValido = 1;
            }
            else
            {
                printf("\nSolo se permiten letras. Intentelo de nuevo.");
                modeloValido = 0;
            }

        } while (modeloValido == 0);


        // Precio del vehiculo
        int precioValido = 0;
        do
        {
            printf("\nIngrese el precio del vehiculo: ");
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                float precioIngresado = atof(entrada);
                if (precioIngresado > 0)
                {
                    nuevo[count].precio = precioIngresado;
                    precioValido = 1;
                }
                else
                {
                    printf("\nSe debe ingresar un precio valido mayor a 0");
                }
            }

        } while (precioValido == 0);

        // Anio del vehiculo
        int anioValido = 0;
        do
        {
            printf("\nIngrese el anio del vehiculo: ");
            if (fgets(entrada, 30, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionFloat(entrada))
            {
                int anioIngresado = atof(entrada);
                if (anioIngresado > 1950)
                {
                    nuevo[count].anio = anioIngresado;
                    anioValido = 1;
                }
                else
                {
                    printf("\nSe debe ingresar un anio valido mayor a 1950");
                }
            }

        } while (anioValido == 0);
        

        // Estado del vehiculo
        int estadoValido = 0;
        do
        {
            printf("\nIngrese el estado del auto: ");
            if (fgets(entrada, 10, stdin) == NULL)
            {
                LimpiarBuffer();
                continue;
            }

            // Eliminar el salto de línea al final de la cadena
            entrada[strcspn(entrada, "\n")] = '\0';

            if (VerificacionChar(entrada) == 1)
            {
                strcpy(nuevo[count].estado, entrada);
                estadoValido = 1;
            }
            else
            {
                printf("\nSolo se permiten letras. Intentelo de nuevo.");
                estadoValido = 0;
            }

        } while (estadoValido == 0);


        archivo = fopen("inventario.txt", "a");
        archivo;
        fprintf(archivo, "%-20s %-10s %-10s %-10s %-10s %-10s\n", nuevo[count].marca, nuevo[count].tipo, nuevo[count].modelo, nuevo[count].precio, nuevo[count].anio, nuevo[count].estado);
        fclose(archivo);

        // Aumentar la cantidad de productos ingresados
        count++;

        break;

    case 2:

    default:
        break;
    }

    return 0;
}