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
#include "../Composite/Bloque/Bloque.h"
#include "../Composite/Registro/Registro.h"
#include "../utils/StringUtils.h"
#include <sstream>
#include <iostream>
#include <vector>

class EstrategiaAlmacenamiento :public Object{
public:
	EstrategiaAlmacenamiento();
	virtual ~EstrategiaAlmacenamiento();
	std::string toString();
	virtual int altaComponente(Almacenamiento* donde, Componente* componente) = 0;
	virtual void quitarComponente(Almacenamiento* donde, Componente* componente, int pos) = 0;
	virtual int actualizarComponente(Almacenamiento* donde, Componente* componente, int pos) = 0;
	virtual void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos) = 0;
virtual void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos)=0;
};

#endif /* ESTRATEGIAALMACENAMIENTO_H_ */
