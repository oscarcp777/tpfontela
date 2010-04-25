/*
 * BPlusTree.cpp
 *
 *  Created on: 20/04/2010
 *      Author: nelson ramos
 */

#include "BPlusTree.h"
#include "../src.datos.utils/ParserInput.h"
#include "getopt.h"

using namespace std;
void help(){

	printf("Uso:\n");
	printf(" ./BPlusTree [options]\n");
	printf("Options:\n");
	printf(" 	-B, --search\t   Busca una clave en la estructura.\n");
	printf(" 	-I, --insert\t   Ingresa datos a la estructura.\n");
	printf(" 	-S, --print\t   Vuelca todos los datos de la estructura en un archivo de texto.\n");
	printf(" 	-M, --print\t    Modificar un dato ya existente en la estructura.\n");
	printf(" 	-Q, --print\t    Quitar un dato de la estructura.\n");
}

void parse_cmdline(int argc, char * const argv[], int sizeBlock){

	int index;
	char result;

	struct option options[] = {
			{"search", 0, NULL, 'B'},
			{"insert", 0, NULL, 'I'},
			{"print", 1, NULL, 'S'},
			{"modificar", 0, NULL, 'M'},
			{"quitar", 0, NULL, 'Q'},
			{"help", 0, NULL, 'h'},
	};


	BPlusTree <int>  bTree (sizeBlock);
	bTree.open("./files/ejemplo",ios::in | ios::out);
	string cadena;
	//= argv[1];

	/*
	 * Aca tiene que venir las lineas de codigo que recorren el archivo de
	 * entrada. A madida que leo una linea me va tirando las claves con su valor
	 * y lo parseo con el parser.
	 */
	while ((result = getopt_long(argc, argv,"BISMQh", options, &index)) != -1) {
		switch (result) {
			case 'B':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						ParserInput* parser = new ParserInput(cadena);
						if(bTree.search(parser->getKey())!= NULL){
							cout<<bTree.search(parser->getKey())<< endl;
						}
						delete parser;
					}
				}
				break;
			case 'I':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						ParserInput* parser = new ParserInput(cadena);
						bTree.insert(parser->getKey(),parser->getData().c_str());
						delete parser;
					}
				}

				break;
			case 'S':
				bTree.print(cout);
//				cout<<"Volcado de los datos del arbol en un archivo"<<endl;
				break;
			case 'M':
				cout<<"Modifiacion de un dato del arbol"<<endl;
				break;
			case 'Q':
				cout<<"Quitar una clave del arbol"<<endl;
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

	int sizeBlock = 128;
	parse_cmdline(argc,argv,sizeBlock);
	return 0;
}
