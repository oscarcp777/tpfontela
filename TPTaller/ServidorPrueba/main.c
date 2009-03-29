#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"

char buffin[1024]= "HOLAAA";
char* pbuff = buffin;


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
	int i = 0;
	int vectorEnteros[5];
	int* datos = vectorEnteros;
	
    if (iniciarServidor(&conexion)== 0){                          

        while(TRUE){
          trRecibir(&conexion, td_comando,1, datos);          
				
		}
        
    }

     trConexionActiva(&conexion);//veo si la coneccion esta activa
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




