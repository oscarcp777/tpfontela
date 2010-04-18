/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../src.datos.treeB+/BPlusTree.h"
using namespace std;


const char* keys="CSDTAMPIBWNGURKEHOLJYQZFXV";


const int bTreeSize = 4;


int main(){
	string keys="CSDTAMPIBWNGURKEHOLJYQZFXV";
	string ruta="files/testbt.dat";
	string::iterator it;
	int numKeys[26] = {3,19,4,20,1,13,16,9,2,23,14,7,21,18,11,5,8,15,12,10,25,17,26,6,24,22};
	BPlusTree<int> bt(80);
	bt.create(ruta,ios::out);

    int count=1;
	for (int i = 0; i<26; i++){
		string str2 = keys.substr(i,1);
		cout<<" Inserto el :"<<str2<<endl;
		bt.insert(numKeys[i],str2.c_str());
		bt.print(cout);
        count++;
	}




	string a = "JAJAJAJAJJA";
	string b = "JOJOOJOJOJO";
	string c = "AAAAAAAAAAA";
	string d = "TATATATATAT";
	string e = "sSSSSSSSSSS";
	string f = "OYYYYYYY";
	string g = "LOLOLOLOLO";
	string h = "MMMMMMMMMM";
	bt.insert(27,a.c_str());
	bt.print(cout);
	bt.insert(28,b.c_str());
	bt.print(cout);
	bt.insert(29,c.c_str());
	bt.print(cout);
	bt.insert(30,d.c_str());
	bt.print(cout);
	bt.insert(31,e.c_str());
	bt.print(cout);
	bt.insert(32,f.c_str());
	bt.print(cout);
	bt.insert(33,g.c_str());
	bt.print(cout);
	bt.insert(34,h.c_str());
	bt.print(cout);
	bt.close();




//	bt.open(ruta,ios::in|ios::out);
//	int dir = bt.search(19,19);
//	cout<<"direccion: " << dir << endl;

	//No lo cierro porque el destructor hace el close
	return 1;
}
