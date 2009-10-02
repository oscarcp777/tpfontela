/*
Codigo C Trabajo Practico 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

const char* version = "Organizacion de Computadoras - 6620\n\tTP0 - Version 1.0.0 \n Donikian Santiago, Dubini Richard \n";
const char* modifiers = "Vhd:b:f:s";

static struct option long_options[] ={
    {"Version", no_argument,       0, 'V'},
    {"help",    no_argument,       0, 'h'},
    {"delimiter",  required_argument, 0, 'd'},
    {"bytes",   required_argument,       0, 'b'},
    {"field",   required_argument,       0, 'f'},
    {"ignore",   no_argument,       0, 's'},
    {0, 0, 0, 0}
};

typedef struct options_flags{
	int flag_delimiter;
	char p_delimiter[10];

	int flag_bytes;
	char p_bytes[50];

    int flag_field;
	char p_field[50];

    int flag_ignore;
    //Si hay un archivo de entrada ifile = 1
	int flag_ifile;
}Oflags;

Oflags oflags;
int posicionesArchivos[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
int rango[10] = {-5,-5,-5,-5,-5,-5,-5,-5,-5,-5};
char* filename = "";
int numParameters = 0;

//Funciones para parsear los parametros
int getOptions(int argc, char** argv,char** ofname);
int* validateRange(char* datos);

int validateCommand();
int numDigitos( int numero );
int totalFields(char* line,char c);


//Funciones que ejecutan parametros
void help();
void getVersion();
int listFields(char* string);
int listBytes(char* string,FILE* inputFile);
void getField(char* line, int nField, char delimiter, char* field);


int main(int argc, char** argv){
	char* ofname;
	//char field[80];
	char cadena[80]	;
	int i = 0;
	//int k=0;
	FILE* inputFile;

	char delimiterDefault[10]="\t";
	memcpy(oflags.p_delimiter, delimiterDefault, 10);

	if (getOptions(argc,argv,&ofname) != EXIT_SUCCESS)
	   return -1;

	if (validateCommand() != EXIT_SUCCESS)
		return -1;

	if(oflags.flag_ifile == 0){
		fgets(cadena, 80, stdin);

		if(oflags.flag_field != 0){
			if(validateRange(oflags.p_field) == NULL){
				help();
				return -1;
			}else
				listFields(cadena);
		}
		else if(oflags.flag_bytes == 1){
			if(validateRange(oflags.p_bytes) == NULL){
				help();
				return -1;
			}else
				listBytes(cadena,stdin);
		}

	}
	else{
		for(i = 0; i < 10; i++){
			if(posicionesArchivos[i] != -1){
				filename = argv[posicionesArchivos[i]];
				inputFile = fopen(filename, "r");

				if(inputFile == NULL){
					fprintf(stderr, "No se puede abrir el archivo!! %s!\n" ,filename);
					return -1;
				}
				//while(fgets(cadena, 80, inputFile) != NULL) {
					if(oflags.flag_field != 0){
						if(validateRange(oflags.p_field) == NULL){
							help();
							return -1;
						}else
							listFields(cadena);
					}
					else if(oflags.flag_bytes == 1){
						if(validateRange(oflags.p_bytes) == NULL){
							help();
							return -1;
						}else
							listBytes(cadena,inputFile);
					}
				//}
				fclose(inputFile);
			}
		}
	}

	return EXIT_SUCCESS;
}

int validateCommand(){

    	if(oflags.flag_delimiter == 1 && oflags.flag_field == 0 ){
                  help();
                  return -1;
            }

        if(oflags.flag_bytes == 1 && oflags.flag_field == 1 ){
                  help();
                  return -1;
        }

        return EXIT_SUCCESS;
}


void help(){
     /*In computing, cut is a Unix command line utility which is used to extract sections from each line of input � usually from a file*/
	printf("\nThe tp0 utility is used to extract sections from each line of input (usually from a file)\n");
	printf("Usage:  tp0 [-h] [-V] [-f LIST] [-d CHARACTER] [-b LIST] [-s] [files]\n\n");
	//de la wiki Extraction of line segments can typically be done by bytes (-b), characters (-c), or fields (-f) separated by a delimiter (-d � the tab character by default)
	//importante --> by a delimiter (-d � the tab character by default)
    printf("-V, --version \t\tPrint version and quit.\n");
	printf("-h, --help \t\tPrint this information and quit.\n");
	printf("-d, --delimiter \tUse as field delimiter instead of tab character.\n");
	printf("-b, --bytes \t\tSpecifies bytes positions to be extracted. \n ");
	            printf("\tLIST [n,] \tBytes position to be extracted, separated by points\n");
	            printf("\tLIST [n-n] \tExtract bytes in this range\n");
	            printf("\tLIST [n-] \tExtract bytes from this position to the end\n");
	            printf("\tLIST [-n] \tExtract bytes from the beginning to this position\n");
	printf("-f, --field \t\tSpecifies fields positions to be extracted.\n");
                printf("\tLIST [n,] \tFields to be extracted, separated by points\n");
                printf("\tLIST [n-n] \tExtract fields in this range\n");
	            printf("\tLIST [n-] \tExtract from this field to the end\n");
	            printf("\tLIST [-n] \tExtract from the beginning to this field\n");
	printf("-s, --ignore \t\tIgnore lines not containing delimiters\n");
	printf("files \t\t\tFiles to be cutted\n\n");
	printf("Examples: \n\t tp0 -b -3 inputl.in \n\t tp0 -f 1-5 -d . tes.txt");
}

