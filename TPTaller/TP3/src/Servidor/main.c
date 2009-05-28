#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include <windows.h>

#include "..\parser.h"
#include "..\Utilidades.h"
#include "..\transferencia.h"
#include "Servidor.h"


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




int iniciarServidor(){ // Procedimiento que iniciara el socket secuencialmente.
         
           int a = 0;  
			
		   char leyenda[30];
		   char* pLeyenda = leyenda;
		   char puerto[50];
		   int error = 0;

			pLeyenda = "PUERTO DE CONEXION (EJ: 2121)";
			ingresoMensaje(puerto,pLeyenda);	


			Servidor* s = new Servidor(atoi(puerto), NUMERO_CLIENTES);
			


		   
           
        
}


/************************************************************/
/*                                                          */
/*                  MAIN DEL SERVIDOR                       */
/* se conecta el servidor y se levantan los hilos           */
/*                                                          */
/***********************************************************/


int main(int argc, char *argv[])
{  
    
    
    
		iniciarServidor();

}
