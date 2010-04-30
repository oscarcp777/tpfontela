/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"
#include "TestFreeBlockController.h"
#include "TestBTree.h"
#include "TestLogger.h"
#include "../src.datos.utils/Define.h"

int main(){

	TestIOFile* testIOFile = new TestIOFile();
	TestFreeBlockController* testFreeBlockController = new TestFreeBlockController();
	TestBTree* testBTree = new TestBTree();
	TestLogger* testLogger = new TestLogger();


//	testIOFile->runBinaryFileTest2();
//	testIOFile->runTextFileTest();
//	testFreeBlockController->runGeneralTest();
//	testFreeBlockController->runAddTest();
//	testFreeBlockController->runGetTest();
//	testBTree->runTestInsert("files/testbt.dat", 128);
	testBTree->runTestSecuenceSet("files/testbt.dat",128);
//	testBTree->runTestRemove("files/testbt.dat",128);
//	testLogger->runTestLogger();

	delete testLogger;
	delete testIOFile;
	delete testFreeBlockController;
	delete testBTree;


	return 0;
}
