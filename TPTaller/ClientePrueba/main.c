#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>                 // Referencia a la librería
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"




int main(int argc, char *argv[])
{
    CONEXION conexion;
    
	DWORD  threadId;
    HANDLE hThread,hThread1;
    

    char msjIngresado[TAM_MSJ];
    //char *pmsjIngresado = msjIngresado;
    iniciarCliente(&conexion); // Iniciamos el Socket

   	
	hThread = CreateThread( NULL, 0, enviar, &conexion, 0, &threadId );
	hThread1 = CreateThread( NULL, 0, recibir, &conexion, 0, &threadId );
	SetThreadPriority(hThread,1);
	SetThreadPriority(hThread,2);


	// wait for the thread to finish 
	WaitForSingleObject( hThread, INFINITE ); 
  

    //clean up resources used by thread 
    CloseHandle( hThread );
    CloseHandle( hThread1 );

	
	

    printf("QUIERE CERRAR LA CONECCION : S/N  \n");
    scanf("%s",msjIngresado);
    trConexionActiva(&conexion);
    if(strcmp(msjIngresado,"S") == 0 || strcmp(msjIngresado,"s") == 0){
         trCerrarConexion(&conexion);     
    } 
    trConexionActiva(&conexion);

    system("PAUSE");	
}
