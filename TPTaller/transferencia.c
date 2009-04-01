#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> 
#include "transferencia.h"
#include "parser.h"

//#define DEBUG                       //Habilitar para debuggear, muestra printfs

enum tr_tipo_dato convertirDeStringATipoDato(char* cadena){
	
	
	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;


}
int trRecibir(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, void *datos){

	char* pChar; 
	char cadena[1000];
	int i = 1;
	int *pDatosInt ;
	char *pDatosChar;
	float *pDatosFloat;
	double *pDatosDouble;
	int* puntero;
	int* pInicialInt;
	float* pInicialFloat;
	double* pInicialDouble;
	TDA_Parser parser;
	char archconfig[50]="config.txt";
	char archlog[50]="log.txt";
	char *parchconfig=archconfig;
	char *parchlog = archlog;
	char *pTipoDato;
	char tipoDato[10];
	char *pCantidadItems;
	char cantidadItems[1000];
	
	pTipoDato = tipoDato;
	pCantidadItems = cantidadItems;

	pChar = cadena;	

	switch(tipo){
	
	case td_comando:
			
		memset(pChar,0,sizeof(cadena));
		memset(pTipoDato,0,sizeof(tipoDato));
		//cambiar el *1000
		recv(pConexion->locsock,pChar,sizeof(char)*1000,0);	
		#ifdef DEBUG
               printf("Primer Recive: %s \n",pChar);
		#endif
        parserCrear(&parser,parchconfig,parchlog);
		parserCargarLinea(&parser,pChar);
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
            trRecibir(pConexion, convertirDeStringATipoDato(pTipoDato) ,atoi(pCantidadItems), datos);
			
		}

		parserDestruir(&parser);
		

		break;

	case td_int:
		pDatosInt = (int*)malloc(sizeof(int)*cantItems);
		pInicialInt = pDatosInt;
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialInt = pDatosInt;		
		#ifdef DEBUG
               printf("Cantidad de items CASE: %d \n",cantItems);
		#endif
		while( i<= cantItems){
		       recv(pConexion->locsock,pDatosInt,sizeof(int),0);		
		       #ifdef DEBUG
                      printf("Dato %d: %d \n",i,*pDatosInt);
               #endif
               pDatosInt++;
               i++;
        }
         
        memcpy(datos,pInicialInt,sizeof(int)*cantItems);
		free(pInicialInt);       
		
        //printf("LLEGO BIEN, DATO: %d\n",*(int*)datos);
		//printf("LLEGO BIEN, DATO2: %d\n",*(int*)datos++);
		//TODO validar si salio bien
		return 0;
		break;
	
				
	case (td_char):
		pDatosChar = (char*)malloc(sizeof(char)*cantItems);
				
		recv(pConexion->locsock,pDatosChar,sizeof(char)*cantItems,0);		
		
		memcpy(datos,pDatosChar,sizeof(char)*cantItems);
		free(pDatosChar);
		//TODO validar si salio bien
		return 0;		
		
		break;

					
	case (td_float):
		
		pDatosFloat = (float*)malloc(sizeof(float)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialFloat = pDatosFloat;
				
		while( i< cantItems){			
			recv(pConexion->locsock,pDatosFloat++,sizeof(float),0);		
			i++;
		
		}
		memcpy(datos,pDatosFloat,sizeof(float)*cantItems);
		free(pInicialFloat);
		//TODO validar si salio bien
		return 0;
		break;

					
	case (td_double):
		pDatosDouble = (double*)malloc(sizeof(double)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialDouble = pDatosDouble;
		
		
		while( i< cantItems){
			recv(pConexion->locsock,pDatosDouble++,sizeof(double),0);		
			i++;
		
		}
		memcpy(datos,pDatosDouble,sizeof(double)*cantItems);
		free(pInicialDouble);
		//TODO validar si salio bien
		return 0;			
		break;	
		

	}



}

int trEscuchar(int Puerto,CONEXION *pConexion){
	
    //Definición Variables
    int exito,addrleng;
	int wasa = 0;
	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
    //--------------
	
	wasa = WSAStartup(MAKEWORD(2,0),&(punteroConexion->wsdata));
	
	if(wasa == 0){
		
		punteroConexion->locsock = socket(AF_INET/* IP V4 */, SOCK_STREAM, 0); // socket Stream(TCP)			
		
		if (punteroConexion->locsock == INVALID_SOCKET){
			printf("FALLA socket() \n");
			WSACleanup();
			free(punteroConexion);
			return -1;
		}
		else{

		     punteroConexion->host=gethostbyname("localhost"); 
             punteroConexion->conexrem.sin_port = htons(Puerto); 
             punteroConexion->conexrem.sin_addr = *((struct in_addr *) punteroConexion->host->h_addr);
             punteroConexion->conexrem.sin_family = AF_INET; 
             memset(punteroConexion->conexrem.sin_zero,0,8); 
			 exito = bind(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), sizeof(punteroConexion->conexrem));
			
            if(exito == 0){
			        int escuchaExitosa = listen(punteroConexion->locsock,1); 
					if(escuchaExitosa != -1){
  	                    printf("============================================================================== \n\n");
                       	printf("EL SERVIDOR DE SOMOS LO MAS GROSSO QUE HAY ESTA ESCUCHANDO\n\n");
					    printf("============================================================================== \n");
					
						addrleng = sizeof(punteroConexion->conexrem);
						punteroConexion->locsock = accept(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), &addrleng);
						printf("CONEXION ACEPTADA \n");
						punteroConexion->usuario=0;//le asigna un 0 que es servidor
						memcpy (pConexion, punteroConexion,sizeof(CONEXION));
                        return 0;// cambiar por RES_OK
					}
					else{
						printf("FALLA listen() \n");
						WSACleanup();
						free(punteroConexion);
						return -1;
					}
			}
			else{
			     	printf("FALLA en bind() \n");
					WSACleanup();
					free(punteroConexion);
					return -1;
			}		
		
		}	
	
	}
	else{
		printf("FALLA EN WSASTARTUP \n");
		WSACleanup();
		free(punteroConexion);
		return -1;	
	}


}

