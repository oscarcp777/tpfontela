/*
 * TestLogger.cpp
 *
 *  Created on: 30/04/2010
 *      Author: nelson
 */

#include "TestLogger.h"

TestLogger::TestLogger() {

}
/*
 * Ejecuta los test del logger, inserta una info al logger y busca una
 * parabra en el archivo de salida.
 */
void TestLogger::runTestLogger(){

	Logger* logger = Logger::getUnicaInstancia();
	this->runTestInsert(logger);
	this->runTestSearch(logger);
}
void TestLogger::runTestInsert(Logger* logger){

	string line = "Esto es un test del logger";
	logger->info(line);

}
void TestLogger::runTestSearch(Logger* logger){

	string word = "test";
	logger->search(word);
}

TestLogger::~TestLogger() {

}
