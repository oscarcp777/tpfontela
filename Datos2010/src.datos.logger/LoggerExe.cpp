
#include "stdio.h"
#include "stdlib.h"
#include "Logger.h"
#include "getopt.h"

/*
 * En este metodo podemos buscar, tanto claves como cadenas
 * ya que en el archivo todo es texto plano.
 */
static void search(Logger* logger,string cadena){
	/*
	 * Chequear que el grep no busca numeros enteros.
	 */
	string grep = "grep " + cadena + "</home/nelson/workspace/OrganizacionDeDatos/files/logger";
	system(grep.c_str());
}

//static void insert(Logger* logger, string clave, string cadena){
//
//	logger->info(clave,cadena);
//}

static void insert(Logger* logger, string cadena){

	logger->info("",cadena);
}

static void print(Logger* logger){

	printf("print\n");
}

static void help(){

	printf("Uso:\n");
	printf(" ./logger [options]\n");
	printf("Options:\n");
	printf("	-h, --help\t   Imprime esta información.\n");
	printf(" 	-B, --search\t   Busca una clave o cadena de caracteres.\n");
	printf(" 	-I, --insert\t   Ingresa datos a la estructura.\n");
	printf(" 	-S, --print\t   Vuelca todos los datos de la estructura en un archivo de texto.\n");
}

static void parse_cmdline(Logger* logger,char* cadena,int argc, char * const argv[]){

	int index;
	char result;

	struct option options[] = {
			{"search", 1, NULL, 'B'},
			{"insert", 1, NULL, 'I'},
			{"print", 0, NULL, 'S'},
			{"help", 0, NULL, 'h'},
	};

	while ((result = getopt_long(argc, argv,
			"BISh", options, &index)) != -1) {
		switch (result) {
			case 'B':
				search(logger,cadena);
				break;
			case 'I':
				insert(logger,cadena);
				break;
			case 'S':
				print(logger);
				break;
			case 'h':
				help();
				break;
			default:
				help();
		}
	}
}

int main22222(int argc, char * const argv[]){

	Logger* logger = Logger::getUnicaInstancia();
	char cadena[256];
	FILE* file = fopen("/home/nelson/workspace/OrganizacionDeDatos/files/log","r");
	fgets(cadena,256,file);
	parse_cmdline(logger,cadena,argc,argv);
	fclose(file);
	return 0;
}
