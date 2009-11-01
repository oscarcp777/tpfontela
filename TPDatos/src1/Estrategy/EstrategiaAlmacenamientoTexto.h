/*
 * EstrategiaAlmacenamientoTexto.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOTEXTO_H_
#define ESTRATEGIAALMACENAMIENTOTEXTO_H_
#include "EstrategiaAlmacenamiento.h"
#include <list>
#include <iterator>
class EstrategiaAlmacenamientoTexto: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoTexto();
	virtual ~EstrategiaAlmacenamientoTexto();
    void guardar(Almacenamiento* donde);
    std::string generarRegistro(Componente* componente);
    int altaComponente(Almacenamiento* donde, Componente* componente);
    void quitarComponente(Almacenamiento* donde, Componente* componente, int pos);
    void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde, std::string clave);
    void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,string clavePrimaria, int numEtiquetaClave);
};

#endif /* ESTRATEGIAALMACENAMIENTOTEXTO_H_ */
