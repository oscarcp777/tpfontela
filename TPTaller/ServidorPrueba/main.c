#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librer�a
#include <windows.h>
#include "..\transferencia.h"
#include "..\parser.h"
#include "..\Utilidades.h"



int iniciarServidor(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.
         
           int a = 0;  
           a = trEscuchar(2121,conexion);                
           if ( a == -1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y�
                   iniciarServidor(conexion); // Repetimos proceso
           }
           else 
                return a;
        
}



int main(int argc, char *argv[])
{  
    
    
    CONEXION conexion;
	//do{
	
		if (iniciarServidor(&conexion)== 0){       
			 iniciarHilos(&conexion);
	     
		 //reconectarSockets(&conexion);
		}
	//}while(TRUE);

}
