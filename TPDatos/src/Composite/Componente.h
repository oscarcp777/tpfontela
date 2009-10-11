/*
 * Componente.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef COMPONENTE_H_
#define COMPONENTE_H_
#include <iostream>

#include "../Object/Object.h"
#include <map>
class Componente :public Object {

private:
	int tamanio;
	std::string clave;
protected:
	std::map<std::string ,std::string> mapaAtributos;

public:

   virtual	void serializar() =0;
	virtual void hidratar() =0;
	Componente(int tamanio);
    Componente();
	virtual ~Componente();
    int getTamanio();
    void setTamanio(int tamanio);
    std::map<std::string,std::string>::iterator  iteratorCampos();
    std::map<std::string,std::string>::iterator  finIteratorCampos();
    std::string getClave() const;
    std::map<std::string,std::string> getMapaAtributos() const;
    void setClave(std::string clave);
    virtual std::string getDatosRegistro() const = 0;
    virtual void setDatosRegistro(std::string datosRegistro) = 0;



};

#endif /* COMPONENTE_H_ */
