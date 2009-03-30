#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "C:\Users\Richy\Desktop\TP Taller de Programacion\transferencia.h"
#include "C:\Users\Richy\Desktop\TP Taller de Programacion\parser.h"

void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

        if (trConectar("localhost",2121,conexion)==-1){ 
                   Sleep(500); // Esperamos 500 Milisegundos y…
                   iniciarCliente(conexion); // Repetimos proceso
        }
}



enum tr_tipo_dato convertirDeStringATipoDato2(char* cadena){
	
	
	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;
	
	

}


int main(int argc, char *argv[])
{
    CONEXION conexion;
    char msj[100] = "hola";
    char *pmsj = msj;
    int puerto;
	int* pPuerto = &puerto;
	int datosInt[2]= {8,4};
	//double datosDouble[5]= {123,4234,234234,234234,3243};
	TDA_Parser parser;
	char campo1[50];
	char *pcampo1 = campo1;
	char archconfig[50]="config.txt";
	char archlog[50]="log.txt";
	char *parchconfig=archconfig;
	char *parchlog = archlog;
	int numCampos;
	char* pNumCamposEnChar;
	char NumCamposEnChar[10];


	char BORRARPUTO[10];
	char *pBORRAR=BORRARPUTO;
	int* punteroHORRIBLEdatosInt = datosInt;


	pNumCamposEnChar = NumCamposEnChar;
	
	if (parserCrear(&parser,parchconfig,parchlog)==1)
           printf("OK\n");
    else
           printf("NOOO\n");
    iniciarCliente(&conexion); // Iniciamos el Socket
/*	while (strcmp(msj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         gets(msj);
		 printf("MENSAJE INGRESADO: %s \n ",msj);
		 trEnviar(&conexion,td_comando,1,msj);
		 
		 
	}*/
	
	
	
   	trPuerto(&conexion,pPuerto);
	printf("NUMERO PUERTO %d \n", *pPuerto);
	
	
	
	while (strcmp(pmsj,"EXIT") != 0){
         printf("INGRESE MENSAJE: (para salir EXIT) \n");   
         gets(pmsj);
         parserCargarLinea(&parser,pmsj);
         printf(" \n");
		 numCampos = parserCantCampos(&parser)-1;
         printf("NUM CAMPOS: %d \n",numCampos);
         memset(pcampo1,0,sizeof(campo1));         
         parserCampo(&parser, 1, pcampo1);
         memcpy(pBORRAR,pcampo1,sizeof(BORRARPUTO));


		 strcat(pcampo1," ");
		 itoa(numCampos,pNumCamposEnChar,10);

		 strcat(pcampo1,pNumCamposEnChar);
		 printf("CONCATENADAS %s \n",pcampo1);
		 trEnviar(&conexion,td_comando,1,pcampo1);
		 trEnviar(&conexion,convertirDeStringATipoDato2(pBORRAR),numCampos,punteroHORRIBLEdatosInt);
		 	
    }
    parserDestruir(&parser);
    printf("QUIERE CERRAR LA CONECCION : S/N  \n");
      scanf("%s",msj);
      if(strcmp(msj,"S") == 0 || strcmp(msj,"s") == 0){
              
         trCerrarConexion(&conexion);     
          } 
   

    system("PAUSE");	
}




