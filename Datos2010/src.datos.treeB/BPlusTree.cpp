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
	string file;
	file = argv[1];
	int ok = bTree.open(file,ios::in | ios::out);
	std::fstream fileOut;
	if(!ok){

		bTree.create(file,ios::in | ios::out);
	}

	ParserInput* parser = new ParserInput();
	string cadena;

	while ((result = getopt_long(argc, argv,"BIS:MQh", options, &index)) != -1) {
		switch (result){
			case 'B':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						char* search = bTree.search(parser->getKey());
						if(search != NULL){
							cout<<"Resultado de la busqueda: " << parser->getKey() << " = " << search <<endl;
						}else{
							cout<<"La clave no se encuentra en el arbol" << endl;
						}
					}
				}
				break;

			case 'I':
				while(!cin.eof()){
					getline(cin,cadena);
					if(cadena.length() != 0){
						parser->parser(cadena);
						if(bTree.insert(parser->getKey(),(char*)parser->getData().c_str())){
							cout<<"Se inserto correctamente la clave: "<<parser->getKey()<<endl;
						}else{
							cout<<"No se pudo insertar la clave: "<<parser->getKey()<<endl;
						}
					}
				}
				break;

			case 'S':
				fileOut.open(argv[3],ios::in | ios::out);
//				bTree.print("archivoarbol");
				fileOut.close();
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

int mainsdfsd(int argc, char * const argv[]){

	int sizeBlock = 128;
	parse_cmdline(argc,argv,sizeBlock);
	return 0;
}
