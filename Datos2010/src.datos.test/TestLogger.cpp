/*
 * TestLogger.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestLogger.h"

TestLogger::TestLogger(){

	this->file = new TextFile();
	this->logger = Logger::getUnicaInstancia();
}

void TestLogger::testLoggerInfo(){


	this->logger->info(this->file,"Esta es una info");
}

void TestLogger::testLoggerDebug(){


	this->logger->debug(this->file,"este es un debug");
}

void TestLogger::testLoggerError(){

	this->logger->error(this->file,"este es un error");
}

void TestLogger::runLoggerTest(){

	this->testLoggerInfo();
	this->testLoggerDebug();
	this->testLoggerError();
}

TestLogger::~TestLogger() {

	delete this->file;
}
