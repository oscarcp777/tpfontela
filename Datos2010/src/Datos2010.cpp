//============================================================================
// Name        : Datos2010.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "../src.datos.logger/Logger.h"
#include "../hashExtensible/Cube.h"
using namespace std;

int main() {
  fstream file;
  METADATA_CUBE reg;
  string nombre= "files/reg";
//  reg.numberOfRecords=12;
//  reg.sizeFree=2400;
//  reg.sizeOfDispersion=8;
//
//            file.open(nombre.c_str(),ios::out|ios::binary);
//            file.close();
  int minimo=PORCENT_FREE_CUBE*SIZE_CUBE;
  cout << "!!!compila  malditos   !!!"<<minimo<<endl;
            file.open(nombre.c_str(),ios::in|ios::out|ios::binary);
            file.read((char*)&reg,sizeof(METADATA_CUBE));
            file.close();

	cout << "!!!compila  malditos   !!!"<<reg.numberOfRecords<<reg.sizeFree<<reg.sizeOfDispersion<<endl;
	return 0;
}
