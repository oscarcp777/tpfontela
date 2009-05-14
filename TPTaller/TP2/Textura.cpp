#include "Textura.h"

Textura::Textura(std::string id, std::string path){
	this->id = id;
	this->path = path;
}

std::string Textura::getId(){
	return this->id;
}

std::string Textura::getPath(){
	return this->path;
}
Textura::~Textura(){
	
}
