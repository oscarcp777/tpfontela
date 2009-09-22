/*
Codigo C Trabajo Practico 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

const char* version = "Version 0.1.4 beta \n";
const char* modifiers = "Vhd:b:f:s";

static struct option long_options[] ={
    {"Version", no_argument,       0, 'V'},
    {"help",    no_argument,       0, 'h'},
    {"delimeter",  required_argument, 0, 'd'},
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
int listBytes(char* string);
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
	
	getOptions(argc,argv,&ofname);
		
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
                  listBytes(cadena);	    	
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
    				while(fgets(cadena, 80, inputFile) != NULL) { 
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
                                       listBytes(cadena);	
                           }
                     }
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
	printf("The cut utility is used to extract sections from each line of input (usually from a file)\n");
	printf("Usage: \n tp0 -h \n tp0 -V \n tp0 [options] \n");
	//de la wiki Extraction of line segments can typically be done by bytes (-b), characters (-c), or fields (-f) separated by a delimiter (-d � the tab character by default)
	//importante --> by a delimiter (-d � the tab character by default)
    printf("-V, --version Print version and quit.\n");
	printf("-h, --help Print this information and quit.\n");
	printf("-d, --Use the first character of the specified string as field delimiter instead of tab caracter.\n");
	printf("-b, --LIST specifies byte positions to be extracted.\n");
	printf("-f, --LIST specifies field positions to be extracted.\n");
	printf("-s, --Ignore lines not containing delimiters..\n");
	printf("Example: \n tp0 -b 1 inputl.in");
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
            	break;
        	case 'h':
        	   	help();
    	   	break;
        	case 'd':
                 oflags.flag_delimiter = 1;
                 aux = oflags.p_delimiter;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(char)*10);
                 else
                     help(); 
        	break;
        	case 'b':
                 oflags.flag_bytes = 1;
        		 aux = oflags.p_bytes;
        		 if (optarg != NULL)
                    memcpy(aux,optarg,sizeof(char)*50);
                 else
                     help();  
        	break;
        	case 'f':
                 oflags.flag_field = 1;
        		 aux = oflags.p_field;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(char)*50);
                 else
                    help();      
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

int listBytes(char* string){
    int i = 0;
    int j = 0;
    char* aux;
    char field[50]; 
    memset(field,0,80);
    aux = string;
    
    while (rango[i]!= -5){
          if (rango[i+1] == -1){
             rango[i+1] = -5;
             while (j<rango[i]){
                   j++;
                   aux++;
             }
             aux--;
             strcpy(field,aux);
             printf("%s\n", field);  
          }else
               if (rango[i+1] == -2){
                  rango[i+1] = -5;            
                  while (j<rango[i]){
                   j++;
                   aux++;
                  }
                  aux--;
                   strncpy(field,string,aux-string);
                   printf("%s\n", field);
               }else{
                        while (j<rango[i]){
                              j++;
                              aux++;
                        }
                        aux--;
                        printf("%c\n", *aux); 
                    }
          j = 0; 
          aux = string;         
          i++;
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
    if (tFields == 1)
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
        printf("%s\n", field); 
      
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
