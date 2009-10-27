/*
 * RegistroIndexador.h
 *
 *  Created on: Oct 26, 2009
 *      Author: dan
 */
#include <string>

#ifndef REGISTROINDEXADOR_H_
#define REGISTROINDEXADOR_H_

using namespace std;

class RegistroIndexador{

	public:
			RegistroIndexador();
			void setTermino(string termino);
			string getTermino();
			~RegistroIndexador();
	private:
			string termino;
};

#endif /* REGISTROINDEXADOR_H_ */
