/*
 * Elemento.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include <string>

#ifndef ELEMENTO_H_
#define ELEMENTO_H_

using namespace std;

class Elemento{

	public:
			Elemento();
			Elemento(int hijoIzq, int hijoDer, string clave);
			~Elemento();
			string getClave();
			int getHijoIzq();
			int getHijoDer();
			void setClave(string clave);
			void setHijoDer(int hijoDer);
			void setHijoIzq(int hijoIzq);

	private:
			int hijoIzq;
			int hijoDer;
			string clave;

};

#endif /* ELEMENTO_H_ */



