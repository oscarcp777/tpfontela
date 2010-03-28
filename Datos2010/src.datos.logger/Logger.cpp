/*
 * Logger.cpp
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#include "Logger.h"
#include "time.h"

Logger* Logger::logger = NULL;

Logger::Logger(){

}

std::string Logger::getTimeSystem(){

	time_t rawtime;
	struct tm* timeinfo;
	time ( &rawtime );
	timeinfo = localtime (&rawtime);
	return asctime(timeinfo);
}

void Logger::open(fstream file, string fileName){

	file.open(fileName.c_str(), ios::in | ios::out);

	if (!this->file.is_open()) {

		this->file.clear();
		this->file.open(fileName.c_str(), ios::out);
		this->file.close();
		this->file.open(fileName.c_str(), ios::in | ios::out);
	}

}

void Logger::write(fstream file, string cadena){

	if (file.is_open()){


		file.seekg(0, ios::end);
		file << cadena << endl;
	}
}

Logger* Logger::getUnicaInstance(){

	if(!Logger::logger){
		/*
		 * Aca instancio el singleton y abró los archivos.
		 */
		Logger::logger = new Logger();

		this->open(this->fileInfo,PATH_INFO);
		this->open(this->fileDebug,PATH_DEBUG);
		this->open(this->fileError,PATH_ERROR);
	}

	return logger;
}

void Logger::setInfo(std::string cadena){

	this->write(this->fileInfo,this->getTimeSystem() + this->cadena);
}

void Logger::setDebug(std::string object, std::string cadena){

	this->write(this->fileDebug,this->getTimeSystem() + object + cadena);
}

void Logger::setError(std::string object, std::string cadena){

	this->write(this->fileError,this->getTimeSystem() + object + cadena);
}
/*
 * El logger se instancia al comienzo de la aplicacion
 * por lo tanto cuando esta se termine llamara al destructor
 * del logger automaticamente y es ahi donde se cierran los archivos
 * y liberan los recursos.
 */
Logger::~Logger(){

	//Cierra los archivos abiertos.
	this->fileInfo.close();
	this->fileDebug.close();
	this->fileError.close();

}
