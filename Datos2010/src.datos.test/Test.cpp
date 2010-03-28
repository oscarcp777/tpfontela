/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "Test.h"

Test::Test() {
	// TODO Auto-generated constructor stub

}

Test::~Test() {
	// TODO Auto-generated destructor stub
}
int main(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest();
//	test->runTextFileTest();

	return 0;
}
