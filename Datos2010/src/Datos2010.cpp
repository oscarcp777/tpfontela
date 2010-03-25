//============================================================================
// Name        : Datos2010.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include "../src.datos.storage/TextFile.h"
using namespace std;

int main() {
	TextFile* text= new TextFile();
	text->open("files/texto");
	string datos;
//	text->read(datos);
	text->write("esto es para vos nelson castro 3333");
	text->close();
	cout << "!!!compila  malditos   !!!"<<endl << datos<<endl; // prints !!!Hello World!!!
	return 0;
}
