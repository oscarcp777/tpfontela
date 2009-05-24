#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h>
#include "transferencia.h"
#include "parser.h"

//#define DEBUG                       //Habilitar para debuggear, muestra printfs
#define PRIMER_ENVIO 15
#define SERVIDOR 0
#define CLIENTE 1

#define NUMERO_CLIENTES 2


enum tr_tipo_dato convertirDeStringATipoDato(char* cadena){


	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;


}


void mensajeServidorEnEspera(){

	 printf("============================================================================== \n\n");
     printf("                     EL SERVIDOR ESTA ESCUCHANDO\n\n");
	 printf("============================================================================== \n");
		
}

void mensajeClienteConectado(){

	 printf("============================================================================== \n\n");
     printf("                         EL CLIENTE SE CONECTO\n\n");
	 printf("============================================================================== \n");
		
}


void mensajeConexionAceptada(CONEXION *pConexion){
	
	printf("\n CONEXION ACEPTADA CON EL CLIENTE Nro:   %d \n",pConexion->cliente);
	
}

void mensajeClienteDesconectado(){

	printf(" \n EL CLIENTE SE DESCONECTO :  \n");
    printf(" \n EL SERVIDOR ESPERA QUE UN CLIENTE SE CONECTE \n");
		
}


int iniciarSocket(CONEXION* pConexion, int tipo){
	
	WSADATA wsdata;
	
	pConexion->usuario = tipo ; //0 = servidor, 1 = cliente
	if(WSAStartup(MAKEWORD(2,0),&wsdata) == RES_OK){
		if (tipo == SERVIDOR)
			pConexion->locsock = socket(AF_INET, SOCK_STREAM, 0); // socket Stream(TCP)			
		else
			pConexion->cliente = socket(AF_INET, SOCK_STREAM, 0); // socket Stream(TCP)			
		if (pConexion->locsock == INVALID_SOCKET){
			printf("FALLA socket() \n");
			WSACleanup();
			return RES_INVALID_SOCKET;
		}
	}
	else{
		printf("FALLA EN WSASTARTUP \n");
		WSACleanup();
		return RES_WSA_STARTUP;	
	}
	return RES_OK;
}


int socketEscuchando(int puerto,CONEXION *pConexion){
	
	struct hostent* host;
	SOCKADDR_IN conexrem;
	int error;

	host = gethostbyname("localhost"); 
	conexrem.sin_port = htons(puerto); 
    conexrem.sin_addr = *((struct in_addr *)host->h_addr);
    conexrem.sin_family = AF_INET; 
    memset(&conexrem.sin_zero,0,8); 
	memcpy(&pConexion->conexrem, &conexrem, sizeof(SOCKADDR_IN));

	error = bind(pConexion->locsock, (SOCKADDR*)&conexrem, sizeof(conexrem));
	if (error != RES_OK){
		printf("FALLA en bind() \n");
		closesocket(pConexion->locsock);
		WSACleanup();
		return RES_BIND;
	}
	
	if (listen(pConexion->locsock,1) == RES_ERROR){
		printf("FALLA listen() \n");
		closesocket(pConexion->locsock);
		WSACleanup();
		return RES_LISTEN;
	}
	
	return RES_OK;

	

}




int trEscuchar(int puerto,CONEXION *pConexion){
	
    int error;
	SOCKADDR cliente;
	int Longitud_Cliente;
	
	error = iniciarSocket(pConexion, SERVIDOR);
	if (error != RES_OK)
		return error;
	
	error = socketEscuchando(puerto,pConexion);	
	if (error != RES_OK)
		return error;	
		

	mensajeServidorEnEspera();
	Longitud_Cliente = sizeof(cliente);
	pConexion->cliente = accept(pConexion->locsock, &cliente, &Longitud_Cliente );
	
	mensajeConexionAceptada(pConexion);
	
	return RES_OK;
					
}



int conectarSocket(const char *pDireccion, int puerto, CONEXION *pConexion){

	struct hostent* host;
	SOCKADDR_IN conexrem;
	
	host=gethostbyname(pDireccion); 
    conexrem.sin_port = htons(puerto); 
    conexrem.sin_addr = *((struct in_addr *)host->h_addr);
    conexrem.sin_family = AF_INET; 
    memset(&conexrem.sin_zero,0,8); 
	
	memcpy(&pConexion->conexrem, &conexrem, sizeof(SOCKADDR_IN));
	if (connect(pConexion->cliente, (SOCKADDR*)&conexrem, 
		sizeof(conexrem)) != RES_OK){
				printf("FALLA en connect() \n");
				WSACleanup();
				return RES_ERROR;
	}

	return RES_OK;

}


int trConectar(const char *pDireccion, int puerto, CONEXION *pConexion){
	
	int error;

	error = iniciarSocket(pConexion, CLIENTE);
	if (error != RES_OK)
		return error;
    
	error = conectarSocket(pDireccion, puerto, pConexion);
	if (error != RES_OK)
		return error;
	
	mensajeClienteConectado();
					
    return RES_OK;
				
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
	else
		return RES_PORT;
	
	

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
	int* pInt;
	char *pChar;


	switch(tipo){
	
		case td_comando:
			if (pConexion->usuario == SERVIDOR){
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


		case td_char:

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

		case td_double:
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
