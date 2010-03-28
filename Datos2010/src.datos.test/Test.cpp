/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"
#include "Test.h"

Test::Test() {
	// TODO Auto-generated destructor stub
}
Test::~Test() {
	// TODO Auto-generated destructor stub
}
int main24235(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest();
	test->runTextFileTest();

	delete test;

	return 0;
}
