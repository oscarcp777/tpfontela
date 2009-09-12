/*
Codigo C Trabajo Practico 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

const char* version = "Version 1.0 beta \n";
const char* modifiers = "Vh:dbfs";

static struct option long_options[] ={
    {"Version", no_argument,       0, 'V'},
    {"help",    no_argument,       0, 'h'},
    {"delimeter",  required_argument, 0, 'd'},
    {"bytes",   required_argument,       0, 'b'},
    {"field",   required_argument,       0, 'f'},
    {"ignore",   no_argument,       0, 's'},
    {0, 0, 0, 0}
};

struct options_flags{
	int flag_delimeter;
	int flag_bytes;
	int flag_field;
	int flag_ignore;	
    //Si hay un archivo de entrada ifile = 1
	int flag_ifile;
	
	
};

typedef struct options_flags Oflags;

Oflags oflags = {0,0,0,0,0};
int posicionesArchivos[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
char* filename = "";

//Funciones para parsear los parametros
int getOptions(int argc, char** argv,char** ofname);
void help();
void getVersion();

//Funciones para extraccion de caracteres

int listFields(char* fields, char* delimiter);
int listBytes(char* bytes, char* delimiter);

int main(int argc, char** argv){
	char* ofname;
			
	getOptions(argc,argv,&ofname);
   	
        /* 
		char cadena[80];	
		//Copio el archivo para podeer leerlo varias veces
		while(fgets(cadena, 80, stdin) != NULL) { 
			printf("entro por pipe %sn",cadena);
		}*/
		    	
        	if(oflags.flag_delimeter == 1 && oflags.flag_field == 0 ){
                  help();                
                  return EXIT_SUCCESS;
            } 
                         
            if(oflags.flag_delimeter !=0){
                 if(posicionesArchivos[1] == -1){
                    help();
                    return EXIT_SUCCESS;
                 } 
            }
            if(oflags.flag_field != 0){
                    if(oflags.flag_field == 1){                                            
                         printf("parametros de -f %s\n",argv[posicionesArchivos[0]]); 
                         if ( posicionesArchivos[1] != -1)
                               listFields(argv[posicionesArchivos[0]],argv[posicionesArchivos[1]]);
                         else
                               listFields(argv[posicionesArchivos[0]],NULL); 
                    }else{
                         printf("parametros de -f %s\n",argv[posicionesArchivos[1]]); 
                         listFields(argv[posicionesArchivos[1]],argv[posicionesArchivos[0]]);
                         
                    }
                                                       
            }
            else{
                         printf("parametros de -f %s\n",argv[posicionesArchivos[1]]); 
                         listFields(argv[posicionesArchivos[2]],argv[posicionesArchivos[0]]);
            }
	return EXIT_SUCCESS;
}

void help(){
     /*In computing, cut is a Unix command line utility which is used to extract sections from each line of input — usually from a file*/
	printf("The cut utility is used to extract sections from each line of input (usually from a file)\n");
	printf("Usage: \n tp0 -h \n tp0 -V \n tp0 [options] \n");
	//de la wiki Extraction of line segments can typically be done by bytes (-b), characters (-c), or fields (-f) separated by a delimiter (-d — the tab character by default)
	//importante --> by a delimiter (-d — the tab character by default)
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
	
    opterr = 0;
   /* DESCRIPTION getopt_long:
       The  getopt()  function parses the command line arguments.
       Its arguments argc and argv are  the  argument  count  and
       array  as passed to the main() function on program invoca-
       tion.  An element of argv that starts with `-' (and is not
       exactly "-" or "--") is an option element.  The characters
       of this element (aside from the initial  `-')  are  option
       characters.   If getopt() is called repeatedly, it returns
       successively each of the option characters  from  each  of
       the option elements.
       consultar dudas en http://www.cs.duke.edu/courses/spring04/cps108/resources/getoptman.html
       */
    while((c = getopt_long(argc, argv, modifiers,long_options, &option_index)) != EOF){
    	switch (c){
        	case 'V':
        		getVersion();
            	break;
        	case 'h':
        	   	help();
    	   	break;
        	case 'd':
                 if(oflags.flag_bytes != 0 ||  oflags.flag_field != 0)
                    oflags.flag_delimeter = 2;
                 else 
                 oflags.flag_delimeter = 1;
        		//TODO levantar el caracter delimitador y guardarlo en algun lado
        	break;
        	case 'b':
        		if(oflags.flag_delimeter == 1)
                    oflags.flag_bytes = 2;
                else
                    oflags.flag_bytes = 1;
        		
        	break;
        	case 'f':
                 if(oflags.flag_delimeter == 1)
              		oflags.flag_field = 2;
       		    else
       		        oflags.flag_field = 1;
        	break;
        	case 's':
        		oflags.flag_ignore = 1;
        	break;
        	default:
        		help();
        		abort();
    	}

    }    
    //Veo si quedo algun parametro por recoger
    //optind es una variable externa (la utiliza getopt_long), leer link
    //a mi forma de verlo guarda en posicionArchivos la posicion del primer caracter donde comienza la cadena con el nombre del archivo
    if (optind < argc){
    	int j = 0;
    	while (optind < argc && j < 10){
    		oflags.flag_ifile = 1;
    		posicionesArchivos[j]=optind++;
    		j++;
    	}
    }
    
    return 0;
}

int listBytes(char* bytes, char* delimiter){
    printf("ENTRO A listByte\n");
    if(delimiter == NULL){
     //no se definio delimitador, uso el delimitador por defecto TAB
     printf("delimitador por defecto: %s\n",delimiter); 
    }
    else{
    // se definio un delimitador
    printf("delimitador: %s\n",delimiter);   
         
         
    }
    return 0;    
}
int listFields(char* fields, char* delimiter){
    printf("ENTRO A listField\n");
    if(delimiter == NULL){
     //no se definio delimitador, uso el delimitador por defecto TAB
     printf("delimitador por defecto: %s\n",delimiter); 
    }
    else{
    // se definio un delimitador
    printf("delimitador: %s\n",delimiter);   
         
         
    }
    return 0;    
}

/* TODO las siguientes funciones borrarlas, tenes en cuenta su estructura para hacer nuestras funciones
int countWord(char* cadena){
	char* word;
	int count = 0;
	
	word = strtok(cadena, " ");
	while(word != NULL ) {
	    if(word[strlen(word)-1] != '\n' || strlen(word) > 1)
	    	count++;
	    word = strtok( NULL, " ");
	}

	return count;
}

int countBytes(char* cadena){
	int count = 0;

	count = strlen(cadena);
	return count;
}

int fcountBytes(FILE* inputFile){
	char cadena[80];
	int count = 0;

	rewind(inputFile); //Me aseguro que este al principio
	while(fgets(cadena, 80, inputFile) != NULL) { 
		count += countBytes(cadena);
	}
	
	return count;
}

int fcountWord(FILE* inputFile){
	char cadena[80];
	int count = 0;
	
	rewind(inputFile); //Me aseguro que este al principio
	while(fgets(cadena, 80, inputFile) != NULL) { 
		count += countWord(cadena);
	}
	
	return count;
}

int countLines(FILE* inputFile){
	int count = 0;
	char cadena[80];
    
	rewind(inputFile); //Me aseguro que este al principio
	while(fgets(cadena, 80, inputFile) != NULL) { 
		if(cadena[strlen(cadena)-1] == '\n' )
			count++;
	}

	return count;
}*/
