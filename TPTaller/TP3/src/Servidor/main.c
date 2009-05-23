#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
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




int iniciarServidor(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.
         
           int a = 0;  
			
		   char leyenda[30];
		   char* pLeyenda = leyenda;
		   char puerto[50];

		   pLeyenda = "PUERTO DE CONEXION (EJ: 2121)";

		   ingresoMensaje(puerto,pLeyenda);	

           a = trEscuchar(atoi(puerto),conexion);  
		   
           if ( a == -1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarServidor(conexion); // Repetimos proceso
           }
           else 
                return RES_OK;
        
}


/************************************************************/
/*                                                          */
/*                  MAIN DEL SERVIDOR                       */
/* se conecta el servidor y se levantan los hilos           */
/*                                                          */
/***********************************************************/


int main(int argc, char *argv[])
{  
    
    
    CONEXION conexion;

	
		if (iniciarServidor(&conexion)== 0){       
			 iniciarHilos(&conexion);
	     
		
		}

}
