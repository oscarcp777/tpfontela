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
};

#endif /* TESTBTREE_H_ */
