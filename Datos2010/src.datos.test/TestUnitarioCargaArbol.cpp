/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../src.datos.treeB/BPlusTree.h"


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


	BPlusTree<int> bt(64);

	string ruta="files/testbt.dat";

	bt.create(ruta,ios::out);


	string a = "Ale";
	string b = "Oscar";
	string c = "Santiago";
	string d = "Dani";
	string e = "Ricardo Sivori";
	string f = "Sebas";
	string g = "Nelson Castro";
	string h = "Lionel Messi";
	string i = "Carlitos Tevez";
	string j = "Martin Palermo";
	string k = "Medel";
	string l = "Agustin";
	string m = "Torres";
	string n = "Liberty";
	string o = "Don Jones";
	string p = "Puerto Pirata";
	string q = "Los pibes";
	string r = "La academia";
	string s = "River";
	string t = "San Lorenzo";
	string u = "Huracan";
	string v = "Gimnasia";
	string w = "All Boys";
	string x = "Ferro";
	string y = "Chacarita";
	string z = "Chicago";
/*
 * Print inicial ... Se hace para saber cuanto espacio libre tengo
 * en el nodo vacio.
 */
	bt.print(cout);
	bt.insert(2,c.c_str());
//	bt.print(cout);
	bt.insert(1,a.c_str());
//	bt.print(cout);
	bt.insert(3,e.c_str());
//	bt.print(cout);
	bt.insert(4,b.c_str());
//	bt.print(cout);
	bt.insert(5,i.c_str());
//	bt.print(cout);
	bt.insert(6,d.c_str());
//	bt.print(cout);
	bt.insert(8,f.c_str());
//	bt.print(cout);
	bt.insert(10,g.c_str());
//	bt.print(cout);
	bt.insert(7,h.c_str());
//	bt.print(cout);
	bt.insert(9,i.c_str());
//	bt.print(cout);
	bt.insert(11,j.c_str());
	bt.insert(15,k.c_str());
	bt.insert(12,l.c_str());
	bt.insert(13,m.c_str());
	bt.insert(14,n.c_str());
	bt.insert(18,o.c_str());
	bt.insert(16,p.c_str());
	bt.insert(17,q.c_str());
	bt.insert(20,r.c_str());
	bt.insert(47,s.c_str());
	bt.insert(48,t.c_str());
	bt.insert(49,u.c_str());
	bt.insert(50,v.c_str());
	bt.insert(51,w.c_str());
	bt.insert(52,x.c_str());
	bt.insert(53,y.c_str());
	bt.insert(54,z.c_str());
	bt.print(cout);
//cout<< "Elimino la clave 3" <<endl;
//	bt.remover(3);
//	bt.print(cout);
//	bt.insert(3,"Na");
//	bt.print(cout);
//	bt.remover(3);
//	bt.remover(2);
//	bt.print(cout);
//	bt.remover(2);
//	bt.remover(6);
//	bt.remover(74);
//	bt.remover(73);
//	bt.print(cout);
//	bt.remover(72);
//	bt.remover(71);
//	bt.print(cout);
cout<<"Llego bien hasta aca" << endl;
//	bt.remover(55);
//	bt.remover(60);
//	bt.remover(65);
//	bt.remover(70);
//	bt.remover(46);
//	bt.remover(69);
//	bt.remover(47);
//	bt.remover(48);
//	bt.remover(49);

//	cout<<endl<<"ELIMINACION DE CLAVES 1,2,3,4,5,20"<<endl<<endl;

//	bt.remover(2);
//	bt.remover(3);
//	bt.remover(4);
//	bt.remover(20);
//	bt.print(cout);
//	bt.remover(5);
	//bt.print(cout);
//	bt.remover(1);

//	bt.print(cout);


	//bt.print(cout);
	//bt.remover(2,-1);
	//bt.print(cout);
	bt.close();

//	BPlusTree<int> btAux(128);
//	btAux.open(ruta,ios::in|ios::out);

	/*Hay que ver que retorna search porque cuando la
	 * clave a buscar no existe se cuelga.
	 */
//	char* data = btAux.search(2);

//	if(data != NULL){
//		cout << "Encontro el dato: " << data << endl;
//	}else{
//		cout << "No existe el dato." << endl;
//	}


	//No lo cierro porque el destructor hace el close
//	BPlusTree<int> btAux(100);
//	btAux.open(ruta,ios::in|ios::out);


//	if(btAux.getFirstElementSecuentSet()!= NULL){
//
//		cout<<"El primer elemento es ... " << btAux.getFirstElementSecuentSet()<<endl;
//		while(!btAux.getEndSecuentSet()){
//			cout<<"El elemento es ... " << btAux.getNextElementSecuentSet()<<endl;
//		}
//
//	}else{
//			cout << "No existe el dato." << endl;
//	}

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
