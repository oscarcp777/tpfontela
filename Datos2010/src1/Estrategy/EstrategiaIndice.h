/*
 * EstrategiaIndice.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAINDICE_H_
#define ESTRATEGIAINDICE_H_
#include "../Object/Object.h"
#include "../Almacenamiento/Archivo.h"

class EstrategiaIndice :public Object{
public:
	EstrategiaIndice();
	virtual ~EstrategiaIndice();
	virtual int setArchivo(char* nombre, char* ruta);

	virtual int abrir() =0;
	virtual int crear(char* nombre, char* ruta) =0;
	virtual int cerrar() =0;
	virtual int insertar(char* key, int dir) =0;
	virtual int modificar(char* key, int dir) =0;
	virtual int remover(char* key, int dir=-1) =0;
	virtual int buscar(char* key, int dir=-1) =0;

	std::string toString();

protected:
	char* buffer;
	Archivo* archivoIndice;
};

#endif /* ESTRATEGIAINDICE_H_ */
