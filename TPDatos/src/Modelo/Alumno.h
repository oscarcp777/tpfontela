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
	Alumno(double dni, std::string nombre, int padron);
	virtual ~Alumno();
	int getPadron() const;
	void setPadron(int padron);
	int getDni() const;
	void setDni(int dni);
	std::string getNombre() const;
	void setNombre(std::string nombre);
    virtual Clave* serializarToolkit() const;
	virtual void hidratarToolkit (Clave* desde) const;



private:
	int padron;
	double dni;
	std::string nombre;

};



#endif /* ALUMNO_H_ */
