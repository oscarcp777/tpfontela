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


	void serializar(string tipo);
	void hidratar(string tipo);
	void clear();

	virtual string getClaveObjeto() = 0;
	virtual void serializarBinario() =0;
	virtual void hidratarBinario() =0;
	virtual void serializarTexto() =0;
	virtual void hidratarTexto() =0;

	int setAtributo(string etiqueta, const void* campo, int tamanio = -1);
	int getAtributo(void* campo, int tamanio = -1);

	void Init();

};

#endif /* REGISTRO_H_ */