void getVersion(){
	printf("%s",version);
}

int getOptions(int argc, char** argv, char** ofname){
	int option_index = 0;
	int c;
	char *aux;
    opterr = 0;

    while((c = getopt_long(argc, argv, modifiers,long_options, &option_index)) != EOF){

        switch (c){
        	case 'V':
        		getVersion();
        		return -1;
            	break;
        	case 'h':
        	   	help();
        	   	return -1;
    	   	break;
        	case 'd':
                 oflags.flag_delimiter = 1;
                 aux = oflags.p_delimiter;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(char)*10);
                 else{
                     help();
                     return -1;
                 }
        	break;
        	case 'b':
                 oflags.flag_bytes = 1;
        		 aux = oflags.p_bytes;
        		 if (optarg != NULL)
                    memcpy(aux,optarg,sizeof(char)*50);
                 else{
                     help();
                     return -1;
                 }
        	break;
        	case 'f':
                 oflags.flag_field = 1;
        		 aux = oflags.p_field;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(char)*50);
                 else{
                    help();
                    return -1;
                 }
            break;
            case 's':
                 oflags.flag_ignore = 1;
        	break;
        	default:
        		help();
        		abort();
    	}

    }
    if (optind < argc){
    	int j = 0;
    	//printf ("Nombres Archivos: \n\t");
    	while (optind < argc && j < 10){
    		oflags.flag_ifile = 1;
    		//printf("%s\n\t", argv[optind]);
            posicionesArchivos[j]=optind++;
    		j++;
    	}
    	numParameters = j;
    }

    return EXIT_SUCCESS;
}

int listBytes(char* string,FILE* inputFile){
    int i = 0;
    int j = 0;
    char* aux;
    char field[50];
    memset(field,0,50);


    while(fgets(string, 80, inputFile) != NULL) {
    i = 0;
    j = 0;
    memset(field,0,50);
    aux = string;
      while (rango[i]!= -5){
          if (rango[i+1] == -1){

             //si el menor campo pedido es mayor que la cantidad de bytes de la linea no devuelve nada
             if (rango[i] < strlen(string)){

            	 j=1;
            	 while(*aux != '\n'){
            		 printf("%c", *aux);
            		 aux++;

            	 }
             }
          }else
               if (rango[i+1] == -2){
                  //si el mayor campo pedido es mayor que la cantidad de bytes de la linea devuelve
                  //hasta el final de la linea
                  if (rango[i] < strlen(string)){

                	  while (j<rango[i]){
                	   printf("%c", *aux);
                	   j++;
                	   aux++;
                	  }

                  }else{
                	  strcpy(field,aux);
                	  printf("%s", string);
                  }

               }else{
            	   //si el campo pedido es mayor que la cantidad de bytes de la linea no devuelve nada
            	   if (rango[i] < strlen(string)){

            		   while (j<rango[i]){
            			   j++;
            			   aux++;
            		   }
            		   aux--;
            		   printf("%c", *aux);
            	   }

               }
          j = 0;
          aux = string;
          i++;

    }
    printf("\n");
    }

    return EXIT_SUCCESS;
}
int listFields(char* string){

    int i = 0;
    int min = 0;
    int max = 0;
    int tFields;
    int aux;
    char field[80];
    memset(field,0,80);
    tFields = totalFields(string,*(oflags.p_delimiter));
    if (tFields == 1 && oflags.flag_ignore)
       return EXIT_SUCCESS;

    while (rango[i]!= -5){
          if (rango[i+1] == -2){
             aux = rango[i];
             rango[i+1] = -5;
             min = 1;
          }else
               if (rango[i+1] == -1){
                  rango[i+1] = -5;
                  aux = rango[i];
                  max = 1;
               }else
                    getField(string, rango[i],*(oflags.p_delimiter), field);
          i++;
    }
    if (min)
       for (i=1;i<=aux;i++){
            memset(field,0,80);
            getField(string, i,*(oflags.p_delimiter), field);
       }
    if (max){
       for (i=aux;i<=tFields;i++){
            memset(field,0,80);
            getField(string, i,*(oflags.p_delimiter), field);
       }
    }
    return EXIT_SUCCESS;
}
int totalFields(char* line,char c) {
        char* lAux;
        int total = 0;
        lAux = line;

        while (lAux!=NULL){
              if ((lAux=strchr(++lAux,c))!= NULL)
              total++;
        }
        total++;
        return total;
}

