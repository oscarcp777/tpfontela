#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>                 // Referencia a la librería
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"



int iniciarHilos(CONEXION *conexion){
	DWORD  threadId;
    HANDLE hThread,hThread1; 	
    hThread = CreateThread( NULL, 0, enviar, conexion, 0, &threadId );
  
	hThread1 = CreateThread( NULL, 0, recibir, conexion, 0, &threadId );

	if(hThread==NULL)
	return RES_THREAD;   
	
	if(hThread1==NULL)
	return RES_THREAD;   
	
	SetThreadPriority(hThread1,1);
	SetThreadPriority(hThread,2);
	


	// wait for the thread to finish 
   WaitForSingleObject( hThread1, INFINITE ); 
	
    printf("\n  EL CLIENTE ESTA DESCONECTADO \n \n");
    //clean up resources used by thread 
    CloseHandle( hThread );
    CloseHandle( hThread1 );

	return RES_OK;	
        

}


void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

	//por default

	char leyenda[25];
	char ip[100];
	char puerto[100];
	
	char* pLeyenda = leyenda;
	char* pIp = ip;
	char* pPuerto = puerto;

	pLeyenda = "CONECTAR CON LA IP (EJ: localhost)";

	//pPuerto = (char*)malloc(sizeof(char)*100);
	
	ingresoMensaje(pIp,pLeyenda);
	
	//printf("IP: %s",pIp);

	pLeyenda="CONECTAR CON EL PUERTO (EJ: 2121)";

	ingresoMensaje(pPuerto,pLeyenda);
 	
	//printf("IP: %s",pIp);
	//printf("puerto: %s",pPuerto);

	
	if (trConectar(pIp,atoi(pPuerto),conexion)==-1){ 
         Sleep(500); // Esperamos 500 Milisegundos y…
         iniciarCliente(conexion); // Repetimos proceso
    }
}









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

