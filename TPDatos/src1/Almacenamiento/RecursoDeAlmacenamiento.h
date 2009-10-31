/*
 * RecursosAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include "Almacenamiento.h"
#include "Archivo.h"
#include "Buffer.h"
#include "../Estrategy/EstrategiaRecurso.h"
#include "../Estrategy/EstrategiaAlmacenamiento.h"
#include "../Estrategy/EstrategiaIndice.h"
#include "../Estrategy/EstrategiaIndiceBuffer.h"
#include "../Composite/Componente.h"
#include "../Composite/Compuesto.h"
#include <map>
#ifndef RECURSOSALMACENAMIENTO_H_
#define RECURSOSALMACENAMIENTO_H_
using namespace std;
class RecursoDeAlmacenamiento :public Object{
	private:

	vector<Almacenamiento*> almacenamientos;
	EstrategiaAlmacenamiento* estrategiaAlmacenamiento;
	EstrategiaRecurso* estrategiaRecurso;
	vector<EstrategiaIndice*> estrategiaIndices;
public:
	std::string toString();
	RecursoDeAlmacenamiento();
	RecursoDeAlmacenamiento(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,Almacenamiento* archivo,Almacenamiento* buffer,  EstrategiaRecurso* estrategiaRecurso,
			               EstrategiaIndice* estrategiaIndice ,EstrategiaIndiceBuffer* estrategiaIndiceBuffer);
	virtual ~RecursoDeAlmacenamiento();
	void busquedaSecuencial(Componente* componente, std::string clave);

	/**
	 *este metodo se encarga de persistir el registro en le archivo
	 */
    int alta(Componente* componente);
    /**
     * Elimina un registro del archivo
     */
    int baja(Componente* componente);
    /**
     * modifica un registro ya existente
     */
    int modificion(Componente* componente);
    /**
     *pre: ninguna
     *post: este metodo se encarga de la busquedas de registros
     */
    int buscar(list<Componente*> &resultadoDeLABusqueda,Componente* componente,std::string clave);
    /**
     *pre :ninguna
     *este metodo se encarga de actualizar la metadata del recurso de lamacenamineto
     */
     void cerrar();

};

#endif /* RECURSOSALMACENAMIENTO_H_ */
