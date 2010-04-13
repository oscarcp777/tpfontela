/*
 * Logger.cpp
 *
 *  Created on: 26/03/2010
 *      Author: nelson
 */

#include "Logger.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "../src.datos.utils/Define.h"

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

		(date[i]) = *(cadena + i);
	}

	date[SIZE_SYSTEM_TIME - 1]='\0';

	return date;
}
void Logger::split(string cadena){

	string numero = this->convertIntToString(this->coutFiles);
	fstream newFile;
	string newPath = PATH_LOGGER + numero;
	rename(PATH_LOGGER,newPath.c_str());
	this->file.close();
	this->open(&newFile,PATH_LOGGER);
	this->write(&newFile,cadena);
	this->coutFiles++;
	fstream config;
	this->open(&config,PATH_CONFIG);
	config.seekg(0,ios::beg);
	config << this->convertIntToString(this->coutFiles) << std::endl;
	config.close();
}

string Logger::convertIntToString(int numero){

	string retorno;
	int temp;
	int tempCountFiles = numero;

	while((tempCountFiles/ 10) != 0){
		temp = tempCountFiles % 10;
		tempCountFiles = tempCountFiles/10;
		temp =temp + 48;
		retorno = (char)temp + retorno;
	}

	tempCountFiles = tempCountFiles + 48;
	retorno = (char)tempCountFiles + retorno ;
	return retorno;
}

Logger::Logger(int sizeFile){

	this->open(&this->file,PATH_LOGGER);
	this->date = new char[SIZE_SYSTEM_TIME];
	std::string cadena;
	int sizeTemp = 0;

	if (this->file.is_open()){
		while (!this->file.eof()){

			getline(this->file,cadena);
			sizeTemp = sizeTemp + strlen(cadena.c_str());
		}
	}

	this->file.close();
	this->open(&this->file,PATH_LOGGER);

	fstream config;
	int fileCount;
	this->open(&config,PATH_CONFIG);

	getline(config,cadena);
	fileCount = atoi(cadena.c_str());
	//Verificamos si el archivo se creo vacio, si es asi la variable toma
	//el valor inicia 1.
	if(fileCount==0){

		fileCount = 1;
		this->write(&config,this->convertIntToString(fileCount));
	}

	this->sizeFile = sizeFile - sizeTemp;
	this->coutFiles = fileCount;
	config.close();
}

Logger* Logger::getUnicaInstancia(){

	if(!Logger::logger){

		Logger::logger = new Logger();
	}

	return logger;
}

void Logger::setSizeFile(int fileSize){

	this->sizeFile = fileSize;
}

void Logger::info(std::string cadena){

	string temp = this->getTimeSystem() + TAB + cadena;
	int size = strlen(temp.c_str());
	int aux = this->sizeFile - size;
	if(aux < 0){

		this->split(temp);
	}else{
		this->write(&this->file,temp);
		this->sizeFile = aux;
	}
}

void Logger::print(){

	fstream result;
	fstream logTemp;
	string cadena;
	int countFileTemp = this->coutFiles;
	countFileTemp--;
	this->open(&result,"files/result");

	/*
	 * Leo todos los archivos parciales del logger
	 * y los escribo en uno nuevo.
	 */
	while(countFileTemp > 0){

		this->open(&logTemp,PATH_LOGGER + this->convertIntToString(countFileTemp));
		while(!logTemp.eof()){
			getline(logTemp,cadena);
			if(cadena!=""){
				this->write(&result,cadena);
			}
		}
		logTemp.close();
		countFileTemp--;
	}

	this->file.close();
	this->open(&this->file,PATH_LOGGER);
	while(!this->file.eof()){
		getline(this->file,cadena);
		this->write(&result,cadena);
	}
	result.close();
}

/*
 * El logger se instancia al comienzo de la aplicacion
 * por lo tanto cuando esta se termine llamara al destructor
 * del logger automaticamente y es ahi donde se cierran los archivos
 * y liberan los recursos.
 */
Logger::~Logger(){

	//Cierra el archivos abierto.
	delete []this->date;
	this->file.close();

}
