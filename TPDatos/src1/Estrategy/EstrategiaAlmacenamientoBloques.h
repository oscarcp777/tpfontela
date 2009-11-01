/*
 * EstrategiaAlmacenamientoBloques.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ESTRATEGIAALMACENAMIENTOBLOQUES_H_
#define ESTRATEGIAALMACENAMIENTOBLOQUES_H_

#include "EstrategiaAlmacenamiento.h"



class EstrategiaAlmacenamientoBloques: public EstrategiaAlmacenamiento {
public:
	std::string toString();
	EstrategiaAlmacenamientoBloques();
	virtual ~EstrategiaAlmacenamientoBloques();
    void guardar(Almacenamiento* donde);
    std::string generarRegistro(Componente* componente);
    int altaComponente(Almacenamiento* donde, Componente* componente);
    void quitarComponente(Almacenamiento* donde, Componente* componente, int pos);
    void busquedaSecuencial(list<Componente*> &resultadoDeLABusqueda, Componente* componente, Almacenamiento* donde,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
    void hidratarComponente(Almacenamiento* donde,list<Componente*> &resultadoDeLABusqueda,Componente* componente,int pos,vector<string> vecCampos, vector<int> vecEtiquetasCampos);
private:
	int posicionarEnBloque(int tamanioRegistro);
};

#endif /* ESTRATEGIAALMACENAMIENTOBLOQUES_H_ */
