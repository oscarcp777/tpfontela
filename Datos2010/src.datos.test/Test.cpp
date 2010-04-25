/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"
#include "TestFreeBlockController.h"

int main(){
//	TestIOFile* test = new TestIOFile();
//	test->runBinaryFileTest2();
//	test->runTextFileTest();

	TestFreeBlockController* test = new TestFreeBlockController();
	test->runFreeBlockControllerTest();

	delete test;

	return 0;
}
