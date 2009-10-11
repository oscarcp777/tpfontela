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
class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	virtual void guardar(Almacenamiento* donde);
	std::string toString();
	void generarClaves(Almacenamiento* donde);
	std::string getRegistro(Componente* componente);

};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