int trConectar(const char *pDireccion, int Puerto, CONEXION *pConexion){
	
	//Definición Variables
    int exito;
	int wasa = 0;
	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
    //--------------
    
    wasa = WSAStartup(MAKEWORD(2,0),&punteroConexion->wsdata);
	
	if(wasa == 0){
		punteroConexion->locsock = socket(AF_INET/* IP V4 */, SOCK_STREAM, 0); // socket Stream(TCP)			
		if (punteroConexion->locsock == INVALID_SOCKET){
			printf("FALLA socket() \n");
			WSACleanup();
			free(punteroConexion);
			return -1;
		}
		else{
            punteroConexion->host=gethostbyname(pDireccion); 
            punteroConexion->conexrem.sin_port = htons(Puerto); 
            punteroConexion->conexrem.sin_addr = *((struct in_addr *) punteroConexion->host->h_addr);
            punteroConexion->conexrem.sin_family = AF_INET; 
            memset(punteroConexion->conexrem.sin_zero,0,8); 
			exito = connect(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), sizeof(punteroConexion->conexrem));
		    if(exito == 0){
                    	printf("============================================================================== \n\n");
                       	printf("EL CLIENTE DE  SOMOS LO MAS GROSSO QUE HAY ESTA CONECTADO\n\n");
					    printf("============================================================================== \n");
					
                     punteroConexion->usuario=1;//le asigna  un 1 que es cliente
			         memcpy (pConexion, punteroConexion,sizeof(CONEXION)); //si se conecto correctamente devuelvo el puntero a la conexion y RES_OK
					 return 0;// cambiar por RES_OK
			}
			else{
			         printf("FALLA en connect() \n");
					 WSACleanup();
					 free(punteroConexion);
					 return -1;
			}
		}	
	}
    else{
		printf("FALLA EN WSA STARTUP \n");
		WSACleanup();
		free(punteroConexion);
		return -1;	
	}
}

