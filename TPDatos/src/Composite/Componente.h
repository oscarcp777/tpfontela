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
	int id;
	int posicionActual;
protected:
	std::map<std::string ,std::string> mapaAtributos;
	std::string clave;
public:

	virtual	void serializar() =0;
	virtual void hidratar() =0;
	Componente();
	virtual ~Componente();
    int getTamanio();
    void setTamanio(int tamanio);
    std::map<std::string,std::string>::iterator  iteratorCampos();
    std::map<std::string,std::string>::iterator  finIteratorCampos();
    std::string getClave() const;
    std::map<std::string,std::string> getMapaAtributos();
    void cargarAtributo(std::string clave, std::string valor);
    void setClave(std::string clave);
    virtual std::string getDatosRegistro() = 0;
    virtual void setDatosRegistro(std::string datosRegistro) = 0;
    int getPosicionActual() const;
    void setPosicionActual(int posicionActual);
    int getId() const;
    void setId(int id);

};

#endif /* COMPONENTE_H_ */
