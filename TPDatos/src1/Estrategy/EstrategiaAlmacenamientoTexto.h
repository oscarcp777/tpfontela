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
    int actualizarComponente(Almacenamiento* donde, Componente* componente, int pos);
    void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
    void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
};

#endif /* ESTRATEGIAALMACENAMIENTOTEXTO_H_ */
