#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> 
#include "transferencia.h"


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
						printf("escuchando correctamente \n");
						addrleng = sizeof(punteroConexion->conexrem);
						punteroConexion->locsock = accept(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), &addrleng);
						printf("CONEXION ACEPTADA \n");
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
		
		while( i< cantItems){
			//pDatoChar = &pDatosChar[i];			
			send(pConexion->locsock,pDatosChar++,sizeof(char),0);		
			i++;
		
		}
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