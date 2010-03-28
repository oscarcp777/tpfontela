/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"

int main(){

Test::~Test() {
	// TODO Auto-generated destructor stub
}
int main567(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest();
	test->runTextFileTest();

	delete test;

	return 0;
}
