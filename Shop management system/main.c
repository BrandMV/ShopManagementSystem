#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <wait.h>   //define las declaraciones de espera
#include <unistd.h> //define las declaraciones de espera

typedef struct Producto
{
    int id;        //guarda el id del producto
    char produ[50]; //alamcena el nombre del producto
    int precio;    //guarda el precio del producto
    int cantidad;  //guarda la cantidad de productos
} Producto;

typedef struct Carrito
{
    int idProd;      //id del producto que esta en el carrito
    char prodNom[50]; //nombre del producto que esta en el carrito
    int precio;      //precio del producto del carrito
    int cantidad;    //cantidad que se desea comprar del producto
} Carrito;

void verProductos();
void editProducto();
void compraProducto();
void actualizarPds(int idp, int cantidad);
void verCarrito();
void menuCliente(char *cliente);
void cliente();
void proveedor();
void menuProveedor();
void aProductos();
void eProducto();

void verProductos()
{
    FILE *p;      //para ver los productos contenidos en un archivo
    Producto pro; // estructura de tipo prodcuto

    p = fopen("productos.dat","rb");
    printf("\t\t\t==========================================\n");
    printf("\t\t\tLista de productos disponibles en la tienda\n");
    printf("\t\t\t===========================================\n");

    printf("\t\t\tid\tProducto\tprecio\tstock\n");
    while (1)
    {
        fread(&pro, sizeof(pro), 1, p); //leemos un producto del archivo y se guarda en pro
        if (feof(p)) //cuando llegamos al final se cierra
            break;

        //imprimimos los productos
        printf("\t\t\t%d\t", pro.id);
        printf("\t\t\t%d\t", pro.produ);
        printf("\t\t\t%d\t", pro.precio);
        printf("\t\t\t%d\n", pro.cantidad);
    }

    fclose(p); //cerramos el archivo
}

void compraProducto(){
    char res[2], cont[2]; //variables para opcion del cliente
    int idp; //variable para indicar el producto a agregar al carrito
    int cant; //variable para indicar la cantidad del producto
    FILE *ca,*p; //variable para el archivo de carrito
    Producto pro;
    Carrito c;

    while(1){
        verProductos();
        __fpurge(stdin); //Vaciamos el buffer
        printf("\t¿Desea agregar al carrito? Ingrese una s si desea agregar o una n si no lo desea\n");
        scanf("%c",&res);

        if(strcmp(res,"s") == 0){
            //abrimos el archivo de carrito para añadir el producto al final
            ca = fopen("carrito.dat", "ab"); 
            printf("Ingrese el producto a añadir al carrito (id): ");
            scanf("%d",&idp);//leemos el id del producto
            printf("\nIngrese la cantidad del producto: ");
            scanf("%d",&cant); //leemos la cantidad del producto

            //buscamos el producto
            p = fopen("productos.dat", "rb");
            while(1){
                fread(&pro, sizeof(pro),1,p);
                if(feof(p))
                    break;
                if(pro.id == idp){
                    actualizarPds(idp, pro.cantidad-cant); //actualizamos la lista de productos
                    break; //salimos del if
                }
            }
            fclose(p); //Terminamos de actualizar el producto

            //aquí guardamos el producto seleccionado en el carrito
            c.idProd = pro.id; 
            strcpy(c.prodNom, pro.produ); //copiamos las cadenas
            c.precio = pro.precio;
            c.cantidad = pro.cantidad;
            fwrite(&c,sizeof(c),1,p); //guardamos el valor de c en el archivo de productos
            fclose(p); //cerramos el archivo
        }
        __fpurge(stdin); //Vaciamos el buffer
        if(strcmp(res,"n") == 0)
            break;

    }
}

void actualizarPds(int idp, int cantidad){
    FILE *p, *auxP;
    Producto pro, auxPro;
    int bandera; //para indicar que hubo coincidencia en el producto

    p = fopen("productos.dat", "rb");
    auxP = fopen("aux.dat", "wb"); //Creamos un archivo temporal para actualizar los productos
    while(1){
        fread(&pro, sizeof(pro),1,p);
        if(feof(p)) //Si llega al final del archivo salimos
            break;
        if(pro.id == idp){
            bandera = 1; //se encontró el producto
            pro.cantidad = cantidad; //se actualiza la cantidad
            fwrite(&pro,sizeof(pro),1,auxP); //se copian los productos en un archivo auxiliar
        }else
            fwrite(&pro,sizeof(pro),1,auxP);//se copian los productos en un archivo auxiliar
    }
    //cerramos los archivos
    fclose(p);
    fclose(auxP);

    if(bandera == 0)
        printf("No se encontró el producto\n");
    else{
        //volvemos a abrir los archivos
        p = fopen("productos.dat", "wb"); //se abre en escritura para actualizarlo
        auxP = fopen("aux.dat", "rb"); //Se abre en lectura
        while(1){
            fread(&pro,sizeof(pro),1,auxP); //se guarda la estructura del archivo en pro
            if(feof(auxP)) //si se llega al final salimos
                break;
            fwrite(&pro, sizeof(pro),1,p); //guardamos pro en el archivo de productos.dat
        }
    }

    //cerramos los archivos
    fclose(p);
    fclose(auxP);
}

