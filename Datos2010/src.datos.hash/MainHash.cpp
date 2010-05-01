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
	printf(" 	-B =\t   Busca una clave en la estructura.\n");
	printf(" 	-I =\t   Ingresa datos a la estructura.\n");
	printf(" 	-S =\t   Vuelca todos los datos de la estructura en un archivo de texto.\n");
	printf(" 	-M =\t   Modificar un dato ya existente en la estructura.\n");
	printf(" 	-Q =\t   Quitar un dato de la estructura.\n");
	printf("Ejemplos: \n");
	printf(" 	cat archivo_de_claves | ./hash path­NombreArchivo ­-I \n");
	printf(" 	echo \"(clave;)\" | ./hash path­NombreArchivo ­-Q \n");
	printf(" 	./hash path­NombreArchivo -S archivoPrint \n");
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
	ParserInput* parser = new ParserInput();
	string cadena = argv[1];

	while ((result = getopt_long(argc, argv,"BIS:MQh", options, &index)) != -1) {
		switch (result) {
			case 'B':
				if(hash->isCreated(cadena))
					hash->open(cadena);

				else
					hash->create(cadena);
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						cout<<"Resultado de la busqueda: "<<parser->getKey()<<" = "<<hash->search(parser->getKey())<<endl;
					}
				}
				hash->close();
				break;
			case 'I':
				if(hash->isCreated(cadena))
					hash->open(cadena);

				else
					hash->create(cadena);
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						if(hash->insert(parser->getKey(),(char*)parser->getData().c_str()))
							cout<<"Se inserto correctamente la clave: "<<parser->getKey()<<endl;
						else
							cout<<"No se pudo insertar la clave: "<<parser->getKey()<<endl;
					}
				}
				hash->close();
				break;
			case 'S':
				if(hash->isCreated(cadena))
					hash->open(cadena);

				else
					hash->create(cadena);
				hash->print(argv[3]);
				hash->close();
				break;
			case 'M':
				if(hash->isCreated(cadena))
					hash->open(cadena);

				else
					hash->create(cadena);
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						if(hash->update(parser->getKey(),(char*)parser->getData().c_str()))
							cout<<"Se modifico correctamente la clave: "<<parser->getKey()<<endl;
						else
							cout<<"No se pudo modificar la clave: "<<parser->getKey()<<endl;
					}
				}
				hash->close();
				break;
			case 'Q':
				if(hash->isCreated(cadena))
					hash->open(cadena);

				else
					hash->create(cadena);
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						if(hash->remove(parser->getKey()))
							cout<<"Se elimino correctamente la clave: "<<parser->getKey()<<endl;
						else
							cout<<"No se pudo eliminar la clave: "<<parser->getKey()<<endl;

					}
				}
				hash->close();
				break;
			case 'h':
				help();
				break;
			default:
				help();
		}
	}


	delete hash;
	delete parser;

}

int main6546(int argc, char * const argv[]){
	parse_cmdline(argc,argv);
	return 0;
}

