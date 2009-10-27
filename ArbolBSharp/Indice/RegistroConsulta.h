/*
 * RegistroConsulta.h
 *
 *  Created on: Oct 26, 2009
 *      Author: dan
 */

#include <string>

#ifndef REGISTROCONSULTA_H_
#define REGISTROCONSULTA_H_

using namespace std;

class RegistroConsulta{
	public:
			RegistroConsulta();
			RegistroConsulta(string termino,double pesoGlobal);
			string getTermino();
			double getPesoGlobal();
			int compareTo(RegistroConsulta o);
			~RegistroConsulta();

	private:
			string termino;
			double pesoGlobal;

};

#endif /* REGISTROCONSULTA_H_ */
