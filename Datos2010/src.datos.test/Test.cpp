/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"
#include "TestFreeBlockController.h"
#include "TestBTree.h"

int main(){
	TestIOFile* testIOFile = new TestIOFile();
	TestFreeBlockController* testFreeBlockController = new TestFreeBlockController();
	TestBTree* testBTree = new TestBTree();


//	testIOFile->runBinaryFileTest2();
//	testIOFile->runTextFileTest();
//	testFreeBlockController->runFreeBlockControllerTest();
	testBTree->runTestInsert("files/testbt.dat", 128);
//	testBTree->runTestSecuenceSet("files/testbt.dat",128);
//	testBTree->runTestRemove("files/testbt.dat",128);




	delete testIOFile;
	delete testFreeBlockController;
	delete testBTree;


	return 0;
}
