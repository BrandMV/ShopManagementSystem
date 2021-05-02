#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <wait.h> //define las declaraciones de espera
#include <unistd.h> //define las declaraciones de espera


void menuCliente(char *cliente)
{
    system("clear");
    printf("\t\t\t=====================================\n");
    printf("\t\t\t===Bienvenido a la tienda %s===\n", cliente);
    printf("\t\t\t=====================================\n");
}

void cliente()
{
    int intento = 1; //varible para intentos de logeo de usuario
    int existe;      //variable para verificar si existe tal usuario
    FILE *aClientes; //archivo de clientes  
    char cliente[30];
    char pass[30];
    char lCliente[100]; //para leer la linea de cliente del archivo
    char lPass[100];    //para leer la linea de contraseña del cliente del archivo
    
    printf("Ingrese su usuario: \n"); //el cliente ingresa su usuario
    scanf("%s", cliente);                 //se lee el usuario del cliente
    printf("Ingrese su clave; \n");   //el cliente ingresa su contraseña
    scanf("%s", pass);                     //se lee la contraseña del usuario

    aClientes = fopen("clientes.txt", "r"); //se abre el archivo que contiene los clientes en solo lectura

    if (aClientes == NULL)
    {
        printf("No se pudo abrir el archivo que contiene los clientes");
        exit(0);
    }

    while (!feof(aClientes))
    {                                                //se lee el archivo de clientes
        if (fgets(lCliente, 100, aClientes) != NULL) //se lee la línea del usuario del cleinte
        {
            if (fgets(lPass, 100, aClientes) != NULL) // se lee la línea de la contraseña
            {
                strcpy(lCliente, strtok(lCliente, "\n")); //eliminamos salto de línea si es que  hay
                strcpy(lPass, strtok(lPass, "\n"));

                //vemos si coincide el usuario y la contraseña
                if (strcmp(cliente, lCliente) == 0 && strcmp(pass, lPass) == 0)
                {
                    existe = -1; //retornamos true; ture = -1
                    break;
                }
            }
            else
            {
                printf("Error al iniciar sesion...");
                exit(0);
            }
        }
        else
        {
            printf("Error al iniciar sesion...");
            exit(0);
        }
    }

    fclose(aClientes);

    if (existe == -1)
    {
        printf("Iniciando sesion...\n");
        sleep(2);
        menuCliente(cliente);
    }
    else
        printf("Verifique sus datos\n");
}


int main()
{
    int opc;
    while (opc >= 0)
    {
        printf("\t\t\t============================\n");
        printf("\t\t\t===Bienvenido a la tienda===\n");
        printf("\t\t\t============================\n");
        printf("\n\n\t\tUsted es: \n\n");
        printf("\t\t1. Cliente\n");
        printf("\t\t2. Proveedor\n");
        printf("\t\t3. Salir del sistema\n");
        scanf("%d", &opc);
        if (opc > 4)
            printf("Opcion no valida\n");

        switch (opc)
        {
        case 1:
            system("clear");
            cliente();
            break;
        case 2:
            // proveedor()
            break;
        case 3:
            return 0;
        }
    }
}