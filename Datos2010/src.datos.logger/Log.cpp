
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

	struct option options[] = {
			{"search", 1, NULL, 'B'},
			{"insert", 1, NULL, 'I'},
			{"print", 1, NULL, 'S'},
			{"help", 0, NULL, 'h'},
	};

	while ((result = getopt_long(argc, argv,
			"B:I:S:h", options, &index)) != -1) {
		switch (result) {
			case 'B':
				search(logger,StringUtils::joinStringCmdLine(argc,argv));
				break;
			case 'I':
				insert(logger,StringUtils::joinStringCmdLine(argc,argv));
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

int main(int argc, char * const argv[]){

	Logger* logger = Logger::getUnicaInstancia();
	parse_cmdline(logger,argc,argv);

	std::string cadena = "(12345;nelson ramos aruquipa)";
	ParserInput parser(cadena);
	std::cout << cadena.length()<< std::endl;
	std::cout << parser.getKey() << std::endl;
	std::cout << parser.getData() << std::endl;

	return 0;
}
