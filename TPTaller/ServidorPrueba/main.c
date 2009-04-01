#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librer�a
#include "..\transferencia.h"



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
    char direccion[100];
    char *pdir = direccion; 
	char dato[150];
	char* pDato= dato;
	int i = 0;
	int k = 1;
	int datos[100];
	int* pdatos = datos;
	
	if (iniciarServidor(&conexion)== 0){                          

        while(TRUE){
          memset(datos,0,100);
          trRecibir(&conexion, td_comando,1, pdatos);          
          k = 1;
          while (*pdatos != NULL){
                printf("Dato %d: %d \n",k,*pdatos);
                pdatos++;
                k++;
          }
          pdatos = datos;  	
        }
        
    }

    trConexionActiva(&conexion);//veo si la coneccion esta activa
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




