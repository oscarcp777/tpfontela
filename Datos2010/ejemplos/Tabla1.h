/*
 * Tabla.h
 *
 *  Created on: 31/10/2009
 *      Author: santiago
 */

#ifndef TABLA_H_
#define TABLA_H_

#include<list>
#include<vector>
#include<string>
#include <fstream>
#include"Cubo.h"
#include"RegistroClaveHash.h"

using namespace std;

class Tabla {
private:
	vector<int> offsetCubos;
	int cantCubos; //se setea en el encabezado del archivo tabla
public:
	Tabla();
	int GetCantCubos();
	void SetCantCubos(int cantCubos);
	int ClaveToInt(string clave);
	int Hash(string clave);
	void AddClave(RegistroClaveHash *reg);
	int AddCubo(); //ver si necesito la ruta del archivo
	Cubo GetCubo(fstream fileCubo, int offsetCubo, int longclave);
	int Buscar(string clave);
	Tabla CargarTabla(fstream* fileTabla); //carga la tabla desde el archivo y setea la cantCubos
	void SaveTabla(fstream* fileTabla) throw (exception); //guarda la tabla en el archivo
	void DuplicarTabla(int indiceCubo);
	void Redispersar(int offsetCubo);
	virtual ~Tabla();
}


#endif /* TABLA_H_ */
