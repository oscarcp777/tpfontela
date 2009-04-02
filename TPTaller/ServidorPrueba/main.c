#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "..\transferencia.h"
#include "..\parser.h"

#define DEBUG

#define TAM_MSJ 10000                 //Tamaño maximo del mensaje a enviar
#define PRIMER_ENVIO 15      

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

	char primerRecibo[PRIMER_ENVIO];
	char *pPrimerRecibo = primerRecibo;

    CONEXION conexion;
    char direccion[100];
    char *pdir = direccion; 
	char dato[150];
	char* pDato= dato;
	int i = 0;
	int k = 1;
	int datos[100];
	int* pdatos = datos;

	TDA_Parser parser;
	char archconfig[50]="config.txt";
	char archlog[50]="log.txt";
	char *parchconfig=archconfig;
	char *parchlog = archlog;
	
	
	char tipoDato[PRIMER_ENVIO];
	char *pTipoDato = tipoDato;
	char cantidadItems[PRIMER_ENVIO];
	char *pCantidadItems = cantidadItems;
	
	char *datosChar;
	int *datosInt,pDatosIntTemporal;
	double *datosDouble;

	
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
			memset(pPrimerRecibo,0,sizeof(char)*PRIMER_ENVIO);
			memset(pTipoDato,0,sizeof(char)*PRIMER_ENVIO);
			trRecibir(&conexion, td_comando,1, pPrimerRecibo);
		 
			parserCrear(&parser,parchconfig,parchlog);
			parserCargarLinea(&parser,pPrimerRecibo);
			#ifdef DEBUG
			       printf("CAMPOS: %d \n",parserCantCampos(&parser));
			#endif
			if(parserCantCampos(&parser) == 2){    //tiene que tener dos "palabras" TIPO_DATO CantItems
				parserCampo(&parser,1,pTipoDato);
				parserCampo(&parser,2,pCantidadItems);
				#ifdef DEBUG
                   printf("pTipoDato: %s \n",pTipoDato);
			       printf("ENUM: %d\n",convertirDeStringATipoDato(pTipoDato));
			       printf("atoi(pCantidadItems) %d \n",atoi(pCantidadItems));
				#endif
				
			}
			switch (convertirDeStringATipoDato(pTipoDato)){
				
				case td_int:
						datosInt = (int*)malloc(sizeof(int)*atoi(pCantidadItems));
						//la siguiente linea es para poder hacer FREE() correctamente, porque datosInt es incrementado
						pDatosIntTemporal = datosInt;
						trRecibir(&conexion, td_int ,atoi(pCantidadItems), datosInt);
						k=1;
						#ifdef DEBUG
						while (k <= atoi(pCantidadItems)){
							 printf("DatoEnMain %d: %d \n",k,*datosInt);
							 datosInt++;
							 k++;
						}
						#endif
						free(pDatosIntTemporal);
				break;
			}
	 
          
        }
        
    }

    trConexionActiva(&conexion);//veo si la coneccion esta activa
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




