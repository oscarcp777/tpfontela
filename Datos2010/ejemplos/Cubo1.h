/*
 * Cubo.h
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#ifndef CUBO_H_
#define CUBO_H_

#include <iostream>
#include <fstream>
#include <list>
#include <string.h>
#include <stdexcept>
#include <stdio.h>
#include "RegistroClaveHash.h"

using namespace std;

class Cubo {
static const int maxClaves = 5;

private:
	int tamanioDispersion;
	int cantClaves; //puede ser variable ver como hacerlo
	int offsetCubo;

public:
	list<RegistroClaveHash> claves;
	Cubo(int cantClaves, int tamaniodispersion);
	int GetTamanioDispersion();
	void SetTamanioDispersion(int newDispersion);
	int GetCantClaves();
	void SetCantClaves(int newDispersion);
    void AgregarClave(RegistroClaveHash* reg);
	void EliminarClave(string clave);
	int Buscar(string clave);
	bool TieneEspacio();
	list<RegistroClaveHash> GetClaves();
	Cubo GetCubo(int offsetCubo, fstream* fileCubo, int longClave);
	void SaveCubo(fstream* fileCubos, int offsetCubo) throw (exception);
	virtual ~Cubo();
};

#endif /* CUBO_H_ */

