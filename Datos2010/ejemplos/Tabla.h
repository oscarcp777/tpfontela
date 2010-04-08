/*
 * Tabla.h
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#ifndef TABLA_H_
#define TABLA_H_

using namespace std;

#include<list>
#include<vector>
#include<string>
#include "Cubo.h"
#include "RegistroClaveHash.h"
Z
class Tabla {
private:
	vector<int> offsetCubos;
	int cantCubos; //se setea en el encabezado del archivo tabla
public:
	Tabla();
	Tabla CargarTabla(); //carga la tabla desde el archivo y setea la cantCubos
	int GetCantCubos();
	void SetCantCubos(int cantCubos);
	int ClaveToInt(string clave);
	int Hash(string clave);
	void AddClave(string clave, int offset);
	int AddCubo(); //ver si necesito la ruta del archivo
	Cubo GetCubo(int offsetCubo);
	int Buscar(string clave);
	void DuplicarTabla(int indiceCubo);
	void Redispersar(int offsetCubo);
	virtual ~Tabla();
};

#endif /* TABLA_H_ */
