//============================================================================
// Name        : Datos2010.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../hashExtensible/HashExtensible.h"
using namespace std;

int main326() {
	HashExtensible* hash = new HashExtensible();
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
//	cout<<"data key: "<<hash->search(56739)<<endl;
//	hash->close();
//	delete hash;

	cout<<hash->open("hash")<<"HOLAAA"<<endl;cout<<"LLEGO 1"<<endl;
//	hash->print(NULL);
//	cout<<"data key: "<<hash->search(11739)<<endl;
//	//hash->remove(86534);

	hash->close();
	cout<<"LLEGO 2"<<endl;
	delete hash;
	cout<<"LLEGO 3"<<endl;
	return 0;

}
