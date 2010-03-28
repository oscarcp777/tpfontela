/*
 * TestLogger.h
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#ifndef TESTLOGGER_H_
#define TESTLOGGER_H_

#include "../src.datos.logger/Logger.h"
#include "../src.datos.storage/TextFile.h"

class TestLogger {

private:

	Logger* logger;
	TextFile* file;
	void testLoggerInfo();
	void testLoggerDebug();
	void testLoggerError();

public:
	TestLogger();
	void runLoggerTest();
	~TestLogger();
};

#endif /* TESTLOGGER_H_ */
