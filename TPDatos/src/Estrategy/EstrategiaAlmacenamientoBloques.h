/*
 * EstrategiaAlmacenamientoBloques.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOBLOQUES_H_
#define ESTRATEGIAALMACENAMIENTOBLOQUES_H_

#include "EstrategiaAlmacenamiento.h"
#include <vector>


class EstrategiaAlmacenamientoBloques: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoBloques();
	virtual ~EstrategiaAlmacenamientoBloques();
    void guardar(Almacenamiento* donde);
    std::string generarRegistro(Componente* componente);
    void agregarComponente(Almacenamiento* donde, Componente* componente);
    std::string getMetaData(Componente* componente);
    void busquedaSecuencial(Componente* componente, Almacenamiento* donde,std::string clave);


};

#endif /* ESTRATEGIAALMACENAMIENTOBLOQUES_H_ */
