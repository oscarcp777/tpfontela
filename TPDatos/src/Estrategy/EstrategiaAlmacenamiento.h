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
#include "../utils/StringUtils.h"
#include <sstream>
#include <iostream>

class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	virtual void guardar(Almacenamiento* donde) = 0;
	std::string toString();
	virtual void agregarComponente(Almacenamiento* donde, Componente* componente) = 0;
	virtual void quitarComponente(Almacenamiento* donde, Componente* componente) = 0;
	virtual void busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave) = 0;

protected:
	virtual std::string generarRegistro(Componente* componente);
	std::string generarMetadata(Componente* componente);
};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
