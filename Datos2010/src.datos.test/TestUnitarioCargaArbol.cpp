/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../src.datos.treeB+/BPlusTree.h"
//#include "../src.datos.treeB+/BPlusTree.tc"



const char* keys="CSDTAMPIBWNGURKEHOLJYQZFXV";

const int bTreeSize = 4;

int main1234(){

	char letra;
	//char valor[6]="M";
	//char* pchar=valor;
	BPlusTree<char> bt(4);
	//char nArch[]="testbt.dat";
	string ruta="files/testbt.dat";

	bt.create((char*)ruta.c_str(),ios::out);
	bt.open((char*)ruta.c_str(),ios::in|ios::out);


	for (int i = 0; i<2; i++){
		memcpy(&letra,keys,sizeof(char));
		bt.insert(letra,i);
		bt.print(cout);
		keys++;

	}
//	bt.print(cout);
	bt.close();

	//BPlusTree<int> arbol(bTreeSize);

//	BPlusTree<int>* arbol = new BPlusTree<int>(5);
//	delete arbol;
	return 1;
}
