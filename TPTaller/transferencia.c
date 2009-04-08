#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> 
#include "transferencia.h"
#include "parser.h"

//#define DEBUG                       //Habilitar para debuggear, muestra printfs
#define PRIMER_ENVIO 15


enum tr_tipo_dato convertirDeStringATipoDato(char* cadena){
	
	
	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;


}
int trRecibir(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, void *datos){

	int i = 1;
//	int *pDatosInt ;
//	char *pDatosChar;
//	float *pDatosFloat;
	double *pDouble;
//	int* puntero;
	int* pInt;
//	float* pInicialFloat;
//	double* pInicialDouble;
	int estadorecv=0;
	
	
	switch(tipo){
	
	case td_comando:
			
			
			estadorecv=	recv(pConexion->cliente,datos,sizeof(char)*PRIMER_ENVIO,0);	
			//printf("el valor de datos es: %s  \n",datos);
			
			if(estadorecv==0||estadorecv==-1||(strcmp((char*)datos,"QUIT") == 0)){
   			  if(pConexion->usuario==0){                     
                                       
    			printf(" \n EL CLIENTE SE DESCONECTO :  \n");
    			printf(" \n EL SERVIDOR ESPERA QUE UN CLIENTE SE CONECTE \n");
		
              reconectarSockets(pConexion);
			  recv(pConexion->cliente,datos,sizeof(char)*PRIMER_ENVIO,0);
			  //el siguiente RES_OK tiene que devolverse si reconectarSockets tuvo exito, sino no
              return RES_OK;              
          	  break;
			 }
			  else if(pConexion->usuario==1){
			  //printf("llego el quit cierra conexcion y devuelve RES_QUIT \n");
              return RES_QUIT;              
          	  break;
			  }

			}	  
		#ifdef DEBUG
               printf("Primer Recive: %s \n",datos);
		#endif
    
		//parserDestruir(&parser);
		

		break;

	case td_int:
		
		pInt = (int*)datos;		
		#ifdef DEBUG
               printf("Cantidad de items CASE: %d \n",cantItems);
		#endif

		while( i<= cantItems){
		       recv(pConexion->cliente,pInt,sizeof(int),0);		
		       #ifdef DEBUG
                      printf("Dato %d: %d \n",i,*pInt);
               #endif
               pInt++;
               i++;
        }
         
       	return RES_OK;
		break;
	
				
	case (td_char):
							
		#ifdef DEBUG
                      printf("Cant Items en td_char %d \n",cantItems);
        #endif	
		
		memset((char*)datos,'\0',(cantItems+1)*sizeof(char));		
		recv(pConexion->cliente,(char*)datos,sizeof(char)*cantItems,0);		
		//TODO validar si salio bien
		return RES_OK;

		break;

					
					
	case (td_double):
		pDouble = (double*) datos;		
		
		#ifdef DEBUG
               printf("Cantidad de items CASE: %d \n",cantItems);
		#endif

		while( i<= cantItems){
		       recv(pConexion->cliente,pDouble,sizeof(double),0);		
		       #ifdef DEBUG
                      printf("Dato %d %e \n",i,*pDouble);
               #endif
               pDouble++;
               i++;
        }
         
       	return RES_OK;		
		break;	
		

	}

return RES_OK;

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
			return RES_INVALID_SOCKET;
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
                       	printf("                     EL SERVIDOR ESTA ESCUCHANDO\n\n");
					    printf("============================================================================== \n");
						/*
                           	* La llamada a la funcion accept  esta variable contiene la longitud de la informacion
	                         * util devuelta en Cliente
	                         */
						addrleng = sizeof(punteroConexion->conexrem);
						punteroConexion->cliente = accept(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), &addrleng);
						printf("\n CONEXION ACEPTADA CON EL CLIENTE Nro:   %d \n",punteroConexion->cliente);
						punteroConexion->usuario=0;//le asigna un 0 que es servidor
						memcpy (pConexion, punteroConexion,sizeof(CONEXION));
                        return RES_OK;// cambiar por RES_OK
					}
					else{
						printf("FALLA listen() \n");
						WSACleanup();
						free(punteroConexion);
						return RES_LISTEN;
					}
			}
			else{
			     	printf("FALLA en bind() \n");
					WSACleanup();
					free(punteroConexion);
					return RES_BIND;
			}		
		
		}	
	
	}
	else{
		printf("FALLA EN WSASTARTUP \n");
		WSACleanup();
		free(punteroConexion);
		return RES_WSA_STARTUP;	
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
		punteroConexion->cliente = socket(AF_INET/* IP V4 */, SOCK_STREAM, 0); // socket Stream(TCP)			
		if (punteroConexion->cliente == INVALID_SOCKET){
			printf("FALLA socket() \n");
			WSACleanup();
			free(punteroConexion);
			return RES_INVALID_SOCKET;
		}
		else{
            punteroConexion->host=gethostbyname(pDireccion); 
            punteroConexion->conexrem.sin_port = htons(Puerto); 
            punteroConexion->conexrem.sin_addr = *((struct in_addr *) punteroConexion->host->h_addr);
            punteroConexion->conexrem.sin_family = AF_INET; 
            memset(punteroConexion->conexrem.sin_zero,0,8); 
			exito = connect(punteroConexion->cliente, (SOCKADDR*)&(punteroConexion->conexrem), sizeof(punteroConexion->conexrem));
		    if(exito == 0){
                    	printf("============================================================================== \n\n");
                       	printf("                         EL CLIENTE SE CONECTO\n\n");
					    printf("============================================================================== \n");
					
                     punteroConexion->usuario=1;//le asigna  un 1 que es cliente
			         memcpy (pConexion, punteroConexion,sizeof(CONEXION)); //si se conecto correctamente devuelvo el puntero a la conexion y RES_OK
					 return RES_OK;// cambiar por RES_OK
			}
			else{
			         printf("FALLA en connect() \n");
					 WSACleanup();
					 free(punteroConexion);
					 return RES_CONNECT;
			}
		}	
	}
    else{
		printf("FALLA EN WSA STARTUP \n");
		WSACleanup();
		free(punteroConexion);
		return RES_WSA_STARTUP;	
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
		return RES_OK;
	}
	else{
	
	//mensaje de error	
	return RES_PORT;
	
	}


}


