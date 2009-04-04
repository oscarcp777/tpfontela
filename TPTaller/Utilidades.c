#include <stdio.h>
#include <stdlib.h>
#include <winsock2.h> // Referencia a la librería
#include "transferencia.h"
#include "parser.h"
#include "Utilidades.h"


#define DEBUG







////////////////////AUXILIARES/////////////////////////
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

void iniciarCliente(CONEXION *conexion){ // Procedimiento que iniciara el socket secuencialmente.

    if (trConectar("localhost",2121,conexion)==-1){ 
         Sleep(500); // Esperamos 500 Milisegundos y…
         iniciarCliente(conexion); // Repetimos proceso
    }
}

enum tr_tipo_dato deStringATipoDato(char* cadena){
	
	if (strcmp("INT",cadena)==0)
		return td_int;
	if (strcmp("DOUBLE",cadena)==0)
		return td_double;

	return td_char;
}


void ingresoMensaje(char *pmsj){
     
     printf("INGRESE MENSAJE: (para salir EXIT) \n");   
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
	 
    // parserDestruir(&parser);
	 
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
     
     //parserDestruir(&parser);
     
     
     
		 
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
	
	int aux;
	char prueba[TAM_MSJ];
	char *pPrueba = prueba;
	char direccion[100];
    char *pdir = direccion; 
	

		while(TRUE){
			memset(datos,0,100);
			memset(pPrimerRecibo,0,sizeof(char)*PRIMER_ENVIO);
			memset(pTipoDato,0,sizeof(char)*PRIMER_ENVIO);
			trRecibir(conexion, td_comando,1, pPrimerRecibo);
		 
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
						trRecibir(conexion, td_int ,atoi(pCantidadItems), datosInt);
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
							printf("DATOS CHAR DESPUES DEL MALLOC: %s \n",datosChar);
							trRecibir(conexion, td_char ,atoi(pCantidadItems), pPrueba);
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
						trRecibir(conexion, td_double ,atoi(pCantidadItems), datosDouble);
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


DWORD WINAPI enviar(LPVOID c){


		CONEXION *conexion = (CONEXION*)c;

		char msjIngresado[TAM_MSJ];
		char *pmsjIngresado = msjIngresado;
    
		char primerEnvio[PRIMER_ENVIO];
		char *pPrimerEnvio = primerEnvio;
    
		int puerto;
		int* pPuerto = &puerto;
		int exito;
		

		while (strcmp(pmsjIngresado,"EXIT") != 0){
			ingresoMensaje(pmsjIngresado);
			exito = validarComando(pmsjIngresado);
			if(exito == 0){
				parsearPrimerEnvio(pmsjIngresado,pPrimerEnvio);
				#ifdef DEBUG
					printf("PRIMER ENVIO: %s \n",pPrimerEnvio);
				#endif	 
				trEnviar(conexion,td_comando,1,pPrimerEnvio);
				segundoEnvio(conexion,pmsjIngresado);
			 }       	
		}


}
   