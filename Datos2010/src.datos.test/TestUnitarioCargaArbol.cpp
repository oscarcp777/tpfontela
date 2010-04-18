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

	char letra={0};
//	char* pLetra = letra;
	//char valor[6]="M";
	//char* pchar=valor;
	//BPlusTree<char> bt(4);


	BPlusTree<int> bt(100);
	string ruta="files/testbt.dat";

	bt.create(ruta,ios::out);

//	char nombre[10]="santiago";
//	char* pNom = nombre;
	for (int i = 0; i<26; i++){
		memcpy(&letra,keys,sizeof(char));
//		bt.insert(letra[0],pLetra);
		bt.insert(numKeys[i],&letra);
		bt.print(cout);
//		keys++;
		keys++;

	}
//	string a = "JAJAJAJAJJA";
//	string b = "JOJOOJOJOJO";
//	string c = "AAAAAAAAAAA";
//	string d = "TATATATATAT";
//	string e = "sSSSSSSSSSS";
//	string f = "OYYYYYYY";
//	string g = "LOLOLOLOLO";
//	string h = "MMMMMMMMMM";
//	bt.insert(27,a.c_str());
//	bt.print(cout);
//	bt.insert(28,b.c_str());
//	bt.print(cout);
//	bt.insert(29,c.c_str());
//	bt.print(cout);
//	bt.insert(30,d.c_str());
//	bt.print(cout);
//	bt.insert(31,e.c_str());
//	bt.print(cout);
//	bt.insert(32,f.c_str());
//	bt.print(cout);
//	bt.insert(33,g.c_str());
//	bt.print(cout);
//	bt.insert(34,h.c_str());
//	bt.print(cout);
	bt.close();




//	bt.open(ruta,ios::in|ios::out);
//	int dir = bt.search(19,19);
//	cout<<"direccion: " << dir << endl;

	//No lo cierro porque el destructor hace el close
	return 1;
}