void getField(char* line, int nField, char delimiter, char* field){

       // char* lAux;
        char c = delimiter;
        int tFields = 0;
        int i, size;
        char *fBegin , *fEnd;

        fBegin = fEnd = line;

        tFields = totalFields(line, delimiter);

        if (tFields == 1)
        	strcpy(field,fBegin);
        else{
              //printf("nField: %d", nField );
              //printf("tfields: %d", tFields);
        	if (nField>tFields)
        		memset(field,0,10);
        	else{
        		for(i=0;i<nField;++i){
        			fBegin=fEnd;
        			fEnd=strchr(fEnd,c);
        			if (fEnd!=NULL)
        				++fEnd;
        		}
        		if (nField==tFields)
        			strcpy(field,fBegin);
        		else{
        			fEnd--;
        			size = (fEnd-fBegin);
        			strncpy(field,fBegin,size);
        		}
        	}
        }
        printf("%s", field);
        if (nField < tFields)
        	printf("%c",delimiter);

}


int numDigitos( int numero ){
    int cuentaDigitos = 0;
    while ( numero ) {
          ++cuentaDigitos;
          numero /= 10;
    }
    return cuentaDigitos;
}


int* validateRange(char* datos){

      char* pDatos;
      int i = 0;
      int aux1;
      int aux2;
      int iInicial;
      int diferencia;
      int digitos;

    if(strpbrk(datos,"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.:;!��?_+*[]{}����#$%&^/=`~") != NULL){
		 printf("tiene caracteres incorrectos \n");
        return NULL;
	}
	else{
         pDatos = datos;

         while(*pDatos != '\0'){

               if(i==0){
               //si es el primer caracter leido
                     if(*pDatos == '-'){
                                //si es un guion, ej -5 pongo en el vector 5,-2
                                rango[i+1]= -2;
                                pDatos++;
                                rango[i]= atoi(pDatos);
                                digitos = numDigitos(rango[i]);
                                while(digitos){
                                  pDatos++;
                                 digitos--;
                                }
                                i+=2;
                     }
                     else if(*pDatos == ','){
                          //no puede empezar con una "," ERROR
                          return NULL;
                     }
                     else{
                          //si es un numero
                          rango[i] = atoi(pDatos);
                          digitos = numDigitos(rango[i]);
                          while(digitos){
                              pDatos++;
                              digitos--;
                          }
                          i++;
                     }
               }
               else{
                    //si no es el primer caracter
                    if(*pDatos == '-'){
                               pDatos++;
                                if(*pDatos == '\0'){
                                   //si es un guion y le sigue un \0, ej 5- pongo 5,-1
                                   rango[i]= -1;
                                   i++;
                                }
                                else if(*pDatos == ','){
                                     //no puede empezar con una "," ERROR
                                     return NULL;
                                }
                                else{
                                   //si es un guion y le sigue un numero, ej 2-5 pongo 2,3,4,5 pero si el primero es mayor al segundo es un ERROR  (ej 5-2)
                                     aux1 = rango[i-1];// ultimo numero guardado
                                     aux2 = atoi(pDatos);//obtengo el siguiente despues del "-"

                                     if(aux2<=aux1)//es un error(ej 5-2)
                                           return NULL;
                                     else{
                                        iInicial = i;
                                        diferencia = aux2-aux1;
                                        //for(i;i<iInicial+diferencia;i++)
                                        while(i<iInicial+diferencia){
                                               aux1++;
                                               rango[i]= aux1;//guardo el siguiente en el ejemplo de 2-5 seria el 3
                                               i++;
                                        }
                                        digitos = numDigitos(aux1);
                                        while(digitos){
                                              pDatos++;
                                              digitos--;
                                        }
                                     }
                                }
                     }
                     else if(*pDatos == ','){
                           pDatos++;
                           if( (*pDatos == ',') || (*pDatos == ' ') || (*pDatos == '-') )
                               return NULL;
                           else{
                                //si es un numero
                                rango[i] = atoi(pDatos);
                                digitos = numDigitos(rango[i]);
                                while(digitos){
                                     pDatos++;
                                     digitos--;
                                }
                                i++;
                           }
                     }
                     else{
                          //si es un numero
                          rango[i] = atoi(pDatos);
                          digitos = numDigitos(rango[i]);
                          while(digitos){
                               pDatos++;
                               digitos--;
                          }
                          i++;
                     }
                    }
          }
		 return rango;
		}

}
