/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"

int main22(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest2();
	//test->runTextFileTest();

	delete test;

	return 0;
}
