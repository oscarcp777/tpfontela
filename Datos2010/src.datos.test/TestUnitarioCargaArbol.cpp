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

int main(){

	char letra;
	//char valor[6]="M";
	//char* pchar=valor;
	BPlusTree<char> bt(4);
	//char nArch[]="testbt.dat";
	string ruta="files/testbt.dat";

	bt.create(ruta,ios::out);
//	bt.open(ruta,ios::in|ios::out);


	for (int i = 0; i<26; i++){
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
