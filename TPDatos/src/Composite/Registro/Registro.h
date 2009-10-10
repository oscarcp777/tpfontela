/*
 * Registro.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef REGISTRO_H_
#define REGISTRO_H_
#include <map>
#include "../../Composite/Componente.h"

class Registro : public Componente{
public:
	Registro(int tamanio);
	virtual ~Registro();
	virtual void serializar()const=0;
	virtual void hidratar()const=0;
	void setAtributo(std::string etiqueta, std::string valor);

private:
	void* datos;
	std::string clave;
	std::map<std::string ,std::string> mapaAtributos;
};

#endif /* REGISTRO_H_ */
