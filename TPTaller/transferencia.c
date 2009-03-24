#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> 


typedef struct _CONEXION{
        WSADATA wsdata;
        struct hostent* host;
        SOCKADDR_IN conexrem;
        SOCKET locsock;
}CONEXION;


int trEscuchar(int puerto,CONEXION *pConexion){
	int exito,addrleng;
	
	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
	

	int wasa = WSAStartup(MAKEWORD(2,0),&punteroConexion->wsdata);
	
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
         
        punteroConexion->conexrem.sin_port = htons(puerto); 

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
									pConexion = punteroConexion; //si se conecto alguien devuelvo el puntero a la conexion y RES_OK
									
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

int trConectar(const char *pDireccion, int puerto, CONEXION *pConexion){
	
	int exito;
	
	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
	

	int wasa = WSAStartup(MAKEWORD(2,0),&punteroConexion->wsdata);
	
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
         
        punteroConexion->conexrem.sin_port = htons(puerto); 

         punteroConexion->conexrem.sin_addr = *((struct in_addr *) punteroConexion->host->h_addr);

         punteroConexion->conexrem.sin_family = AF_INET; 

         memset(punteroConexion->conexrem.sin_zero,0,8); 
			
		 
         exito = connect(punteroConexion->locsock, (SOCKADDR*)&(punteroConexion->conexrem), sizeof(punteroConexion->conexrem));
					
						if(exito == 0){
									
									
									pConexion = punteroConexion; //si se conecto correctamente devuelvo el puntero a la conexion y RES_OK
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

