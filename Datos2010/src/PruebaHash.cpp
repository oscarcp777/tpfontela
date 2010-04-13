/*
 * PruebaHash.cpp
 *
 *  Created on: 12/04/2010
 *      Author: richy
 */
#include <iostream>
#include <fstream>
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../hashExtensible/HashExtensible.h"
using namespace std;

int main(){
//	HashExtensible* hash = new HashExtensible();
//	hash->create("hash");
//	string cadena = "Oscar Caceres";
//	string cadena2 = "Richard Dubini";
//	string cadena3 = "santy Donikian";
//	string cadena4 = "Nelson Arekipa";
//	string cadena5 = " Daniel Sivori";
//	string cadena6 = " Maja perra";
//	string cadena7 = "PAUCARTAMBO";
//	string cadena8 = "River Plate";
//	string cadena9 = "Facultad Ingenieria";
//	hash->insert(86534,(char*)cadena.c_str());
//	hash->insert(85440,(char*)cadena2.c_str());
//	hash->insert(85789,(char*)cadena3.c_str());
//	hash->insert(82289,(char*)cadena4.c_str());
//	hash->insert(45739,(char*)cadena5.c_str());
//	hash->insert(11739,(char*)cadena6.c_str());
//	hash->insert(56739,(char*)cadena7.c_str());
//	hash->insert(98339,(char*)cadena8.c_str());
//	hash->insert(87345,(char*)cadena9.c_str());
//	hash->print(NULL);
//
//	hash->close();
//	cout<<"DESPUES DEL CLOSE "<<endl;
//	delete hash;

	HashExtensible* hash = new HashExtensible();
	hash->open("hash");
	cout<<"data encontrada : " <<hash->search(85440)<<endl;
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA "<<endl;
	return 0;
}
