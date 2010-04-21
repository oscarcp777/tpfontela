
#include "Logger.h"
#include "getopt.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.utils/ParserInput.h"

static void search(Logger* logger,string cadena){

	logger->search(cadena);
}

static void insert(Logger* logger, string cadena){

	logger->info(cadena);
}

static void print(Logger* logger,string fileName){

	logger->print(fileName);
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

static void parse_cmdline(Logger* logger,int argc, char * const argv[]){

	int index;
	char result;
	string cadena;

	struct option options[] = {
			{"search", 0, NULL, 'B'},
			{"insert", 0, NULL, 'I'},
			{"print", 1, NULL, 'S'},
			{"help", 0, NULL, 'h'},
	};

	while ((result = getopt_long(argc, argv,
			"BIS:h", options, &index)) != -1) {
		switch (result) {
			case 'B':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0)
						search(logger,cadena);
				}
				break;
			case 'I':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0)
						insert(logger,cadena);
				}
				break;
			case 'S':
				print(logger,optarg);
				break;
			case 'h':
				help();
				break;
			default:
				help();
		}
	}
}

int mainSDS(int argc, char * const argv[]){

	Logger* logger = Logger::getUnicaInstancia();
	parse_cmdline(logger,argc,argv);

	return 0;
}
