/*
 * TestFreeBlockController.h
 *
 *  Created on: 25/04/2010
 *      Author: Richard
 */

#ifndef TESTFREEBLOCKCONTROLLER_H_
#define TESTFREEBLOCKCONTROLLER_H_

#include "../src.datos.storage/FreeBlockController.h"

class TestFreeBlockController {
public:
	TestFreeBlockController();
	virtual ~TestFreeBlockController();

	void runGeneralTest();
	void runAddTest();
	void runGetTest();
	void runPrintTest(ostream&);
};

#endif /* TESTFREEBLOCKCONTROLLER_H_ */
