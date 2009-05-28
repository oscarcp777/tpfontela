#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "transferencia.h"
#include "parser.h"

//#define DEBUG                       //Habilitar para debuggear, muestra printfs
#define PRIMER_ENVIO 15
#define NUMERO_CLIENTES 2


enum tr_tipo_dato convertirDeStringATipoDato(char* cadena){


	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;


}
int trRecibir(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, void *datos){

	int i = 1;
	int k;
	double *pDouble;
	int* pInt;
	int estadorecv = 0;


	

	switch(tipo){

	case td_comando:

			
			if (pConexion->usuario==0)
				estadorecv=	recv(pConexion->remitente,datos,sizeof(char)*PRIMER_ENVIO,0);
			else
				estadorecv=	recv(pConexion->socketCliente[0],datos,sizeof(char)*PRIMER_ENVIO,0);



			if(estadorecv==0||estadorecv==-1||(strcmp((char*)datos,"QUIT") == 0)){
   			  if(pConexion->usuario==0){

    			printf(" \n EL CLIENTE SE DESCONECTO :  \n");
    			printf(" \n EL SERVIDOR ESPERA QUE UN CLIENTE SE CONECTE \n");

              reconectarSockets(pConexion);
			  //recv(remitente,datos,sizeof(char)*PRIMER_ENVIO,0);
			  //recv(pConexion->cliente2,datos,sizeof(char)*PRIMER_ENVIO,0);
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

		       //estadorecv = recv(remitente,pInt,sizeof(int),0);
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
		
		if (pConexion->usuario==0)
				estadorecv = recv(pConexion->remitente,(char*)datos,sizeof(char)*cantItems,0);
		else
				estadorecv = recv(pConexion->socketCliente[0],(char*)datos,sizeof(char)*cantItems,0);
		//TODO validar si salio bien
		return RES_OK;

		break;



	case (td_double):
		pDouble = (double*) datos;

		#ifdef DEBUG
               printf("Cantidad de items CASE: %d \n",cantItems);
		#endif

		while( i<= cantItems){
		      // estadorecv = recv(remitente,pDouble,sizeof(double),0);
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
	int i = 0;
	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
	wasa = WSAStartup(MAKEWORD(2,0),&(punteroConexion->wsdata));
    
	//--------------
	
	while (i<NUMERO_CLIENTES){
		punteroConexion->socketCliente[i] = -1;
		i++;
	}
		


	if(wasa == 0){

		punteroConexion->socketServidor = socket(AF_INET, SOCK_STREAM, 0); // socket Stream(TCP)
	
		if (punteroConexion->socketServidor == INVALID_SOCKET){
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
			 
			 exito = bind(punteroConexion->socketServidor, (SOCKADDR*)&(punteroConexion->conexrem), sizeof(SOCKADDR_IN));

             if(exito == 0){
				int conexionesAceptadas = 0;
				while (conexionesAceptadas < NUMERO_CLIENTES){
			        int escuchaExitosa = listen(punteroConexion->socketServidor,NUMERO_CLIENTES);
					if(escuchaExitosa != -1){
						
  	                    
						printf("================================================================================ \n\n");
                       	printf("                     EL SERVIDOR ESTA ESPERANDO AL JUGADOR %d\n\n",conexionesAceptadas+1);
					    printf("================================================================================ \n");
						
						
						addrleng = sizeof(punteroConexion->conexrem);
						punteroConexion->socketCliente[conexionesAceptadas] = accept(punteroConexion->socketServidor, (SOCKADDR*)&(punteroConexion->conexrem), &addrleng);
						printf("\n CONEXION ACEPTADA CON EL CLIENTE Nro:   %d \n",punteroConexion->socketCliente[conexionesAceptadas]);

						punteroConexion->usuario=0;//le asigna un 0 que es servidor
						memcpy (pConexion, punteroConexion,sizeof(CONEXION));
						conexionesAceptadas++;

					}
					else{
						printf("FALLA listen() \n");
						WSACleanup();
						close(punteroConexion->socketServidor);
						free(punteroConexion);
						return RES_LISTEN;
					}
				}
				FD_ZERO (&(pConexion->descriptoresLectura));
				for (i=0; i<NUMERO_CLIENTES; i++){ 
					FD_SET (punteroConexion->socketCliente[i], &(pConexion->descriptoresLectura) );
				}
				FD_SET (punteroConexion->socketServidor, &(pConexion->descriptoresLectura));
			}
			else{
			     	printf("FALLA en bind() \n");
					WSACleanup();
					close(punteroConexion->socketServidor);
					free(punteroConexion);
					return RES_BIND;
			}
		 return RES_OK;

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
	int i=0;
	
    wasa = WSAStartup(MAKEWORD(2,0),&punteroConexion->wsdata);

	if(wasa == 0){
		punteroConexion->socketCliente[i] = socket(AF_INET, SOCK_STREAM, 0); // socket Stream(TCP)
		if (punteroConexion->socketCliente[i] == INVALID_SOCKET){
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
			
			exito = connect(punteroConexion->socketCliente[i], (SOCKADDR*)&(punteroConexion->conexrem), sizeof(SOCKADDR_IN));
		    
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
					 close(punteroConexion->socketCliente[i]);
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
	double *pDoubleAux;
//	int* puntero;
	int* pInt;
	int* pIntAux;
	char *pChar;
	int k;
//	float* pInicialFloat;
//	double* pInicialDouble;



	switch(tipo){

	case td_comando:
		if (pConexion->usuario==0){
			for (k=0; k<NUMERO_CLIENTES; k++){ 
				send(pConexion->socketCliente[k],(char*)datos,sizeof(char)*strlen((char*)datos),0);
				}
		}else
			send(pConexion->socketCliente[0],(char*)datos,sizeof(char)*strlen((char*)datos),0);
		break;


	case td_int:

		pInt = (int*)datos;
		pIntAux = pInt;
		while( i< cantItems){
		    #ifdef DEBUG
				printf("send %d  %d\n",i+1,*pInt);
			#endif
				if (pConexion->usuario==0){
					for (k=0; k<NUMERO_CLIENTES; k++){ 
						send(pConexion->socketCliente[k],pInt++,sizeof(int),0);
					}
				}else
					send(pConexion->socketCliente[0],pInt++,sizeof(int),0);

	       i++;
		}

		//TODO validar si salio bien
		return RES_OK;
		break;


	case (td_char):

		pChar = (char*) datos;
		if (pConexion->usuario==0){
			for (k=0; k<NUMERO_CLIENTES; k++){ 
				send(pConexion->socketCliente[k],pChar,sizeof(char)*strlen(pChar),0);
			}
		}else
			send(pConexion->socketCliente[0],pChar,sizeof(char)*strlen(pChar),0);

		//TODO validar si salio bien
		return RES_OK;

		break;

	case (td_double):
			pDouble = (double*)datos;
			pDoubleAux = pDouble;
		while( i< cantItems){
		    #ifdef DEBUG
				printf("send %d  %e \n",i+1,*pDouble);
			#endif
			if (pConexion->usuario==0){
				for (k=0; k<NUMERO_CLIENTES; k++){ 
					send(pConexion->socketCliente[k],pDouble++,sizeof(double),0);
				}
			}else
				send(pConexion->socketCliente[0],pDouble++,sizeof(double),0);
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
	 int k; 
	 closesocket(pConexion->socketServidor);
	 for (k=0; k<NUMERO_CLIENTES; k++){ 
					 closesocket(pConexion->socketCliente[k]);
				}

     return RES_OK;
}


int trConexionActiva(CONEXION *pConexion){
    //ESTA funcion devuelve cero si esta activo el sockets sino -1
   int i=  shutdown(pConexion->socketCliente[0],1);
    if(i==0){
         printf("LA CONECCION ESTA ACTIVA \n");
    }else{
         printf("LA CONECCION ESTA CERRADA \n");
                   }
	return RES_OK;
}
