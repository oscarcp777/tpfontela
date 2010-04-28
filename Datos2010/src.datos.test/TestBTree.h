/*
 * TestBTree.h
 *
 *  Created on: 27/04/2010
 *      Author: Santiago
 */

#ifndef TESTBTREE_H_
#define TESTBTREE_H_

#include "../src.datos.treeB/BPlusTree.h"

class TestBTree {
public:
	TestBTree();
	virtual ~TestBTree();

	void runTestInsert(string fileName, int blockSize);
	void runTestSecuenceSet(string fileName, int blockSize);
	void runTestRemove(string fileName, int blockSize);

	/*
	 * Los siguientes metodos se expesifican distintos casos
	 * de eliminacion de una clave. Su explicacion esta en .cpp
	 */
	void remuveCaseOne(BPlusTree<int>* btree, int clave);
	void remuveCaseTwo(BPlusTree<int>* btree, int clave);
	void remuveCaseThree(BPlusTree<int>* btree, int clave);
};

#endif /* TESTBTREE_H_ */
