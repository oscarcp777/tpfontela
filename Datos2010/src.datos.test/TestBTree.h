/*
 * TestBTree.h
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#ifndef TESTBTREE_H_
#define TESTBTREE_H_

#include "../src.datos.treeB/BPlusTree.h"


using namespace std;

class TestBTree {
public:
	TestBTree();
	virtual ~TestBTree();

	void runTestInsert(string fileName, int blockSize);
	void runTestInsertWithRandom(string fileName, int blockSize);
	void runTestSecuenceSet(string fileName, int blockSize);
	void runTestRemove(string fileName, int blockSize);
	void runTestRemoveRompe(string fileName, int blockSize);

	/*
	 * Los siguientes metodos se expesifican distintos casos
	 * de eliminacion de una clave. Su explicacion esta en .cpp
	 */
	void removeCaseOne(BPlusTree<int>* btree, int clave);
	void removeCaseTwo(BPlusTree<int>* btree, int clave);
	void removeCaseThree(BPlusTree<int>* btree, int clave);
	void removeCaseFor(BPlusTree<int>* btree, int clave);

//****** Nuevos Tests ************
	void runTestInsert	(string fileName, int blockSize, int level);
	void runTestRemove	(string fileName, int blockSize, int level);
//********************************

};

#endif /* TESTBTREE_H_ */
