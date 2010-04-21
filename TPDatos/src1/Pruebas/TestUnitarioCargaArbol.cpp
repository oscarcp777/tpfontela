/*
 * TestUnitarioCargaArbol.cpp
 *
 *  Created on: 28/10/2009
 *      Author: santiago
 */

#include "../Estrategy/IndexadoBSharp.h"

//"CSDAMPIBWNGURKEHOLJYQZFXV"

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



int main(){

	char letra[2] = "";
	//char value[5]="B";
	//char* letraAux=value;
	char valor[5]="C";
	char valorAborrar[5]="M";
	char* pcharAborrar = valorAborrar;
	char valorAborrar2[5]="P";
	char* pcharAborrar2 = valorAborrar2;
	char valorAborrar3[5]="O";
	char* pcharAborrar3 = valorAborrar3;
	char valorAborrar4[5]="L";
	char* pcharAborrar4 = valorAborrar4;
	char valorAborrar5[5]="K";
	char* pcharAborrar5 = valorAborrar5;
	char valorAborrar6[5]="N";
	char* pcharAborrar6 = valorAborrar6;
	char valorAborrar7[5]="B";
	char* pcharAborrar7 = valorAborrar7;
	char valorAborrar8[5]="C";
	char* pcharAborrar8 = valorAborrar8;
	char valorAborrar9[5]="G";
	char* pcharAborrar9 = valorAborrar9;
	char valorAborrar10[5]="F";
	char* pcharAborrar10 = valorAborrar10;
	char valorAborrar11[5]="J";
	char* pcharAborrar11 = valorAborrar11;
	char valorAborrar12[5]="Z";
	char* pcharAborrar12 = valorAborrar12;
	char valorAborrar13[5]="W";
	char* pcharAborrar13 = valorAborrar13;
	char valorAborrar14[5]="S";
	char* pcharAborrar14 = valorAborrar14;
	char valorAborrar15[5]="T";
	char* pcharAborrar15 = valorAborrar15;
	char valorAborrar16[5]="I";
	char* pcharAborrar16 = valorAborrar16;
	char valorAborrar17[5]="Q";
	char* pcharAborrar17 = valorAborrar17;
	char valorAborrar18[5]="V";
	char* pcharAborrar18 = valorAborrar18;
	char valorAborrar19[5]="Y";
	char* pcharAborrar19 = valorAborrar19;
	char valorAborrar20[5]="H";
	char* pcharAborrar20 = valorAborrar20;
	char valorAborrar21[5]="A";
	char* pcharAborrar21 = valorAborrar21;
	char valorAborrar22[5]="R";
	char* pcharAborrar22 = valorAborrar22;
	char valorAborrar23[5]="X";
	char* pcharAborrar23 = valorAborrar23;
	char valorAborrar24[5]="E";
	char* pcharAborrar24 = valorAborrar24;
	char valorAborrar25[5]="X";
	char* pcharAborrar25 = valorAborrar25;
	char valorAborrar26[5]="D";
	char* pcharAborrar26 = valorAborrar26;
	char valorAborrar27[5]="U";
	char* pcharAborrar27 = valorAborrar27;

	char* pchar=valor;
	//IndexadoBSharp bt(bTreeSize,5);
	IndexadoBSharp* bt =new IndexadoBSharp(bTreeSize,1);
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
		//bt->imprimir(cout);
		keys++;

	}

	//bt->remover(letraAux,132);

//	for (int i = 0; i<26; i++){
//
//	}

	//bt->remover(pchar);
	//bt->remover(pcharAborrar2);
//	bt->remover(pcharAborrar7);
//	bt->remover(pcharAborrar);
	bt->remover(pcharAborrar2);
	bt->remover(pcharAborrar3);
	bt->remover(pcharAborrar4);
	bt->remover(pcharAborrar5);
	bt->remover(pcharAborrar6);
	bt->remover(pcharAborrar7);
	bt->remover(pcharAborrar8);
    bt->remover(pcharAborrar9);
	bt->remover(pcharAborrar);
	bt->remover(pcharAborrar10);
	bt->remover(pcharAborrar11);
	bt->remover(pcharAborrar12);
	bt->remover(pcharAborrar13);
	bt->remover(pcharAborrar14);
	bt->remover(pcharAborrar15);
	bt->remover(pcharAborrar16);
	bt->remover(pcharAborrar17);
	bt->remover(pcharAborrar18);
	bt->remover(pcharAborrar19);
	bt->remover(pcharAborrar20);
	bt->remover(pcharAborrar21);
	bt->remover(pcharAborrar22);
	bt->remover(pcharAborrar23);
	bt->remover(pcharAborrar24);
	bt->remover(pcharAborrar25);
	bt->remover(pcharAborrar26);
	bt->remover(pcharAborrar27);

	bt->imprimir(cout);

	bt->cerrar();
//	bt->abrir();
//	int resultado = bt->buscar(pchar);
//	if(resultado == 4)
//		cout<<"BUSQUEDA CORRECTA"<<endl;
//	else
//		cout<<"El resultado dio: "<<resultado<<endl;
//	bt->cerrar();
	delete bt;
	return 1;
}
