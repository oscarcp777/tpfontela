/*
Codigo C Trabajo Practico 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>



const char* version = "Version 1.0 beta \n";
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
	char p_bytes[3];
	
    int flag_field;
	char p_field[3];
	
    int flag_ignore;	
    //Si hay un archivo de entrada ifile = 1
	int flag_ifile;
	
	
}Oflags;

Oflags oflags;
int posicionesArchivos[10]={-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
char* filename = "";
int numParameters = 0;

//Funciones para parsear los parametros
int getOptions(int argc, char** argv,char** ofname);
void help();
void getVersion();

//Funciones para extraccion de caracteres

int listFields();
int listBytes();
int validateCommand();
void getField(char* line, int nField, char delimiter, char* field);

int main(int argc, char** argv){
	char* ofname;
	char field[80]; 
	char string[80];	
	int i = 0;

	char delimiterDefault[10]="        ";
	memcpy(oflags.p_delimiter, delimiterDefault, 10);
	
	
	
	getOptions(argc,argv,&ofname);
   	
		

		fgets(string, 80, stdin);   
		printf("Entro por pipe %s\n",string);
        
		
		    if (validateCommand() != EXIT_SUCCESS)
               return -1;	
        
            if(oflags.flag_field != 0){
                    listFields();
                    memset(field,0,80);
                    getField(string, 4,',', field);
                    printf("Campo obtenido: %s\n", field); 
                    return EXIT_SUCCESS;                                                       
            }
            if(oflags.flag_bytes == 1){
                    listBytes();
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
	char *aux;
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
                 oflags.flag_delimiter = 1;
                 aux = oflags.p_delimiter;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(optarg));
                 else
                     help(); 
                 printf("Parametro de d:  %s\n",aux);
                 
        	break;
        	case 'b':
                 oflags.flag_bytes = 1;
        		 aux = oflags.p_bytes;
        		 if (optarg != NULL)
                    memcpy(aux,optarg,sizeof(optarg));
                 else
                     help();  
        		 printf("Parametro de b:  %s\n",aux);
        	break;
        	case 'f':
                 oflags.flag_field = 1;
        		 aux = oflags.p_field;
                 if (optarg != NULL)
                     memcpy(aux,optarg,sizeof(optarg));
                 else
                    help();      
                 printf("Parametro de f:  %s\n",aux); 
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
    	printf ("Nombres Archivos: \n\t");
    	while (optind < argc && j < 10){
    		oflags.flag_ifile = 1;
    		printf("%s\n\t", argv[optind]);
            posicionesArchivos[j]=optind++;
    		j++;
    	}
    	printf("\n");
    	numParameters = j;
    }
    
    return EXIT_SUCCESS;
}

int listBytes(){
    
    return EXIT_SUCCESS;    
}
int listFields(){
    
    return EXIT_SUCCESS;    
}


void getField(char* line, int nField, char delimiter, char* field){
        
        char* lAux;
        char c = delimiter;
        int totalFields = 0;
        lAux = line;
        int i, size;
        char *fBegin , *fEnd;
        
        fBegin = fEnd = line;
        
        while (lAux!=NULL){
              if ((lAux=strchr(++lAux,c))!= NULL) 
              totalFields++; 
        }
        totalFields++;
       
           
        if (totalFields == 1)
          strcpy(field,fBegin);
        else{  
           for(i=0;i<nField;++i){
              fBegin=fEnd;
              fEnd=strchr(fEnd,c); 
              if (fEnd!=NULL) 
                 ++fEnd;
           }
           if (nField==totalFields)
              strcpy(field,fBegin);
           else{
             fEnd--;
             size = (fEnd-fBegin);
             strncpy(field,fBegin,size);
           }
        }
      
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
