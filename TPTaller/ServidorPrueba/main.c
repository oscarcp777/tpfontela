#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"
#define TAM_MSJ 100                 //Tamaño maximo del mensaje a enviar


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
     char msjIngresado[TAM_MSJ];
    char *pmsjIngresado = msjIngresado;
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
/*       
		 printf("esto lo hago para probar que se puede cerrar \n ");
         printf("la coneccion del cliente desde el servidor \n");
         printf("QUIERE CERRAR LA CONECCION : S/N  \n");
		 scanf("%s",msjIngresado);
		trConexionActiva(&conexion);
    if(strcmp(msjIngresado,"S") == 0 || strcmp(msjIngresado,"s") == 0){
         trCerrarConexion(&conexion);     
    } 
    trConexionActiva(&conexion);*/

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




