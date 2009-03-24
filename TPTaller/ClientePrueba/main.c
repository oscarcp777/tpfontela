#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"


void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

        if (trConectar("localhost",2121,conexion)==-1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarCliente(conexion); // Repetimos proceso
        }
}


int main(int argc, char *argv[])
{
    CONEXION conexion;
    char msj[100] = "hola";
    int puerto;
	int* pPuerto = &puerto;
	
	
    iniciarCliente(&conexion); // Iniciamos el Socket
    
	trPuerto(&conexion,pPuerto);
	printf("NUMERO PUERTO %d \n", *pPuerto);

	while (strcmp(msj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         scanf("%s",msj);
         send(conexion.locsock,msj,sizeof(msj),0); // Enviamos mensaje
    }
    system("PAUSE");	
}




