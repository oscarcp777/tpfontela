/*
 * ParserInput.cpp
 *
 *  Created on: 15/04/2010
 *      Author: nelson ramos
 */

#include "ParserInput.h"
#include "stdlib.h"

ParserInput::ParserInput(std::string line){

	std::string begin = "(";
	std::string separador = ";";
	std::string end = ")";

	std::string aux1 = line;
	std::string aux2 = line;
	std::string aux3 = line;

	int inicio = aux1.find(begin);
	int delimitador = aux2.find(separador);
	int fin = aux3.find(end);

	this->key = atoi(line.substr(inicio + 1,delimitador - 1).c_str());
	this->data = line.substr(delimitador + 1,fin - delimitador -1);

}
int ParserInput::getKey(){

	return this->key;
}

std::string ParserInput::getData(){

	return this->data;
}

ParserInput::~ParserInput(){

}

