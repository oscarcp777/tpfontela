/*
 * TestBTree.cpp
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#include "TestBTree.h"

TestBTree::TestBTree() {
}

TestBTree::~TestBTree() {
}

/**
 * Test que evalúa el método insert del BTree, crea un nuevo árbol y le ingresa una serie de datos
 * preparados para que su resultante en los nodos hojas quede ordenado alfabéticamente, también
 * valida ingresos de igual clave, e ingresos con datos que superan el máximo permitido para un
 * tamaño de bloque dado
 * En caso de querer ingresar mas elementos usar claves como por ejemplo BB o FD y usar alguna clave
 * libre que corresponda a su orden alfabético
 *
 * @param fileName nombre del archivo a ser creado
 * @param blockSize tamaño de bloque del archivo
 */
void TestBTree::runTestInsert(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	bt.create(fileName,ios::out);

	try{
	//Con este conjunto de datos el secuence set tiene que quedar ordenado alfabeticamente
	bt.insert(42,"N--------N");
	bt.insert(66,"V------V");
	bt.insert(21,"G---------G");
	bt.insert(3,"A---A");
	bt.insert(78,"Z--------Z");
	bt.insert(33,"K--K");
	bt.insert(72,"X--------X");
	bt.insert(54,"R---------R");
	bt.insert(12,"D------D");
	bt.insert(69,"W-----W");
	bt.insert(60,"T----t");
	bt.insert(27,"I-------I");
	bt.insert(6,"B------B");
	bt.insert(45,"O------O");
	bt.insert(15,"E---E");
	bt.insert(36,"L--------L");
	bt.insert(51,"Q-------Q");
	bt.insert(9,"C---C");
	bt.insert(18,"F--------F");
	bt.insert(48,"P----P");
	bt.insert(24,"H-------H");
	bt.insert(63,"U----U");
	bt.insert(30,"J------J");
	bt.insert(39,"M----M");
	bt.insert(57,"S---S");
	bt.insert(75,"Y---Y");

	//Intenta insertar clave repetida
	bt.insert(75,"y---y");

	}catch (string& e){
			cerr << e << endl;
	}


	bt.print(cout);
	bt.close();
}

/**
 * Test que evalúa el Secuence Set del BTree, abre un archivo existente y recorre sus claves
 *
 * @param fileName nombre del archivo a ser usado
 * @param blockSize tamaño de bloque del archivo
 */
void TestBTree::runTestSecuenceSet(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	try {
	bt.open(fileName,ios::in|ios::out);
	if(bt.getFirstElementSecuentSet() != NULL){
		cout<< bt.getFirstElementSecuentSet()<<endl;
		while(!bt.getEndSecuentSet()){
			cout<< bt.getNextElementSecuentSet() <<endl;
		}

	bt.close();
	}
	} catch (string& e){
		cerr << e << endl;
	}
}

/**
 * Test que evalúa el método remove del BTree
 */
void TestBTree::runTestRemove(string fileName, int blockSize){

}
