#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librer�a
#include "..\transferencia.h"

char buffin[1024]= "HOLAAA";
char* pbuff = buffin;


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
	char dato=10;
	char* pDato= &dato;
	
	if (iniciarServidor(&conexion)== 0){ 
        do{   
          recv(conexion.locsock,pDato,sizeof(char),0);
          printf("%c \n", *pDato);
        }while(*pDato!='d'/*strcmp(pbuff,"EXIT") != 0*/);    
    }

    
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




