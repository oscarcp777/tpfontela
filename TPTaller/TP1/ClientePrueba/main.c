#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>                 // Referencia a la librería
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"


/************************************************************/
/*                                                          */
/*                  MAIN DEL CLIENTE                        */
/* se conecta el cliente y se levantan los hilos            */
/*                                                          */
/***********************************************************/


int main(int argc, char *argv[])
{
    CONEXION conexion;
    
    iniciarCliente(&conexion); // Iniciamos el Socket   
    iniciarHilos(&conexion);

}

