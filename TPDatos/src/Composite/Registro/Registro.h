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
	virtual std::string getClaveObjeto() = 0;
	virtual void serializarObjeto() =0;
	virtual void hidratarObjeto() =0;
	void setAtributo(std::string etiqueta, std::string valor);
	std::string getAtributo(std::string etiqueta);
    std::string getDatosRegistro();
    void setDatosRegistro(std::string datosRegistro);

private:
	std::string datosRegistro;

};

#endif /* REGISTRO_H_ */
