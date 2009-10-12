/*
 * EstrategiaAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTO_H_
#define ESTRATEGIAALMACENAMIENTO_H_
#include "../Object/Object.h"
#include "../Almacenamiento/Almacenamiento.h"
#include "../utils/Define.h"
#include "../Almacenamiento/Archivo.h"
#include "../Composite/Bloque/Bloque.h"
#include "../Composite/Registro/Registro.h"
#include <sstream>

class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	virtual void guardar(Almacenamiento* donde);
	std::string toString();
	void generarClaves(Almacenamiento* donde);
	virtual std::string generarRegistro(Componente* componente);
	virtual void agregarComponente(Almacenamiento* donde, Componente* componente) = 0;
	virtual std::string getMetaData(Componente* componente) = 0;

};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