int trPuerto(CONEXION *pConexion, int *pPuerto){
	
	if(pConexion != NULL){
		
		//Con esta funcion guardaremos el puerto al que vamos a conectar mas adelante.
		//En el protocolo de red los puertos no se expresan igual que los expresamos nosotros
		unsigned short sinPort = pConexion->conexrem.sin_port;
		
		//obtengo el valor real de puerto
		unsigned int puerto = ntohs(sinPort);
			
		
		memcpy(pPuerto, &puerto,sizeof(int));
		
		//TODO verificar si salio bien el memcpy y despues devolver 0
		return 0;
	}
	else{
	
	//mensaje de error	
	return -1;
	
	}


}


int trIP(CONEXION *pConexion, char *pIP){
    
    char *paux;
    paux = inet_ntoa(pConexion->conexrem.sin_addr);
    memcpy (pIP, paux,100);
}



int trEnviar(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, const void *datos){

	int i = 0;
	int *pDatosInt;
	char *pDatosChar;
	float *pDatosFloat;
	double *pDatosDouble;
	int* puntero;
	int* pInicialInt;
	char* pInicialChar;
	float* pInicialFloat;
	double* pInicialDouble;
	
	

	switch(tipo){
	
	case td_comando:

		send(pConexion->locsock,(char*)datos,sizeof(char)*strlen((char*)datos),0);	
		
		break;


	case td_int:

		pDatosInt = (int*)malloc(sizeof(int)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialInt = pDatosInt;
		memcpy(pDatosInt,datos,sizeof(int)*cantItems);
		
		while( i< cantItems){
		       send(pConexion->locsock,pDatosInt++,sizeof(int),0);		
		       i++;
		}
		free(pInicialInt);
		//TODO validar si salio bien
		return 0;
		break;
	
				
	case (td_char):

		pDatosChar = (char*)malloc(sizeof(char)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialChar = pDatosChar;
		memcpy(pDatosChar,datos,sizeof(char)*cantItems);
		
		//while( i< cantItems){
			//pDatoChar = &pDatosChar[i];			
			send(pConexion->locsock,pDatosChar,sizeof(char)*strlen(pDatosChar),0);		
		//	i++;
		
		//}
		free(pInicialChar);
		//TODO validar si salio bien
		return 0;		
		
		break;

					
	case (td_float):
		pDatosFloat = (float*)malloc(sizeof(float)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialFloat = pDatosFloat;
		memcpy(pDatosFloat,datos,sizeof(float)*cantItems);
		
		while( i< cantItems){			
			send(pConexion->locsock,pDatosFloat++,sizeof(float),0);		
			i++;
		
		}
		free(pInicialFloat);
		//TODO validar si salio bien
		return 0;
		break;

					
	case (td_double):
		pDatosDouble = (double*)malloc(sizeof(double)*cantItems);
		//el siguiente puntero es para liberar memoria correctamente porque el otro puntero se incrementa
		pInicialDouble = pDatosDouble;
		memcpy(pDatosDouble,datos,sizeof(double)*cantItems);
		
		while( i< cantItems){
			send(pConexion->locsock,pDatosDouble++,sizeof(double),0);		
			i++;
		
		}
		free(pInicialDouble);
		//TODO validar si salio bien
		return 0;			
		break;	
		

	}
}
int trCerrarConexion(CONEXION *pConexion){
    //por ahora solo cierra la coneccion si es el cliente 
    //si es el servidor no hace nada
    if(pConexion->usuario==1){               
          closesocket(pConexion->locsock);         
         }
      
    return 0;
}

int trConexionActiva(CONEXION *pConexion){
    //ESTA funcion devuelve cero si esta activo el sockets sino -1
  int i=  shutdown(pConexion->locsock,1);
    if(i==0){
         printf("LA CONECCION ESTA ACTIVA \n");
    }else{
         printf("LA CONECCION ESTA CERRADA \n");
                   }  
	return 0;
}
