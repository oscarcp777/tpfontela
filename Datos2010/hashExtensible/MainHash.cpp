/*
 * Main.cpp
 *
 *  Created on: 18/04/2010
 *      Author: richy
 */

#include "HashExtensible.h"
#include "getopt.h"
#include "../src.datos.utils/ParserInput.h"

using namespace std;
static void help(){

	printf("Uso:\n");
	printf(" ./HashExtensible [options]\n");
	printf("Options:\n");
	printf(" 	-B, --search\t   Busca una clave en la estructura.\n");
	printf(" 	-I, --insert\t   Ingresa datos a la estructura.\n");
	printf(" 	-S, --print\t   Vuelca todos los datos de la estructura en un archivo de texto.\n");
	printf(" 	-M, --print\t    Modificar un dato ya existente en la estructura.\n");
	printf(" 	-Q, --print\t    Quitar un dato de la estructura.\n");
}

static void parse_cmdline(int argc, char * const argv[]){

	int index;
	char result;

	struct option options[] = {
			{"search", 1, NULL, 'B'},
			{"insert", 1, NULL, 'I'},
			{"print", 1, NULL, 'S'},
			{"modificar", 1, NULL, 'M'},
			{"quitar", 1, NULL, 'Q'},
			{"help", 0, NULL, 'h'},
	};

	HashExtensible* hash = new  HashExtensible();
	string cadena = argv[1];

	if(hash->isCreated(cadena))
		hash->open(cadena);

	else
		hash->create(cadena);

	ParserInput* parser = new ParserInput(StringUtils::joinStringCmdLine(argc,argv));

	while ((result = getopt_long(argc, argv,"B:I:S:M:Q:h", options, &index)) != -1) {
		switch (result) {
			case 'B':
				cout<<"Resultado de la busqueda: "<<parser->getKey()<<" = "<<hash->search(parser->getKey())<<endl;
				break;
			case 'I':
				if(hash->insert(parser->getKey(),(char*)parser->getData().c_str()))
					cout<<"Se inserto correctamente la clave: "<<parser->getKey()<<endl;
				else
					cout<<"No se pudo insertar la clave: "<<parser->getKey()<<endl;
				break;
			case 'S':
				hash->print(argv[3]);
				break;
			case 'M':
				if(hash->update(parser->getKey(),(char*)parser->getData().c_str()))
					cout<<"Se modifico correctamente la clave: "<<parser->getKey()<<endl;
				else
					cout<<"No se pudo modificar la clave: "<<parser->getKey()<<endl;
				break;
			case 'Q':
				hash->remove(parser->getKey());
//				if(hash->remove(parser->getKey()))
//					cout<<"Se elimino correctamente la clave: "<<parser->getKey()<<endl;
//				else
//					cout<<"No se pudo eliminar la clave: "<<parser->getKey()<<endl;
				break;
			case 'h':
				help();
				break;
			default:
				help();
		}
	}
	delete parser;
	hash->close();
	delete hash;

}

int main(int argc, char * const argv[]){
	parse_cmdline(argc,argv);
	return 0;
}

