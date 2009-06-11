

#include "transferencia.h"

//#define DEBUG                       //Habilitar para debuggear, muestra printfs
#define PRIMER_ENVIO 15
#define SERVIDOR 0
#define CLIENTE 1


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


void mensajeConexionAceptada(int cliente){

	printf("\n CONEXION ACEPTADA CON EL CLIENTE Nro:   %d \n",cliente);

}

void mensajeClienteDesconectado(){

	printf(" \n EL CLIENTE SE DESCONECTO :  \n");
    printf(" \n EL SERVIDOR ESPERA QUE UN CLIENTE SE CONECTE \n");

}


int iniciarSocket(CONEXION* pConexion, int tipo){

	WSADATA wsdata;

	pConexion->usuario = tipo ; //0 = servidor, 1 = cliente
	if(WSAStartup(MAKEWORD(2,0),&wsdata) == RES_OK){
		pConexion->locsock = socket(AF_INET, SOCK_STREAM, 0); // socket Stream(TCP)

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

	if (listen(pConexion->locsock,2) == RES_ERROR){
		printf("FALLA listen() \n");
		closesocket(pConexion->locsock);
		WSACleanup();
		return RES_LISTEN;
	}

	return RES_OK;



}




int trEscuchar(int puerto,CONEXION *pConexion){

    int error;

	if (pConexion->usuario != 0){
		error = iniciarSocket(pConexion, SERVIDOR);
		if (error != RES_OK)
			return error;

		error = socketEscuchando(puerto,pConexion);
		if (error != RES_OK)
			return error;

		mensajeServidorEnEspera();
	}
	return error;


}

int trAceptar(CONEXION *pConexion){

	SOCKADDR cliente;
	int Longitud_Cliente;
	int clienteDescriptor;

	Longitud_Cliente = sizeof(cliente);
	clienteDescriptor = accept(pConexion->locsock, &cliente, &Longitud_Cliente );

	mensajeConexionAceptada(clienteDescriptor);

	return clienteDescriptor;


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
	if (connect(pConexion->locsock, (SOCKADDR*)&conexrem,
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

			send(pConexion->locsock,(char*)datos,sizeof(char)*strlen((char*)datos),0);

		break;
		case td_int:

			pInt = (int*)datos;

			while( i< cantItems){
				#ifdef DEBUG
					printf("send %d  %d\n",i+1,*pInt);
				#endif
				send(pConexion->locsock,pInt++,sizeof(int),0);
				i++;
			}
			return RES_OK;

		break;
		case td_char:

			pChar = (char*) datos;
			send(pConexion->locsock,pChar,sizeof(char)*strlen(pChar),0);
			return RES_OK;

		break;
		case td_double:

			pDouble = (double*)datos;
			while( i< cantItems){
				#ifdef DEBUG
					printf("send %d  %e \n",i+1,*pDouble);
				#endif
				send(pConexion->locsock,pDouble++,sizeof(double),0);
				i++;
			}
			return RES_OK;

		break;
	}
	return RES_OK;
}


int reconectarSockets(CONEXION *pConexion, int tipo){

	int addrleng;
    addrleng = sizeof(pConexion->conexrem);
///
///	pConexion->cliente = accept(pConexion->locsock, (SOCKADDR*)&(pConexion->conexrem), &addrleng);
///	mensajeConexionAceptada(pConexion);
///	pConexion->usuario = SERVIDOR;
///	return RES_OK;
}



int trRecibir(CONEXION *pConexion, enum tr_tipo_dato tipo, int cantItems, void *datos){

	int i = 1;
	double *pDouble;
	int* pInt;
	int estadorecv=0;


	switch(tipo){

		case td_comando:

			estadorecv=	recv(pConexion->locsock,datos,sizeof(char)*PRIMER_ENVIO,0);

			if(estadorecv==0||estadorecv==-1||(strcmp((char*)datos,"QUIT") == 0)){
   			  if(pConexion->usuario == SERVIDOR){
                    mensajeClienteDesconectado();
    				//reconectarSockets(pConexion, SERVIDOR);
					//recv(pConexion->cliente,datos,sizeof(char)*PRIMER_ENVIO,0);
					return RES_OK;
          	   }
				else return RES_QUIT;

			}
			#ifdef DEBUG
               printf("Primer Recive: %s \n",datos);
			#endif

		break;
		case td_int:

			pInt = (int*)datos;
			#ifdef DEBUG
			   printf("Cantidad de items CASE: %d \n",cantItems);
			#endif
			while( i<= cantItems){
			   recv(pConexion->locsock,pInt,sizeof(int),0);
		       #ifdef DEBUG
                      printf("Dato %d: %d \n",i,*pInt);
               #endif
               pInt++;
               i++;
			}
			return RES_OK;

		break;
		case td_char:

			#ifdef DEBUG
                      printf("Cant Items en td_char %d \n",cantItems);
			#endif
			memset((char*)datos,'\0',(cantItems+1)*sizeof(char));
			recv(pConexion->locsock,(char*)datos,sizeof(char)*cantItems,0);
			return RES_OK;

		break;
		case td_double:

			pDouble = (double*) datos;
			#ifdef DEBUG
			   printf("Cantidad de items CASE: %d \n",cantItems);
			#endif
			while( i<= cantItems){
		       recv(pConexion->locsock,pDouble,sizeof(double),0);
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



int trCerrarConexion(CONEXION *pConexion){

	 closesocket(pConexion->locsock);
	 return RES_OK;
}


int trConexionActiva(CONEXION *pConexion){
    //ESTA funcion devuelve cero si esta activo el sockets sino -1
    int i=  shutdown(pConexion->locsock,1);
    if(i==0){
         printf("LA CONECCION ESTA ACTIVA \n");
    }else{
         printf("LA CONECCION ESTA CERRADA \n");
                   }
	return RES_OK;
}
