#ifndef _FIGURA_H_
#define _FIGURA_H_

#include <iostream>


class Figura{

	public:
		 virtual int dibujar() = 0; //metodo virtual puro 
		 
		 std::string getId();
		 std::string getIdTextura();
		 void setIdTextura(std::string idTextura);
	protected:
		std::string id;
		std::string idTextura;

};
#endif