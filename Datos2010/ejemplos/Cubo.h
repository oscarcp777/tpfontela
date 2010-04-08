/*
 * Cubo.h
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#ifndef CUBO_H_
#define CUBO_H_

#include<string>
#include<list>
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
	void SetCantClaves(int newCantClaves);
	void AddClave(string clave, int offset);
	void EliminarClave(string clave);
	int Buscar(string clave);
	void GuardarCubo();
	bool TieneEspacio();
	list<RegistroClaveHash> GetClaves();
	Cubo GetCubo(int offsetCubo);
	virtual ~Cubo();
};
#endif /* CUBO_H_ */
