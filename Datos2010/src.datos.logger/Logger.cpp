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

	for(int i=0 ; i < (SIZE_SYSTEM_TIME - 1) ; i++){

		(temp[i]) = *(cadena + i);
	}

	temp[SIZE_SYSTEM_TIME - 1]='\0';

	return temp;
}

Logger::Logger(){

	this->open(&this->file,PATH_LOGGER);
	this->temp = new char[SIZE_SYSTEM_TIME];

}

Logger* Logger::getUnicaInstancia(){

	if(!Logger::logger){

		Logger::logger = new Logger();
	}

	return logger;
}

void Logger::info(std::string object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object + TAB + INFO_FLAG + TAB + cadena;
	this->write(&this->file,temp);

}

void Logger::debug(std::string object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object + TAB + DEBUG_FLAG + TAB + cadena;
	this->write(&this->file,temp);
	if(DEBUG){

		std::cout << temp << endl;
	}
}

void Logger::error(std::string object, std::string cadena){

	string temp = this->getTimeSystem() + TAB + object + TAB + ERROR_FLAG + TAB + cadena;
	this->write(&this->file,temp);
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
	this->file.close();

}
