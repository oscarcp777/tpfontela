#ifndef __TAG_H___
#define __TAG_H___

#include <iostream>
#include <iostream.h>
#include <string>
#include <list>
using namespace std;

class Tag{


private:
	std::string nombreTag;
	std::list<std::string> listaAtributos;



public:

	Tag(std::string nombreTag);
	~Tag();
	void Tag::addAtributo(std::string atributo);

	int Tag::chequearAtributo(std::string nombreAtributo);

    std::string Tag::getNombreTag();


};

#endif
