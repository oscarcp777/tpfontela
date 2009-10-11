/*
 * Registro.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_
#include "../../Composite/Componente.h"

class Registro : public Componente{
public:
	Registro(int tamanio);
	virtual ~Registro();
	virtual void serializar()const=0;
	virtual void hidratar()const=0;
	void setAtributo(std::string etiqueta, std::string valor);



};

#endif /* REGISTRO_H_ */
