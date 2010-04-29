/*
 * TestBTree.cpp
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#include "TestBTree.h"
#include "../src.datos.utils/ParserInput.h"

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
	/*
	 * Inserta los datos provenientes de un archivo input.btree.dat.
	 * Con este conjunto de datos el secuence set tiene
	 * que quedar ordenado alfabéticamente
	 */
		fstream file;
		file.open("files/input.btree.dat",ios::in|ios::out);
		ParserInput* parser = new ParserInput();
		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				bt.insert(parser->getKey(),parser->getData().c_str());
			}
		}
		file.close();
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
		char* element = bt.getFirstElementSecuentSet();
		while( element != NULL){
			cout<< element << endl;
			element = bt.getNextElementSecuentSet();
		}
		bt.close();

	} catch (string& e){
		cerr << e << endl;
	}
}

/**
 * Test que evalúa el método remove del BTree
 */
void TestBTree::runTestRemove(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	/*
	 * Realizamos test de distinta índole, ya que segun que clave eliminemos
	 * el árbol estará en un estado u otro.
	 * Además cada ves que eliminemos una clave, ésta será ingresada nuevamente
	 * para tener el árbol original.
	 */
	try {

		bt.open(fileName,ios::in|ios::out);
		int clave = 39;
		char* dato = bt.search(clave);
		cout<<"Arbol antes de la eliminacion de la clave ";
		cout<< clave <<endl <<endl;
		bt.print(cout);
		this->removeCaseThree(&bt,clave);
		cout<<"Arbol despues de la eliminacion de la clave ";
		cout<< clave <<endl << endl;
		bt.print(cout);
		bt.insert(clave,dato);
		cout<<"Arbol reestructurado con la insercion de la clave ";
		cout<< clave <<endl << endl;
		bt.print(cout);
		bt.close();
	} catch (string& e){
		cerr << e << endl;
	}

}

/*
 * Métodos que diferencian distintos caso de eliminación de una clave.
 *
 * El caso UNO consta de eliminar una clave que no es la mayor de ese nodo
 * y además no produce underflow. Es un caso básico en donde no influye en la
 * estructura del árbol. En este ejemplo eliminaremos la clave 9.
 */
void TestBTree::removeCaseOne(BPlusTree<int>* btree, int clave){

	btree->remover(clave);
	btree->print(cout);
}

/* Ver este caso, que no anda. Se cuelga la maquina.
 * Eliminamos una clave que es la mayor dentro del nodo hoja,
 * sin provocar underflow. En este ejemplo eliminamos la clave 21.
 */
void TestBTree::removeCaseTwo(BPlusTree<int>* btree, int clave){

	btree->remover(clave);
	btree->print(cout);
}
/*
 * Ver este caso, no se cuelga pero no elimina.
 * Eliminamos una clave que no es la mayor dentro de la hoja y
 * al eliminarla produce underflow.
 * Para este ejemplo eliminamos la 39.
 */
void TestBTree::removeCaseThree(BPlusTree<int>* btree, int clave){

	btree->remover(clave);
	btree->print(cout);
}


