#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void cliente()
{
    int intento = 1; //varible para intentos de logeo de usuario
    int existe;      //variable para verificar si existe tal usuario
    FILE *aClientes; //archivo de clientes
    char cliente[30];
    char pass[30];
    char lCliente[100]; //para leer la linea de cliente del archivo
    char lPass[100];    //para leer la linea de contraseña del cliente del archivo

    while (intento < 3)
    {
        printf("Ingrese su usuario: \n"); //el cliente ingresa su usuario
        gets(cliente);                    //se lee el usuario del cliente
        printf("Ingrese su clave; \n");   //el cliente ingresa su contraseña
        gets(pass);                       //se lee la contraseña del usuario

        aClientes = fopen("clientes.txt", "r"); //se abre el archivo que contiene los clientes en solo lectura

        if (aClientes == NULL)
        {
            printf("No se pudo abrir el archivo que contiene los clientes");
            exit(0);
        }

      
    }
}

int main()
{
    int opc;
    while (opc >= 0)
    {
        printf("\t\t============================\n");
        printf("\t\t===Bienvenido a la tienda===\n");
        printf("\t\t============================\n");
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
            // cliente();
            break;
        case 2:
            // proveedor()
            break;
        case 3:
            return 0;
        }
    }
}