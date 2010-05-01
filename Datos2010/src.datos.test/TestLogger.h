/*
 * TestLogger.h
 *
 *  Created on: 30/04/2010
 *      Author: nelson
 */

#ifndef TESTLOGGER_H_
#define TESTLOGGER_H_
#include "../src.datos.logger/Logger.h"
class TestLogger {
public:
	TestLogger();
	~TestLogger();
	void runTestLogger();
	void runTestInsert(Logger* logger);
	void runTestSearch(Logger* logger);
	void runTestPrint(Logger* logger);
};

#endif /* TESTLOGGER_H_ */
