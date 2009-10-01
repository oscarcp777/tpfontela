/*
 * Alumno.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include <iostream>
#include "../Composite/Dato.h"

#ifndef ALUMNO_H_
#define ALUMNO_H_

class Alumno : public Dato {
public:
	Alumno();
	virtual ~Alumno();
	int getPadron() const;
	void setPadron(int padron);
	int getDni() const;
	void setDni(int dni);
	std::string getNombre() const;
	void setNombre(std::string nombre);


private:
	int padron;
	int dni;
	std::string nombre;

};



#endif /* ALUMNO_H_ */