int trIP(CONEXION *pConexion, char *pIP){
    
    char *paux;
    paux = inet_ntoa(pConexion->conexrem.sin_addr);
    memcpy (pIP, paux,100);
	return RES_OK;
}



int trEnviar(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, const void *datos){

	int i = 0;
	
	
	double *pDouble;
//	int* puntero;
	int* pInt;
	char *pChar;

//	float* pInicialFloat;
//	double* pInicialDouble;
	
	

	switch(tipo){
	
	case td_comando:

	send(pConexion->cliente,(char*)datos,sizeof(char)*strlen((char*)datos),0);	
			
		break;


	case td_int:

		pInt = (int*)datos;
			
		while( i< cantItems){
		    #ifdef DEBUG
				printf("send %d  %d\n",i+1,*pInt);
			#endif
				send(pConexion->cliente,pInt++,sizeof(int),0);	
	       i++;
		}
		
		//TODO validar si salio bien
		return RES_OK;
		break;
	
				
	case (td_char):
		
		pChar = (char*) datos;			
		send(pConexion->cliente,pChar,sizeof(char)*strlen(pChar),0);
		
				
		//TODO validar si salio bien
		return RES_OK;		
		
		break;
		
	case (td_double):
			pDouble = (double*)datos;
			
		while( i< cantItems){
		    #ifdef DEBUG
				printf("send %d  %e \n",i+1,*pDouble);
			#endif	
		    send(pConexion->cliente,pDouble++,sizeof(double),0);	
	        i++;
		}
		
		//TODO validar si salio bien
		return RES_OK;			
		break;	
		

	}
	return RES_OK;
}
int trCerrarConexion(CONEXION *pConexion){
    //cierra el socket del cliente 
    //si es el servidor no hace nada
	 closesocket(pConexion->cliente); 
	 closesocket(pConexion->locsock);  
	 
     return RES_OK;
}


int trConexionActiva(CONEXION *pConexion){
    //ESTA funcion devuelve cero si esta activo el sockets sino -1
  int i=  shutdown(pConexion->cliente,1);
    if(i==0){
         printf("LA CONECCION ESTA ACTIVA \n");
    }else{
         printf("LA CONECCION ESTA CERRADA \n");
                   }  
	return RES_OK;
}
