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
#include "../Almacenamiento/Metadata.h"
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
	virtual int altaComponente(Almacenamiento* donde, Componente* componente) = 0;
	virtual void quitarComponente(Almacenamiento* donde, Componente* componente, int pos) = 0;
	virtual void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,std::string clave) = 0;
	virtual void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos, string clavePrimaria, int numEtiquetaClave)=0;
	Metadata *getMetadata()
    {
        return metadata;
    }

    void setMetadata(Metadata *metadata)
    {
        this->metadata = metadata;
    }

protected:

	std::string generarMetadata(Componente* componente);
	Metadata* metadata;
};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
