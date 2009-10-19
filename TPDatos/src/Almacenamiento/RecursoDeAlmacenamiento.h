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
#include "../Composite/Componente.h"
#include "../Composite/Compuesto.h"
#ifndef RECURSOSALMACENAMIENTO_H_
#define RECURSOSALMACENAMIENTO_H_

class RecursoDeAlmacenamiento :public Object{
	private:

	vector<Almacenamiento*> almacenamientos;
	EstrategiaAlmacenamiento* estrategiaAlmacenamiento;
	EstrategiaRecurso* estrategiaRecurso;
	EstrategiaIndice* estrategiaIndice;
public:
	std::string toString();
	RecursoDeAlmacenamiento();
	RecursoDeAlmacenamiento(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,Almacenamiento* archivo,Almacenamiento* buffer,  EstrategiaRecurso* estrategiaRecurso,EstrategiaIndice* estrategiaIndice );
	virtual ~RecursoDeAlmacenamiento();
	void crearArchivo();
	void busquedaSecuencial(Componente* componente, std::string clave);

	/**
	 * guarda el archivo especificado con los datos cargados de los registros
	 * en caso de no tener registros genera el archivo vacio
	 * return : en caso de error devulve -1
	 */
    int escribirArchivo(std::string ruta,std::string nombreArchivo);
    /**
     * levantaa memoria los registros de este archivo que recibe por parametro
     * return : en caso de error devulve -1
     */
    int leerArchivo(std::string ruta,std::string nombreArchivo);
    
    /**
     *este metodo carga en el compuesto el registro que se le pasa por parametro
     */
    int cargarComponente(Componente* componente);



};

#endif /* RECURSOSALMACENAMIENTO_H_ */
