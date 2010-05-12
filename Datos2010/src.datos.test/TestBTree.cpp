/*
 * TestBTree.cpp
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#include "TestBTree.h"
#include "../src.datos.utils/ParserInput.h"
#include "../src.datos.utils/StringUtils.h"
#include "../src.datos.storage/TextFile.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>

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
	ParserInput* parser = new ParserInput();

	bt.create(fileName,ios::out);
	try{
	/*
	 * Inserta los datos provenientes de un archivo input.btree.dat.
	 * Con este conjunto de datos el secuence set tiene
	 * que quedar ordenado alfabéticamente
	 */
		fstream file;
		file.open("files/input",ios::in|ios::out);

		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				if(bt.insert(parser->getKey(),parser->getData().c_str())){
					cout << "Inserto el dato con la clave = " << parser->getKey() << endl;
				}else{
					cout << "No se inserto el dato " << parser->getKey() << endl;
				}
			}
		}
		file.close();

	}catch (string& e){
			cerr << e << endl;
	}

	bt.print("files/arbolAltas.txt");
	bt.close();
	delete parser;
}

void TestBTree::runTestInsertWithRandom(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	bt.create(fileName,ios::out);
	fstream file;
	file.open("input",ios::out);

	int max_register = 60000;
	int key;
	string data;
	string keydata;

	for(int i=0;i<max_register;i++){

		key = rand();
		keydata = StringUtils::convertIntToString(key);
		data = "AAAAAAAAAAA " + keydata;
		bt.insert(key,data.c_str());
	}

	bt.print("files/output");
	bt.close();
}
/**
 * Test que evalúa el Secuence Set del BTree, abre un archivo existente y recorre sus claves
 *
 * @param fileName nombre del archivo a ser usado
 * @param blockSize tamaño de bloque del archivo
 */
void TestBTree::runTestSecuenceSet(string fileName, int blockSize){

	BPlusTree<int>* bt = new BPlusTree<int>(blockSize);
	try {
		bt->open(fileName,ios::in|ios::out);
		char* element = bt->getFirstElementSecuentSet();
		while( element != NULL){
			cout<< element << endl;
			element = bt->getNextElementSecuentSet();
		}
		bt->close();

	} catch (string& e){
		cerr << e << endl;
	}
	delete bt;
}

/**
 * Test que evalúa el método remove del BTree
 */
void TestBTree::runTestRemove(string fileName, int blockSize){

	BPlusTree<int> bt(blockSize);
	bt.open(fileName,ios::in|ios::out);
	/*
	 * Realizamos test de distinta índole, ya que segun que clave eliminemos
	 * el árbol estará en un estado u otro.
	 * Además cada vez que eliminemos una clave, ésta será ingresada nuevamente
	 * para tener el árbol original.
	 */
	try {

		fstream file;
		file.open("files/inputdelete",ios::in|ios::out);
		ParserInput* parser = new ParserInput();
		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				if(bt.remover(parser->getKey())){
					cout << "Se elimino la clave = " << parser->getKey() << endl;
				}else{
					cout << "No se pudo eliminar la clave = " << parser->getKey() << endl;
				}
			}
		}
		file.close();
	} catch (string& e){
		cerr << e << endl;
	}

	bt.print("files/output");
	bt.close();
}

/*
 * Métodos que diferencian distintos caso de eliminación de una clave.
 *
 * El caso UNO consta de eliminar una clave que no es la mayor de ese nodo
 * y además no produce underflow. Es un caso básico en donde no influye en la
 * estructura del árbol. En este ejemplo eliminaremos la clave 9.
 *
 * Test OK
 */
void TestBTree::removeCaseOne(BPlusTree<int>* btree, int clave = 9){

	btree->remover(clave);
	btree->print("treeRemove1.txt");
}

/*
 * Eliminamos una clave que es la mayor dentro del nodo hoja,
 * sin provocar underflow en este nodo. En este ejemplo eliminamos la clave 21.
 *
 * Test OK
 */
void TestBTree::removeCaseTwo(BPlusTree<int>* btree, int clave = 21){

	btree->remover(clave);
	btree->print("treeRemove2.txt");

}
/*
 * Eliminamos una clave que no es la mayor dentro de la hoja y
 * al eliminarla produce underflow. Le pide una la clave menor al vecino
 * derecho si este no puede pasarle, porque este vecino entra en underflow, se la pide al izquierdo para equilibrar.
 * Para este ejemplo eliminamos la clave 27.
 * Aca se contemplan otros casos tambien ya que cuando el nodo entra en underflow, este le
 * pide una clave al hermano derecho pero este no se la da porque sino entraria en
 * underflow tambien. Por lo tanto le pide una clave al hermano derecho y este si le puede
 * prestar.
 *
 * Test NO OK.
 */
void TestBTree::removeCaseThree(BPlusTree<int>* btree, int clave = 27){

	btree->remover(clave);
	btree->print("treeRemove3.txt");
}
/*
 * Eliminamos una clave que se encuentra en la raiz. Para este caso
 * la clave a eliminar es la 66.
 *
 * Test NO OK
 */
void TestBTree::removeCaseFor(BPlusTree<int>* btree, int clave = 66){

	btree->remover(clave);
	btree->print("treeRemove4.txt");
}

//*********************************************************
//**************** Nuevos Tests  **************************
//*********************************************************

void TestBTree::runTestInsert(string fileName, int blockSize, int level){

	BPlusTree<int>* bt = new BPlusTree<int>(blockSize);
	ParserInput* parser = new ParserInput();

	std::string numLevel;
	std::stringstream out;
	out << level;
	numLevel = out.str();

	bt->create(fileName,ios::out);
	try{
		fstream file;
		string inputFileName = "files/inputFolder/insertBtreeLevel" + numLevel + ".txt";
		file.open(inputFileName.c_str(),ios::in|ios::out);
		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				if(bt->insert(parser->getKey(),parser->getData().c_str())){
					cout << "Inserto el dato con la clave = " << parser->getKey() << endl;
				}else{
					cout << "No se inserto el dato " << parser->getKey() << endl;
				}
			}
		}
		file.close();

	}catch (string& e){
		cerr << e << endl;
	}

	string outputFileName = "files/outputFolder/insertBtreeLevel" + numLevel + ".txt";
	bt->print(outputFileName);
	bt->close();
	delete parser;
	delete bt;

}


void TestBTree::runTestRemove(string fileName, int blockSize, int level){

	BPlusTree<int>* bt = new BPlusTree<int>(blockSize);
	ParserInput* parser = new ParserInput();
	bt->open(fileName,ios::in|ios::out);

	std::string numLevel;
	std::stringstream out;
	out << level;
	numLevel = out.str();

	try {

		fstream file;
		string deleteFileName = "files/inputFolder/removeBtreeLevel" + numLevel + ".txt";
		file.open(deleteFileName.c_str(),ios::in|ios::out);

		string line;

		while(!file.eof()){
			getline(file,line);
			if(line.length()!=0){
				parser->parser(line);
				if(bt->remover(parser->getKey())){
					cout << "Se elimino la clave = " << parser->getKey() << endl;
				}else{
					cout << "No se pudo eliminar la clave = " << parser->getKey() << endl;
				}
			}
		}
		file.close();
	} catch (string& e){
		cerr << e << endl;
	}

	string deleteFileName = "files/outputFolder/removeBtreeLevel" + numLevel + ".txt";
	bt->print(deleteFileName);
	bt->close();
	delete parser;
	delete bt;
}

//*********************************************************************
//*********************Fin Nuevos Tests********************************
//*********************************************************************




