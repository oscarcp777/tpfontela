/*
 * TestUnitarioTexto.cpp
 *
 *  Created on: 23/10/2009
 *      Author: Programadores
 */

#include "../Modelo/Alumno.h"
using namespace std;


int main12() {

	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	alumno1->Init();
	alumno1->serializarTexto();
	alumno1->setNombre("");
	alumno1->setPadron(0);
	alumno1->setDni(0);
	alumno1->hidratarTexto();
	cout<<"Nombre: " << alumno1->getNombre() << endl;
	cout<<"Padron: " << alumno1->getPadron() << endl;



	return 0;
}
