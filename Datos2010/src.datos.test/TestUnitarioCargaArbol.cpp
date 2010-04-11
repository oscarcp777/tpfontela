/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../src.datos.treeB+/BPlusTree.h"


const char* keys="CSDTAMPIBWNGURKEHOLJYQZFXV";
int numKeys[26] = {3,19,4,20,1,13,16,9,2,23,14,7,21,18,11,5,8,15,12,10,25,17,26,6,24,22};

const int bTreeSize = 4;

int main(){

	char letra;
	//char valor[6]="M";
	//char* pchar=valor;
	//BPlusTree<char> bt(4);


	BPlusTree<char> bt(512);
	string ruta="files/testbt.dat";

	bt.create(ruta,ios::out);

//	char nombre[10]="santiago";
//	char* pNom = nombre;
	for (int i = 0; i<26; i++){
		memcpy(&letra,keys,sizeof(char));
		bt.insert(letra,&letra);
//		bt.insert(numKeys[i],numKeys[i]);
		bt.print(cout);
//		bt.print(cout);
		keys++;

	}
	bt.print(cout);
	bt.close();




//	bt.open(ruta,ios::in|ios::out);
//	int dir = bt.search(19,19);
//	cout<<"direccion: " << dir << endl;

	//No lo cierro porque el destructor hace el close
	return 1;
}
