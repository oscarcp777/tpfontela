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

int main() {
	HashExtensible* hash = new HashExtensible();
	hash->create("hash");
	string cadena = "Oscar Caceres";
	string cadena2 = "Richard Dubini";
	string cadena3 = "santy Donikian";
//	string cadena4 = "Nelson Arequipa";
//	string cadena5 = " Daniel Sivori";
	hash->insert(86534,(char*)cadena.c_str());
	hash->insert(85440,(char*)cadena2.c_str());
	hash->insert(85789,(char*)cadena3.c_str());
//	hash->insert(82289,(char*)cadena4.c_str());
//	hash->insert(45739,(char*)cadena5.c_str());

	hash->close();

	hash->open("hash");
	cout<<"data key: "<<hash->search(85789)<<endl;
	hash->remove(86534);
	hash->close();
	return 0;

}
