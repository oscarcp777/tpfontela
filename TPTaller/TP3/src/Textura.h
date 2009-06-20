#ifndef __TEXTURA_H__
#define __TEXTURA_H__

#include <iostream>

class Textura {

	public:
		Textura(std::string id, std::string path);
		~Textura();
		std::string getId();
		std::string getPath();

	private:
		std::string id;
		std::string path;


};

#endif
