#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "transferencia.h"
#include "parser.h"
#include "Utilidades.h"



/** esta funcion se espera que un cliente se conecte cuando el cliente 
     deja de mandar informacion o cierra su ventana
*/

int reconectarSockets(CONEXION *pConexion){
    int addrleng;
    	CONEXION* punteroConexion = (CONEXION*) malloc(sizeof(CONEXION));
    		memcpy (punteroConexion, pConexion,sizeof(CONEXION));
    		addrleng = sizeof(punteroConexion->conexrem);
						punteroConexion->socketCliente[0] = accept(punteroConexion->socketServidor, (SOCKADDR*)&(punteroConexion->conexrem), &addrleng);
						printf("CONEXION ACEPTADA CON EL CLIENTE Nro:   %d \n",punteroConexion->socketCliente[0]);
						punteroConexion->usuario=0;//le asigna un 0 que es servidor
						memcpy (pConexion, punteroConexion,sizeof(CONEXION));
                        return RES_OK;// cambiar por RES_OK
     }



/*
int iniciarHilos(CONEXION *conexion){
	DWORD  threadId;
    HANDLE hThread,hThread1; 	
    hThread = CreateThread( NULL, 0, enviar, conexion, 0, &threadId );
  
	hThread1 = CreateThread( NULL, 0, recibir, conexion, 0, &threadId );

	if(hThread==NULL)
	return RES_THREAD;   
	
	if(hThread1==NULL)
	return RES_THREAD;   
	
	SetThreadPriority(hThread1,1);
	SetThreadPriority(hThread,2);
	


	// wait for the thread to finish 
   WaitForSingleObject( hThread1, INFINITE ); 
	
    printf("\n  EL CLIENTE ESTA DESCONECTADO \n \n");
    //clean up resources used by thread 
    CloseHandle( hThread );
    CloseHandle( hThread1 );

	return RES_OK;	
        

}
*/



////////////////////AUXILIARES/////////////////////////

