/*
 * Nodo.h
 *
 *  Created on: Oct 11, 2009
 *      Author: dan
 */
#include <string>

#ifndef _NODOREGISTRO_H_
#define _NODOREGISTRO_H_

class NodoRegistro{
	public:
		NodoRegistro ();
		NodoRegistro(int claveRegistro,long posicionRegistro);
		void setClaveRegistro(int claveRegistro);
		void setPosicionRegistro(long posicionRegistro);
		int getClaveRegistro();
		long getPosicionRegistro();
		~NodoRegistro();

	private:
		int claveRegistro; //clave maestra
		long posicionRegistro;
};

#endif /* NODO_H_ */
