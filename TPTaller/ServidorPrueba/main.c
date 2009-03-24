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
    if (iniciarServidor(&conexion)== 0){ 
        do{   
          recv(conexion.locsock,pbuff,sizeof(buffin),0);
          printf("%s \n", pbuff);
        }while(TRUE);    
    }
    system("PAUSE");	
}




