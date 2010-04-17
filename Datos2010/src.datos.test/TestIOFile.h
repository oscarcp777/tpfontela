/*
 * TestIOFile.h
 *
 *  Created on: 27/03/2010
 *      Author: Santiago
 */

#ifndef TESTIOFILE_H_
#define TESTIOFILE_H_

#include "../src.datos.storage/BinaryFile.h"
#include "../src.datos.storage/TextFile.h"

class TestIOFile {
public:
	TestIOFile();
	virtual ~TestIOFile();
	void runBinaryFileTest();
	void runTextFileTest();
	void runBinaryFileTest2();
};

#endif /* TESTIOFILE_H_ */