int validarComando(char* cadenaIngresada,CONEXION *conexion){
	
	
	char* resp = NULL;
	char *comando;
	char *datos = NULL;
	char cadenaQuit[4] = "QUIT";
	char *dobleEspacio= NULL;
	char *puntoSeguidoDeEspacio= NULL;
	char *espacioPuntoEspacio= NULL;
	char *espacioSeguidoDePunto= NULL;
	char *cadena = (char*) malloc(sizeof(char)*TAM_MSJ); 

	memset(cadena,0,sizeof(char)*TAM_MSJ);
	memcpy(cadena,cadenaIngresada,sizeof(char)*TAM_MSJ);

	#ifdef DEBUG	
		printf("CADENA %s \n",cadena);
	#endif

	
	if(	strcmp(cadenaIngresada,"\0") !=0){
		comando = strtok(cadena, " " );
		#ifdef DEBUG	
		printf("comando %s \n",comando);
		#endif	
	
		datos = strtok ( NULL, "\n" );
		
		#ifdef DEBUG		
		printf("datos %s \n",datos);	
		#endif		
	
		if(strcmp(comando,"INT") ==0){
			if(datos != NULL){
				resp = strpbrk(datos,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.:;,!¡¿-_+*[]{}´¨°¬#$%&^/=?`~");
				dobleEspacio = strstr(datos,"  ");
			
				if((resp != NULL) |(dobleEspacio != NULL)){
				
					return RES_ERROR;	
				}
				else {
					return RES_OK;
				}
			}
			else return RES_ERROR;
	
		}
		else if (strcmp(comando,"DOUBLE") == 0){
			
			if(datos != NULL){
				//cuando es double pueden haber "." (puntos) asique el punto no esta en la siguiente cadena
				resp = strpbrk(datos,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ:;,!¡¿-_+*[]{}´¨°¬#$%&^/=?`~");
				dobleEspacio = strstr(datos,"  ");
				puntoSeguidoDeEspacio = strstr(datos,". ");
				espacioPuntoEspacio = strstr(datos," . ");
				espacioSeguidoDePunto = strstr(datos," .");
		
				if((resp != NULL) || (dobleEspacio != NULL) || (puntoSeguidoDeEspacio != NULL) || (espacioPuntoEspacio != NULL) || (espacioSeguidoDePunto != NULL)){
				
					return RES_ERROR;	
				}
				else {
					return RES_OK;
				}
			}
			else{
				return RES_ERROR;
			}
	
		}

		else if((strcmp(comando,"QUIT")==0) && (datos==NULL)){
			if(conexion->usuario==1){
				return RES_QUIT;
			}
			else if(conexion->usuario==0){
				cadenaIngresada = cadenaQuit;
				return RES_OK;
			}
			
		  }

		else if(strcmp(comando,"STRING")==0){
				if(datos==NULL){
					return RES_ERROR;
				}
				else{
					return RES_OK;	        
				}
		}

		
		else{
			return RES_ERROR;	
		}
}
	else {
		
		return RES_ERROR;

	}
}
  
  
void crearParser(TDA_Parser *parser){
           
     char archconfig[TAM_NOMBRE_ARCH]="config.txt";
     char *parchconfig=archconfig;
     char archlog[TAM_NOMBRE_ARCH]="log.txt";
	 char *parchlog = archlog;
     int aux;
     strcpy(parchlog,"log.txt");
	 strcpy(parchconfig,"config.txt");
     aux = parserCrear(parser,parchconfig,parchlog);
     #ifdef DEBUG
     if (aux == 1)
           printf("Parser Creado Correctamente\n");
     else
           printf("Error al Crear Parser\n");
     #endif      
}
/*
void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

	//por default

	char leyenda[25];
	char ip[100];
	char puerto[100];
	
	char* pLeyenda = leyenda;
	char* pIp = ip;
	char* pPuerto = puerto;

	pLeyenda = "CONECTAR CON LA IP (EJ: localhost)";

	//pPuerto = (char*)malloc(sizeof(char)*100);
	
	ingresoMensaje(pIp,pLeyenda);
	
	//printf("IP: %s",pIp);

	pLeyenda="CONECTAR CON EL PUERTO (EJ: 2121)";

	ingresoMensaje(pPuerto,pLeyenda);
 	
	//printf("IP: %s",pIp);
	//printf("puerto: %s",pPuerto);

	
	if (trConectar(pIp,atoi(pPuerto),conexion)==-1){ 
         Sleep(500); // Esperamos 500 Milisegundos y…
         iniciarCliente(conexion); // Repetimos proceso
    }
}
*/
enum tr_tipo_dato deStringATipoDato(char* cadena){
	
	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;
}


void ingresoMensaje(char *pmsj,char* leyenda){
     
     printf("%s: \n",leyenda); 
	 gets(pmsj);
}

void parsearPrimerEnvio(char *pmsj,char *pmsj1){
     
     TDA_Parser parser;
          
     
     int numCampos;	
     char cantidadElementos[10];                //Tengo hasta 10 caracteres para representar el numero de datos a enviar
     char* pCantidadElementos = cantidadElementos ;
     char archconfig[TAM_NOMBRE_ARCH];//="config.txt";
     char *parchconfig=archconfig;
     char archlog[TAM_NOMBRE_ARCH];//="log.txt";
	 char *parchlog = archlog;
	 int aux;
	
	 
     strcpy(parchlog,"log.txt");
	 strcpy(parchconfig,"config.txt");
     aux = parserCrear(&parser,parchconfig,parchlog);

     #ifdef DEBUG
     if (aux == 1)
           printf("Parser Creado Correctamente\n");
     else
           printf("Error al Crear Parser\n");
     #endif    
	 
     parserCargarLinea(&parser,pmsj);
			
     numCampos = parserCantCampos(&parser)-1;
	     
	#ifdef DEBUG
        printf("NUM CAMPOS: %d \n",numCampos);
     #endif
     memset(pmsj1,0,sizeof(char)*PRIMER_ENVIO);         
     parserCampo(&parser, 1, pmsj1);
     strcat(pmsj1," ");
	 if ((strstr(pmsj1,"INT") != NULL)||(strstr(pmsj1,"DOUBLE") != NULL))
		 itoa(numCampos,pCantidadElementos,10);
	 
	 else if(strstr(pmsj1,"STRING") != NULL)
		itoa(sizeof(char)*(strlen(pmsj)-strlen(pmsj1)),pCantidadElementos,10);
	 

	 strcat(pmsj1,pCantidadElementos);
	 
     parserDestruir(&parser);
	 
}     

void segundoEnvio(CONEXION *c,char *pmsj){
     
     TDA_Parser parser;
     
     int* datosInt;   //Lo usa si es td_int para cargar los datos
	 double* datosDouble; //Lo usa si es td_double para cargar los datos
     int *datosIntInicio;
     double *datosDoubleInicio;
     char *finalPtr; // Lo usa funcion strtod
     
     int i=2;
	 int k;
     char cadenaaux[1000];
     char *paux = cadenaaux;
     enum tr_tipo_dato tipoDatoaEnviar;
     int cantidadElementos;
     
     char segEnvio[TAM_MSJ]; //Lo usa para hallar el tipo de dato y tambien si es td_char para cargar los datos
     char *pSegundoEnvio = segEnvio;
	      
     crearParser(&parser);
     parserCargarLinea(&parser,pmsj);
     cantidadElementos = parserCantCampos(&parser)-1;
     
     memset(pSegundoEnvio,0,TAM_MSJ);         
     parserCampo(&parser, 1, pSegundoEnvio);  //Obtengo que tipo de dato es
     #ifdef DEBUG
        printf("Linea Original: %s \n",pmsj);
        printf("CAMPO1 (Segundo Envio): %s \n",pSegundoEnvio);
     #endif
     tipoDatoaEnviar = deStringATipoDato(pSegundoEnvio); //Convierte a el enum corresp.
     
     if (tipoDatoaEnviar == td_int){
           #ifdef DEBUG
                  printf("cantidadElementos: %d\n",cantidadElementos);
                  printf("SEGUNDO ENVIO(INT): \n");
           #endif
           datosInt = (int*)malloc(sizeof(int)*cantidadElementos);
           datosIntInicio = datosInt;

		  k = 1;
          while (k<=cantidadElementos){
                  memset(paux,0,sizeof(char)*1000);
                  parserCampo(&parser, i, paux);
                  *datosInt = atoi(paux); 
                  #ifdef DEBUG
                         printf("MAIN CLIENTE%d \n",*datosInt);
                  #endif
                  datosInt++;
                  i++;  
				  k++;
                    
           } 
		     
		   trEnviar(c,tipoDatoaEnviar,cantidadElementos,datosIntInicio);
           free(datosIntInicio);
     }
     
    else if (tipoDatoaEnviar == td_char){
        memset(paux,0,sizeof(char)*10);
        strcpy(paux,pSegundoEnvio);
        #ifdef DEBUG
               printf("CADENAAUX: %s \n",paux);
        #endif
        memset(pSegundoEnvio,0,sizeof(char)*TAM_MSJ);    //Vuelvo a borrar pmsj2 y cargo los datos
        strncpy(pSegundoEnvio,pmsj+strlen(cadenaaux)+1,strlen(pmsj)-strlen(cadenaaux)-1);
        #ifdef DEBUG
		printf("SEGUNDO ENVIO %s \n",pSegundoEnvio);
		#endif
	
        trEnviar(c,tipoDatoaEnviar,cantidadElementos,pSegundoEnvio); 	
     
     } 
	else if (tipoDatoaEnviar == td_double){
           #ifdef DEBUG
                  printf("cantidadElementos: %d\n",cantidadElementos);
                  printf("SEGUNDO ENVIO(DOUBLE): \n");
           #endif
           datosDouble = (double*)malloc(sizeof(double)*cantidadElementos);
           datosDoubleInicio = datosDouble;

		  k = 1;
          while (k<=cantidadElementos){
                  memset(paux,0,sizeof(char)*1000);
                  parserCampo(&parser, i, paux);
                  *datosDouble = strtod(paux,&finalPtr); 
                  #ifdef DEBUG
                         printf("MAIN CLIENTE %e \n",*datosDouble);
                  #endif
                  datosDouble++;
                  i++;  
				  k++;
                    
           } 
		     
		   trEnviar(c,tipoDatoaEnviar,cantidadElementos,datosDoubleInicio);
           free(datosDoubleInicio);
     }
     
     parserDestruir(&parser);
     
     
     
		 
}     

//////////////////////FIN AUXILIARES/////////////////////////

DWORD WINAPI recibir(LPVOID c){
	

	CONEXION *conexion = (CONEXION*)c;


	char msjIngresado[TAM_MSJ];
    char *pmsjIngresado = msjIngresado;

	char primerRecibo[PRIMER_ENVIO];
	char *pPrimerRecibo = primerRecibo;

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
	
//	int aux;
	char prueba[TAM_MSJ];
	char *pPrueba = prueba;
	char direccion[100];
    char *pdir = direccion; 
	int exito;

		while (exito != RES_QUIT){
			memset(datos,0,100);
			memset(pPrimerRecibo,0,sizeof(char)*PRIMER_ENVIO);
			memset(pTipoDato,0,sizeof(char)*PRIMER_ENVIO);

			select (conexion->socketServidor +1, &(conexion->descriptoresLectura), NULL, NULL, NULL);


			if (conexion->usuario==0){
				for (k=0; k<NUMERO_CLIENTES; k++){ 
					if ( FD_ISSET (conexion->socketCliente[k], &(conexion->descriptoresLectura)) )
						conexion->remitente = conexion->socketCliente[k];
				}
			}

			if (trRecibir(conexion, td_comando,1, pPrimerRecibo) == RES_QUIT){
				exito= RES_QUIT;
			    trCerrarConexion(conexion);				  
			
			}
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
				#ifdef VER_COMANDO_ENVIADO
				printf("%s \n",pTipoDato);
				#endif
				
			}
				
			switch (convertirDeStringATipoDato(pTipoDato)){
				
				case td_int:
						datosInt = (int*)malloc(sizeof(int)*atoi(pCantidadItems));
					
						//la siguiente linea es para poder hacer FREE() correctamente, porque datosInt es incrementado
						pDatosIntTemporal = datosInt;
						trRecibir(conexion, td_int ,atoi(pCantidadItems), datosInt);
						k=1;
						printf("Incoming Message..\n");
						while (k <= atoi(pCantidadItems)){
							 printf("%d \n",*datosInt);
							 datosInt++;
							 k++;
						}
						printf("\n");
						free(pDatosIntTemporal);
						break;

				case td_char:
							
							datosChar = (char*) malloc((atoi(pCantidadItems)+1)*sizeof(char));
							trRecibir(conexion, td_char ,atoi(pCantidadItems), datosChar);
											
							printf("Incoming Message..\n%s \n",datosChar);							
							free(datosChar);							
							break;

				case td_double:
						datosDouble = (double*)malloc(sizeof(double)*atoi(pCantidadItems));
					
						//la siguiente linea es para poder hacer FREE() correctamente, porque datosInt es incrementado
						pDatosDoubleTemporal = datosDouble;
						trRecibir(conexion, td_double ,atoi(pCantidadItems), datosDouble);
						k=1;
						printf("Incoming Message..\n");
						while (k <= atoi(pCantidadItems)){
							 printf("%e \n",*datosDouble);
							 datosDouble++;
							 k++;
						}
						printf("\n");
						free(pDatosDoubleTemporal);
				break;
			}
	 
           printf("INGRESE MENSAJE: (para salir QUIT) \n");
        }
		parserDestruir(&parser);	   

}

DWORD WINAPI enviar(LPVOID c){


		CONEXION *conexion = (CONEXION*)c;

		char msjIngresado[TAM_MSJ];
		char *pmsjIngresado = msjIngresado;
    
		char primerEnvio[PRIMER_ENVIO];
		char *pPrimerEnvio = primerEnvio;

		char leyenda[TAM_MSJ];
		char * pLeyenda = leyenda;
    
		int puerto;
		int* pPuerto = &puerto;
		int exito=RES_OK;
		
		while (exito != RES_QUIT){
			pLeyenda = "INGRESE MENSAJE: (para salir QUIT)";
			ingresoMensaje(pmsjIngresado,pLeyenda);
			exito = validarComando(pmsjIngresado,conexion);
	
			if(exito == RES_QUIT){
				if(conexion->usuario==1){
				trCerrarConexion(conexion);
                
				}
			}
			if(exito == RES_OK){
				
				if(strcmp(pmsjIngresado,"QUIT") !=0){

				//si el mensaje no es QUIT que lo parseem sino que lo envie directamente
				parsearPrimerEnvio(pmsjIngresado,pPrimerEnvio);
				#ifdef DEBUG
					printf("PRIMER ENVIO: %s \n",pPrimerEnvio);
				#endif
				trEnviar(conexion,td_comando,1,pPrimerEnvio);
				segundoEnvio(conexion,pmsjIngresado);
				}

				else{					
					trEnviar(conexion,td_comando,1,pmsjIngresado);

				}
				
				
			 }
			else if(exito==RES_ERROR){
				printf("ERROR EN EL COMANDO INGRESADO \n");
			}
           
			
		}
		
}
   