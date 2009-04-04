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
	
	char *datosChar = NULL;
	int *datosInt;
	int *pDatosIntTemporal;

	double *datosDouble;
	double *pDatosDoubleTemporal;
	
	int aux;
	char prueba[TAM_MSJ];
	char *pPrueba = prueba;
	
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

				case td_char:
							
							aux = atoi(pCantidadItems);
							datosChar = (char*) malloc(aux*sizeof(char));
							memset(datosChar,0,aux*sizeof(char));
							memset(pPrueba,0,TAM_MSJ);
							//printf("sizeof(char)*(atoi(pCantidadItems) %d \n",aux*sizeof(char));
							printf("DATOS CHAR DESPUES DEL MALLOC: %s \n",datosChar);
							//trRecibir(&conexion, td_char ,atoi(pCantidadItems), datosChar);
							trRecibir(&conexion, td_char ,atoi(pCantidadItems), pPrueba);
							strcat(pPrueba," ");
							memcpy(datosChar,pPrueba,aux*sizeof(char)-1);							
							#ifdef DEBUG
							printf("mensaje recibido pPrueba: %s \n",pPrueba);
							printf("mensaje recibido datosChar: %s \n",datosChar);
							//printf("atoi(pCantidadItems) %d \n",atoi(pCantidadItems));
							#endif
							
							free(datosChar);							
							break;

				case td_double:
						datosDouble = (double*)malloc(sizeof(double)*atoi(pCantidadItems));
					
						//la siguiente linea es para poder hacer FREE() correctamente, porque datosInt es incrementado
						pDatosDoubleTemporal = datosDouble;
						trRecibir(&conexion, td_double ,atoi(pCantidadItems), datosDouble);
						k=1;
						#ifdef DEBUG
						while (k <= atoi(pCantidadItems)){
							 printf("DatoEnMain %d: %e \n",k,*datosDouble);
							 datosDouble++;
							 k++;
						}
						#endif
						free(pDatosDoubleTemporal);
				break;
			}
	 
          
        }
        
    }

    trConexionActiva(&conexion);//veo si la coneccion esta activa
    trIP(&conexion, pdir);   
    printf("DIRECCION: %s \n",pdir);
    system("PAUSE");	
}




