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
 * Ejecuta los test del logger, inserta los datos provenientes de
 * un archivo. El logger genera archivo de salida de tamanio de 512 bytes.
 */
void TestLogger::runTestLogger(){

	Logger* logger = Logger::getUnicaInstancia();
//	this->runTestInsert(logger);
	this->runTestSearch(logger);
	this->runTestPrint(logger);
}

void TestLogger::runTestInsert(Logger* logger){

	fstream fileInputTest;
	string line;
	fileInputTest.open("files/input.logger.dat",ios::in|ios::out);

	while(!fileInputTest.eof()){
		getline(fileInputTest,line);
		if(line.length()!=0){
			logger->info(line);
		}
	}
	fileInputTest.close();
}

void TestLogger::runTestSearch(Logger* logger){

	string word = "idioma";
	logger->search(word);
}

void TestLogger::runTestPrint(Logger* logger){

	logger->print("fileTest");
}


TestLogger::~TestLogger() {

}
