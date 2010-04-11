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
#include "../hashExtensible/HashExtensible.h"
using namespace std;

int main() {

	HashExtensible* hash = new HashExtensible();
	hash->create("hash");
	hash->close();

	hash->open("hash");
	hash->close();
	delete hash;
	return 0;

}
