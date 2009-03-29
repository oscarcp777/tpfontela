#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"
#include "..\parser.h"

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
    char *pmsj = msj;
    int puerto;
	int* pPuerto = &puerto;
	//int datosInt[5]= {1,555,3,4,5};
	//double datosDouble[5]= {123,4234,234234,234234,3243};
	TDA_Parser parser;
	char campo1[50];
	char *pcampo1 = campo1;
	char archconfig[50]="config.txt";
	char archlog[50]="log.txt";
	char *parchconfig=archconfig;
	char *parchlog = archlog;
	
	
	if (parserCrear(&parser,parchconfig,parchlog)==1)
           printf("OK\n");
    else
           printf("NOOO\n");
    iniciarCliente(&conexion); // Iniciamos el Socket
	while (strcmp(msj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         gets(msj);
		 printf("MENSAJE INGRESADO: %s \n ",msj);
		 trEnviar(&conexion,td_comando,1,msj);
		 
		 
	}
	
	//trEnviar(&conexion,td_int,5, datosInt);
	//trEnviar(&conexion,td_char,22, datosChar);
	//trEnviar(&conexion,td_double,5, datosDouble);
	trConexionActiva(&conexion);//veo si la coneccion esta activa
   	trPuerto(&conexion,pPuerto);
	printf("NUMERO PUERTO %d \n", *pPuerto);
	
	
	/*
	while (strcmp(pmsj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         gets(pmsj);
         parserCargarLinea(&parser,pmsj);
         printf(" \n");
         printf("NUM CAMPOS: %d",parserCantCampos(&parser));
         memset(pcampo1,0,sizeof(campo1));         
         parserCampo(&parser, 1, pcampo1);
         printf("CAMPO PEDIDO: %s",pcampo1);
         send(conexion.locsock,pcampo1,sizeof(campo1),0); // Enviamos mensaje
    }*/
    parserDestruir(&parser);
    printf("QUIERE CERRAR LA CONECCION : S/N  \n");
      scanf("%s",msj);
      if(strcmp(msj,"S") == 0 || strcmp(msj,"s") == 0){
              
         trCerrarConexion(&conexion);     
          } 
   

    system("PAUSE");	
}




