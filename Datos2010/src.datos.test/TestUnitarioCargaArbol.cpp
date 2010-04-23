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

//	string keys="CSDTAMPIBWNGURKEHOLJYQZFXV";
//	char letra={0};
//	char* pLetra = letra;
//	char valor[6]="M";
//	char* pchar=valor;
//	BPlusTree<char> bt(4);
//	for (int i = 0; i<26; i++){
//		memcpy(&letra,keys,sizeof(char));
//		//bt.insert(letra[0],pLetra);
//		bt.insert(numKeys[i],&letra);
//		bt.print(cout);
//		keys++;
//	}


	BPlusTree<int> bt(100);

	string ruta="files/testbt.dat";

	bt.create(ruta,ios::out);


	string a = "Ale";
	string b = "Oscar Caseres";
	string c = "Santiago";
	string d = "Dani";
	string e = "Ricardo Sivori";
	string f = "Sebas";
	string g = "Nelson Castro";
	string h = "Leonel Mes";
	string i = "Carlitos Tevez";
	string j = "Martin Palermo";


	bt.insert(2,a.c_str());
	bt.print(cout);
	bt.insert(4,e.c_str());
//	bt.print(cout);
	bt.insert(1,c.c_str());
//	bt.print(cout);
	bt.insert(5,d.c_str());
//	bt.print(cout);
	bt.insert(3,b.c_str());
//	bt.print(cout);
	bt.insert(32,f.c_str());
//	bt.print(cout);
	bt.insert(33,g.c_str());
	bt.insert(34,h.c_str());
	bt.insert(35,i.c_str());
	bt.insert(37,j.c_str());
//	bt.print(cout);
	bt.print(cout);
	bt.close();

	BPlusTree<int> btAux(100);
	btAux.open(ruta,ios::in|ios::out);

	char* data = btAux.search(33);
	cout << "Encontro el dato: " << data << endl;

	//No lo cierro porque el destructor hace el close
//	BPlusTree<int> btAux(100);
//	btAux.open(ruta,ios::in|ios::out);

	cout<<"El primer elemento es ... " << btAux.getFirstElementSecuentSet()<<endl;
	while(!btAux.getEndSecuentSet()){

		cout<<"El elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
	}

//	cout<<"El Tercer elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Cuarto elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Quinto elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Sexto elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Septimo elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Octavo elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Noveno elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//	cout<<"El Decimo elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
	return 1;
}
