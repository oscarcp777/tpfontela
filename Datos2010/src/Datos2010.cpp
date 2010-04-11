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
	string cadena = "el hash ya esta, y el arbol???";
//	string cadena2 = "Maja no jodas";
	hash->insert(85440,(char*)cadena.c_str());
//	hash->insert(55443,(char*)cadena2.c_str());
//	hash->insert(854340,(char*)cadena.c_str());
//	hash->insert(25220,(char*)cadena.c_str());
//	hash->insert(81120,(char*)cadena.c_str());
//	hash->insert(85499,(char*)cadena.c_str());
//	hash->insert(75440,(char*)cadena.c_str());
	hash->close();

	return 0;

}
