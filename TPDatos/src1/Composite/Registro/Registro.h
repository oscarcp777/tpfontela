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
	Registro();
	virtual ~Registro();


	void serializar();
	void hidratar();
	void clear();
	virtual std::string getClaveObjeto() = 0;
	virtual void serializarBinario() =0;
	virtual void hidratarBinario() =0;
	int setAtributo(std::string etiqueta, const void* campo, int tamanio);
	int getAtributo(void* campo, int tamanio = -1);


private:
	std::string datosRegistro;




};

#endif /* REGISTRO_H_ */
