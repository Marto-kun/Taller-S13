#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct
{
    int anio;
    float precio;
    char marca[30];
    char modelo[30];
    char estado[15];
    char tipo[30];
} Auto;

/**
 * @brief Funcion para verificar numeros enteros
 *
 * @param string
 * @return int
 */
int VerificacionDigitos(char string[])
{

    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    for (int i = 0; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
        {
            return 0; // Si el elemento de la cadena no es caracter retorna 0
        }
    }
    return 1; // Si la cadena son solo digitos entonces se retorna verdadero
}

/**
 * @brief Funcion para validar datos decimales
 *
 * @param string
 * @return int
 */
int VerificacionFloat(char string[])
{
    int nPuntos = 0;
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    for (int i = 0; i < strlen(string); i++)
    {
        char c = string[i];
        if (isdigit(c))
        {
            continue; // Si el elemento de la cadena es digito continua el bucle
        }
        else if (c == '.')
        {
            nPuntos++;
        }
        else
        {
            return 0; // Si no es digito o punto, es invalido
        }
    }

    if (nPuntos > 1)
    {
        return 0; // No pueden haber mas de 1 punto en el numero decimal
    }

    if (strlen(string) == 1 && (string[0] == '.'))
    {
        return 0; // Cadena invalida si solo es un punto
    }

    return 1; // Si la cadena son digitos validos entonces se retorna verdadero
}

/**
 * @brief Funcion para limpieza de buffer
 * evitar buffer overflow
 *
 */
void LimpiarBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
        ;
}

/**
 * @brief Funcion para verificar solo letras
 *
 * @param string
 * @return int
 */
int VerificacionChar(char string[])
{
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    size_t len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(string[i]))
        {
            return 0; // Si el elemento de la cadena es digito retorna 0
        }
    }
    return 1; // Si la cadena son solo caracteres entonces se retorna 1
}

/**
 * @brief Funcion para verificar solo letras
 *
 * @param string
 * @return int
 */
int VerificacionCharEspacios(char string[])
{
    if (strlen(string) == 0)
    {
        return 0; // Comprobar que la cadena no este vacia
    }

    size_t len = strlen(string);

    for (int i = 0; i < len; i++)
    {
        if (!isalpha(string[i]) && string[i] != ' ')
        {
            return 0; // Si el elemento de la cadena es digito retorna 0
        }
    }
    return 1; // Si la cadena son solo caracteres o espacios entonces se retorna 1
}

/**
 * @brief Funcion para verificar si es que una cadena ingresada esta vacia
 *
 * @param str
 * @return 0 si es valida, 1 si esta vacia
 */
int esVacia(char *str)
{
    if (str[0] == '\0')
    {
        return 1;
    }
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] != ' ' && str[i] != '\t')
            return 0;
    }
    return 1;
}

/**
 * @brief Busca todas las ocurrencias de un ingreso del usuario
 *        dentro del archivo de inventario
 *
 * @param buscar Busqueda ingresada por el usuario
 * @param archivo Puntero al nombre del archivo de inventario
 */
void Busqueda(char buscar[50], const char *archivo, float presupuesto)
{
    int count = 0;
    float precio;
    FILE *file = fopen(archivo, "r");

    if (file == NULL)
    {
        perror("\nError al abrir el archivo");
        return;
    }

    char buffer[150];

    while (fgets(buffer, sizeof(buffer), file))
    {

        if (sscanf(buffer, "%*s %*s %*s %*s %*i %f", &precio) == 1)
        {
            if (strstr(buffer, buscar) != NULL && precio <= presupuesto)
            {
                printf("\n %s", buffer);
                count++;
            }
        }
    }
    if (count == 0)
    {
        printf("\nNo se ha encontrado ninguna coincidencia");
    }
    else
    {
        printf("\nSe han encontrado %i vehiculo(s) con su busqueda", count);
    }

    fclose(file);
}

/**
 * @brief Recibe e ingresa productos en el archivo de inventario
 *
 * @param entrada Texto ingresado por el usuario
 * @param archivo Puntero al archivo de inventario
 */
void IngresarProducto(char entrada[50], FILE *archivo)
{
    Auto nuevo[10];
    int count = 0;
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

        if (VerificacionCharEspacios(entrada) == 1)
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
        printf("\nIngrese el estado del auto (Nuevo o Usado): ");
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

    fprintf(archivo, "%-20s %-10s %-10s %-10s %-10i %-10.2f\n", nuevo[count].marca, nuevo[count].tipo, nuevo[count].modelo, nuevo[count].estado, nuevo[count].anio, nuevo[count].precio);
    fclose(archivo);
}