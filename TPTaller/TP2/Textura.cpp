#include "Textura.h"

Textura::Textura(std::string id, std::string path){
	id = id;
	path = path;
}

std::string Textura::getId(){
	return id;
}

std::string Textura::getPath(){
	return path;
}
