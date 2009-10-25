/*
 * Alumno.h
 *
 *  Created on: 01-oct-2009
 *      Author: Santiago
 */

#include <iostream>
#include "Nota.h"

#include "../Composite/Registro/Registro.h"

#ifndef ALUMNO_H_
#define ALUMNO_H_

class Alumno : public Registro  {
public:
	Alumno(double dni, std::string nombre, int padron,int n1,int n2, int n3);
	Alumno();
	virtual ~Alumno();
	int getPadron();
	void setPadron(int padron);
	int getDni();
	void setDni(int dni);
	std::string getNombre();
	void setNombre(std::string nombre);

	void serializarBinario();
	void hidratarBinario();
	void serializarTexto();
	void hidratarTexto();
	int compareTo(std::string clave, int num);
	Registro* obtenerNuevaInstancia();
	std::string getClaveObjeto();
	//para pruebas unitarias
	void Init();



private:
	int padron;
	double dni;
	std::string nombre;
	Nota* nota[3];


};



#endif /* ALUMNO_H_ */
