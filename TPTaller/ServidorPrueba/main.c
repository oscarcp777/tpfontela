#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"

#define DEBUG

#define TAM_MSJ 10000                 //Tamaño maximo del mensaje a enviar
#define PRIMER_ENVIO 15      

int iniciarServidor(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.
         
           int a = 0;  
           a = trEscuchar(2121,conexion);                
           if ( a == -1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarServidor(conexion); // Repetimos proceso
           }
           else 
                return a;
        
}



int main(int argc, char *argv[])
{  
    
    
    CONEXION conexion;
    char direccion[100];
    char *pdir = direccion; 


	DWORD  threadId;
    HANDLE hThread,hThread1;
    


	if (iniciarServidor(&conexion)== 0){       

	
    hThread = CreateThread( NULL, 0, enviar, &conexion, 0, &threadId );
	hThread1 = CreateThread( NULL, 0, recibir, &conexion, 0, &threadId );
	SetThreadPriority(hThread,1);
	SetThreadPriority(hThread,2);

    // wait for the thread to finish 
   WaitForSingleObject( hThread, INFINITE ); 
  

    //clean up resources used by thread 
    CloseHandle( hThread );
    CloseHandle( hThread1 );

	
		
        
    }

    trConexionActiva(&conexion);//veo si la coneccion esta activa
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




