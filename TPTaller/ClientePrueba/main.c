#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"


void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

        if (trConectar("localhost",2121,conexion)==-1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarCliente(conexion); // Repetimos proceso
        }
}


int main(int argc, char *argv[])
{
    CONEXION conexion;
    char msj[100] = "hola";
    int puerto;
	int* pPuerto = &puerto;
	//int datosInt[5]= {1,555,3,4,5};
	char datosChar[22]= {'T','A','L','L','E','R',' ','D','E',' ','P','R','O','G','R','A','M','A','C','I','O','N'};
	//double datosDouble[5]= {123,4234,234234,234234,3243};
	
	
    iniciarCliente(&conexion); // Iniciamos el Socket
	//trEnviar(&conexion,td_int,5, datosInt);
	trEnviar(&conexion,td_char,22, datosChar);
	//trEnviar(&conexion,td_double,5, datosDouble);
	trConexionActiva(&conexion);//veo si la coneccion esta activa
   	trPuerto(&conexion,pPuerto);
	printf("NUMERO PUERTO %d \n", *pPuerto);
	
	
	/*
	while (strcmp(msj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         scanf("%s",msj);
         send(conexion.locsock,msj,sizeof(msj),0); // Enviamos mensaje
    }*/
    printf("QUIERE CERRAR LA CONECCION : S/N  \n");
      scanf("%s",msj);
      if(strcmp(msj,"S") == 0 || strcmp(msj,"s") == 0){
              
         trCerrarConexion(&conexion);     
          } 
     trConexionActiva(&conexion);//veo si cerro la conecion

    system("PAUSE");	
}




