#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"



int iniciarServidor(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.
         
           int a = 0;  
			
		   char leyenda[30];
		   char* pLeyenda = leyenda;
		   char puerto[50];

		   pLeyenda = "PUERTO DE CONEXION";

		   ingresoMensaje(puerto,pLeyenda);	

           a = trEscuchar(2121,conexion);                
           if ( a == -1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarServidor(conexion); // Repetimos proceso
           }
           else 
                return RES_OK;
        
}



int main(int argc, char *argv[])
{  
    
    
    CONEXION conexion;

	
		if (iniciarServidor(&conexion)== 0){       
			 iniciarHilos(&conexion);
	     
		
		}

}
