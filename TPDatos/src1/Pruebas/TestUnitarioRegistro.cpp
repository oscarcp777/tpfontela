/*
 * TestUnitarioRegistro.cpp
 *
 *  Created on: 22/10/2009
 *      Author: Programadores
 */

#include "../Modelo/Alumno.h"
using namespace std;


int main45() {

	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	alumno1->Init();
	alumno1->serializarBinario();
	alumno1->setNombre("");
	alumno1->setPadron(0);
	alumno1->setDni(0);
	alumno1->hidratarBinario();
	cout<<"Nombre: " << alumno1->getNombre() << endl;
	cout<<"Padron: " << alumno1->getPadron() << endl;
	cout<<"DNI: " <<   alumno1->getDni()<< endl;


	return 0;
}
