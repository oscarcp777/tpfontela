/*
 * RegistroIndice.h
 *
 *  Created on: 21/10/2009
 *      Author: Administrador
 */

#include <string>

#ifndef REGISTROINDICE_H_
#define REGISTROINDICE_H_

using namespace std;

class RegistroIndice{

	public:
			RegistroIndice();
			RegistroIndice(string termino, double pesoGlobal);
			~RegistroIndice();
			double getPesoGlobal();
			string getTermino();
			double pesoGlobal;
			string termino;
	private:



};

#endif /* REGISTROINDICE_H_ */
