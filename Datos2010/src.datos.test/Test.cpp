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
#include "TestHash.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.storage/Buffer.h"
int main(){

//	TestIOFile* testIOFile = new TestIOFile();
//	TestFreeBlockController* testFreeBlockController = new TestFreeBlockController();
//	TestBTree* testBTree = new TestBTree();
//	TestLogger* testLogger = new TestLogger();
	TestHash* testHash = new TestHash();

//	testIOFile->runBinaryFileTest2();
//	testIOFile->runTextFileTest();
//	testFreeBlockController->runGeneralTest();
//	testFreeBlockController->runAddTest();
//	testFreeBlockController->runPrintTest(cout);
//	testFreeBlockController->runGetTest();
//	testBTree->runTestInsert("files/testbt.dat", SIZE_CUBE);
//	testBTree->runTestSecuenceSet("files/testbt.dat",128);
//	testBTree->runTestRemoveRompe("files/testbt.dat",SIZE_CUBE);
//	testBTree->runTestRemoveRompe("files/testbt.dat",128);
//	testLogger->runTestLogger();

//*************TESTs HASH*******************
//	testHash->runCreateAndInsertTest();
//	testHash->runExampleCatedraTest();
    testHash->runRemoveTest();
//	testHash->runSearchTest();
//	testHash->runUpdateTest();
//	testHash->runPrintTest();
//*************FIN TESTs HASH*******************

//	delete testLogger;
//	delete testIOFile;
//	delete testFreeBlockController;
//	delete testBTree;
	delete testHash;


	return 0;
}
