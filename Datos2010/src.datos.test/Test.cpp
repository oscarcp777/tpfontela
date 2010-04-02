/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"

int mainererter(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest();
	test->runTextFileTest();

	delete test;

	return 0;
}