void verCarrito(){

}

void menuCliente(char *cliente)
{
    system("clear");
    printf("\t\t\t=====================================\n");
    printf("\t\t\t===Bienvenido a la tienda %s===\n", cliente);
    printf("\t\t\t=====================================\n");

    int opc;
    while (opc != 3)
    {

        printf("\n\n\t\t¿Que desea realizar? \n\n");
        printf("\t\t1. Comprar productos\n");
        printf("\t\t2. Ver tu carrito\n");
        printf("\t\t3. Cerrar sesión\n");
        scanf("%d", &opc);
        if (opc > 4)
            printf("Opcion no valida\n");

        switch (opc)
        {
        case 1:
            system("clear");
            verProductos();
            break;
        case 2:
            verCarrito();
            break;
        case 3:
            system("clear");
            break;
        }
    }
}

void cliente()
{
    int existe;      //variable para verificar si existe tal usuario
    FILE *aClientes; //archivo de clientes
    char cliente[30];
    char pass[30];
    char lCliente[100]; //para leer la linea de cliente del archivo
    char lPass[100];    //para leer la linea de contraseña del cliente del archivo

    printf("Ingrese su usuario: \n"); //el cliente ingresa su usuario
    scanf("%s", cliente);             //se lee el usuario del cliente
    printf("Ingrese su clave; \n");   //el cliente ingresa su contraseña
    scanf("%s", pass);                //se lee la contraseña del usuario

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
void proveedor()
{

    int existe;      //variable para verificar si existe tal usuario
    FILE *aProveedor; //archivo de proveedor
    char proveedor[30];
    char pass[30];
    char lProveedor[100]; //para leer la linea del proveedor del archivo
    char lPass[100];    //para leer la linea de contraseña del proveedor del archivo

    printf("Ingrese su usuario dado por la empresa: \n"); //el proveedor ingresa su usuario
    scanf("%s", proveedor);             //se lee el usuario del cliente
    printf("Ingrese su clave; \n");   //el proveedor ingresa su contraseña
    scanf("%s", pass);                //se lee la contraseña del proveedor

    aProveedor = fopen("proveedor.txt", "r"); //se abre el archivo que contiene los clientes en solo lectura

    if (aProveedor == NULL)
    {
        printf("No se pudo abrir el archivo que contiene el proveedor");
        exit(0);
    }

    while (!feof(aProveedor))
    {                                                //se lee el archivo de clientes
        if (fgets(lProveedor, 100, aProveedor) != NULL) //se lee la línea del usuario del cleinte
        {
            if (fgets(lPass, 100, aProveedor) != NULL) // se lee la línea de la contraseña
            {
                strcpy(lProveedor, strtok(lProveedor, "\n")); //eliminamos salto de línea si es que  hay
                strcpy(lPass, strtok(lPass, "\n"));

                //vemos si coincide el usuario y la contraseña
                if (strcmp(proveedor, lProveedor) == 0 && strcmp(pass, lPass) == 0)
                {
                    existe = -1; //retornamos true; true = -1
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

    fclose(aProveedor);

    if (existe == -1)
    {
        printf("Iniciando sesion como proveedor...\n");
        sleep(2);
        menuProveedor();
    }
    else
        printf("Verifique sus datos\n");
}

void menuProveedor()
{
    system("clear");
    printf("\t\t\t======================================\n");
    printf("\t\t\t===Bienvenido a la tienda proveedor===\n");
    printf("\t\t\t======================================\n");

    int opc;
    while (opc != 3)
    {

        printf("\n\n\t\t¿Que desea realizar? \n\n");
        printf("\t\t1. Agregar producto\n");
        printf("\t\t2. Editar stock de producto\n");
        printf("\t\t3. Cerrar sesión\n");
        scanf("%d", &opc);
        if (opc > 4)
            printf("Opcion no valida\n");

        switch (opc)
        {
        case 1:
            system("clear");
            aProductos(); //funcion para añadir productos
            break;
        case 2:
            editProducto(); //funcion para editar stock de producto
            break;
        case 3:
            system("clear");
            break;
        }
    }
}
void aProductos(){

}

void editProducto(){

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
            system("clear");
            proveedor();
            break;
        case 3:
            return 0;
        }
    }
}