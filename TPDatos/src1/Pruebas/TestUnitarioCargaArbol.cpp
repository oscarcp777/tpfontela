/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../Estrategy/IndexadoBSharp.h"



const char* keys="CSDTAMPIBWNGURKEHOLJYQZFXV";



const int bTreeSize = 4;

string a="85689";
string b="85440";
string c="86534";
string d="80000";
string e="86524";
string f="84029";
string g="86531";
string h="86934";
string i="86745";
string j="87890";
string k="79900";



int main4564(){

	char letra[2] = "";
	char valor[5]="A";
	char* pchar=valor;
	//IndexadoBSharp bt(bTreeSize,5);
	IndexadoBSharp* bt =new IndexadoBSharp(bTreeSize,10);
	char nArch[]="testbt.dat";
	char ruta[]="../TPDatos/files/";

	bt->crear(nArch,ruta);
	bt->abrir();

//
//	bt->insertar((char*)a.c_str(),1);
//	bt->imprimir(cout);
//	bt->insertar((char*)b.c_str(),2);
//	bt->imprimir(cout);
//	bt->insertar((char*)c.c_str(),3);
//	bt->imprimir(cout);
//	bt->insertar((char*)d.c_str(),4);
//	bt->imprimir(cout);
//	bt->insertar((char*)e.c_str(),5);
//	bt->imprimir(cout);
//	bt->insertar((char*)f.c_str(),6);
//	bt->imprimir(cout);
//	bt->insertar((char*)g.c_str(),7);
//	bt->imprimir(cout);
//	bt->insertar((char*)h.c_str(),8);
//	bt->imprimir(cout);
//	bt->insertar((char*)i.c_str(),9);
//	bt->imprimir(cout);
//	bt->insertar((char*)j.c_str(),10);
//	bt->insertar((char*)k.c_str(),11);
//
////
//	bt->imprimir(cout);

	for (int i = 0; i<26; i++){
		memcpy(letra,keys,sizeof(char));
		bt->insertar(letra,i);
		bt->imprimir(cout);
		keys++;

	}
	bt->cerrar();
	bt->abrir();
	int resultado = bt->buscar(pchar);
	if(resultado == 4)
		cout<<"BUSQUEDA CORRECTA"<<endl;
	else
		cout<<"El resultado dio: "<<resultado<<endl;
	bt->cerrar();
	delete bt;
	return 1;
}
