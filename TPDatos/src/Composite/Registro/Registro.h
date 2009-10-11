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
	virtual void serializar() =0;
	virtual void hidratar() =0;
	void setAtributo(std::string etiqueta, std::string valor);
	std::string getAtributo(std::string etiqueta);
    std::string getDatosRegistro() const;
    void setDatosRegistro(std::string datosRegistro);

private:
	std::string datosRegistro;

};

#endif /* REGISTRO_H_ */
