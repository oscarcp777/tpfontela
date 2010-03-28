/*
 * Logger.cpp
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#include "Logger.h"
#include "time.h"
#include "../src.datos.utils/Object.h"

Logger* Logger::logger = NULL;

void Logger::open(fstream* file, string fileName){

	file->open(fileName.c_str(), ios::in | ios::out);

	if (!file->is_open()) {

		file->clear();
		file->open(fileName.c_str(), ios::out);
		file->close();
		file->open(fileName.c_str(), ios::in | ios::out);
	}
}

void Logger::write(fstream* file, string cadena){

	if (file->is_open()){


		file->seekg(0, ios::end);
		(*file) << cadena << std::endl;
	}
}

std::string Logger::getTimeSystem(){

	time_t rawtime;
	struct tm* timeinfo;
	time ( &rawtime );
	timeinfo = localtime (&rawtime);

	char* cadena = asctime(timeinfo);

	this->temp = new char[25];

	for(int i=0 ; i<24 ; i++){

		(temp[i]) = *(cadena + i);
	}

	temp[24]='\0';

	return temp;
}

Logger::Logger(){

	this->open(&this->fileInfo,PATH_INFO);
	this->open(&this->fileDebug,PATH_DEBUG);
	this->open(&this->fileError,PATH_ERROR);

}

Logger* Logger::getUnicaInstancia(){

	if(!Logger::logger){

		Logger::logger = new Logger();
	}

	return logger;
}


void Logger::info(Object* object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object->toString()+ cadena;
	this->write(&this->fileInfo,temp);

}

void Logger::debug(Object* object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object->toString() + TAB + cadena;
	this->write(&this->fileDebug,temp);
	if(DEBUG){

		std::cout << temp << endl;
	}
}

void Logger::error(Object* object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object->toString() + TAB + cadena;
	this->write(&this->fileError,temp);
}
/*
 * El logger se instancia al comienzo de la aplicacion
 * por lo tanto cuando esta se termine llamara al destructor
 * del logger automaticamente y es ahi donde se cierran los archivos
 * y liberan los recursos.
 */
Logger::~Logger(){

	//Cierra los archivos abiertos.
	delete []this->temp;
	this->fileInfo.close();
	this->fileDebug.close();
	this->fileError.close();

}
