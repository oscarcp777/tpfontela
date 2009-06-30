#include <iostream>
#include <list>
#include "Tag.h"
#include "Define.h"


Tag::Tag(std::string nombre){

	this->nombreTag = nombre;

}


void Tag::addAtributo(std::string atributo){

	this->listaAtributos.push_back(atributo);
}

std::string Tag::getNombreTag(){

	return this->nombreTag;

}

int Tag::chequearAtributo(std::string nombreAtributo){

	std::list<std::string>::iterator iter;
	std::string atributo;
	bool fin = false;
	iter = this->listaAtributos.begin();
	int i=1;

	while((i<=this->listaAtributos.size()) && (fin==false)){
		atributo = *iter;

		if(nombreAtributo.compare(atributo)==0){
			fin = true;
			return 0;
		}

		else{
			i++;
			iter++;
		}

	}
	return -1;

}
Tag::~Tag(){
	list<std::string>::iterator iter;
	if(DEBUG_DESTRUCTOR==1)
			std::cout<<" entro al destructor de Tag"<<std::endl;

			std::string nombreA;
			std::cout<<"tamanio lista atributos: " <<this->listaAtributos.size()<<endl;
		 	iter=this->listaAtributos.begin();

		 	while(iter != this->listaAtributos.end()){
		 		nombreA=*iter;
		 		std::cout<<"atributo: " <<nombreA<<endl;
		 		iter++;
		 	}
		 	this->listaAtributos.clear();

			if(DEBUG_DESTRUCTOR==1)
					std::cout<<" salio del destructor de Tag"<<std::endl;

}
