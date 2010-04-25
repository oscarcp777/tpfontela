/*
 * Logger.cpp
 *
 *  Created on: 26/03/2010
 *      Author: nelson ramos
 */

#include "Logger.h"
#include "time.h"
#include "stdlib.h"
#include "string.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.utils/StringUtils.h"

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

	string numero = StringUtils::convertIntToString(this->coutFiles);
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
	config << StringUtils::convertIntToString(this->coutFiles) << std::endl;
	config.close();
}

Logger::Logger(int sizeFile){
    this->countRead=0;
    this->countWrite=0;
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

	if(fileCount==0){

		fileCount = 1;
		this->write(&config,StringUtils::convertIntToString(fileCount));
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

void Logger::print(string fileName){

	fstream result;
	fstream logTemp;
	string cadena;
	int countFileTemp = this->coutFiles;
	countFileTemp--;
	this->open(&result,"files/" + fileName);

	/*
	 * Leo todos los archivos parciales del logger
	 * y los escribo en uno nuevo.
	 */
	while(countFileTemp > 0){

		this->open(&logTemp,PATH_LOGGER + StringUtils::convertIntToString(countFileTemp));
		while(!logTemp.eof()){
			getline(logTemp,cadena);
			if(cadena!=""){
				this->write(&result,cadena);
			}
		}
		logTemp.close();
		countFileTemp--;
	}
	//Cierro el archivo actual para posicionarme al comienzo de este
	//para copiar el contenido en el archivo nuevo. No lo cierro para
	//poder seguir escribiendo sobre este.
	this->file.close();
	this->open(&this->file,PATH_LOGGER);
	while(!this->file.eof()){
		getline(this->file,cadena);
		this->write(&result,cadena);
	}
	result.close();
}

void Logger::search(string cadena){

	//Me genero un archivo nuevo con todo los log juntos
	//para realizar la busqueda sobre este.
	this->print("temp");
	fstream temp;
	string linea;
	string lineaTemp;

	this->open(&temp,PATH_TEMP);

	while(!temp.eof()){
		getline(temp,linea);
		lineaTemp = linea;
		int flag = linea.find(cadena);
		if(flag != -1){
			std::cout << lineaTemp << std::endl;
		}
	}
	temp.close();
	remove(PATH_TEMP);
}

Logger::~Logger(){

	//Cierra el archivos abierto.
	delete []this->date;
	this->file.close();

}
