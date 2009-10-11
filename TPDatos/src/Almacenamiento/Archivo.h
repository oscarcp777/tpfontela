/*
 * Archivo.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ARCHIVO_H_
#define ARCHIVO_H_

#include "Almacenamiento.h"

class Archivo: public Almacenamiento {
public:
	Archivo(Compuesto* comp);
	std::string toString();
	virtual ~Archivo();
    void guardar(std::string registro);
    void guardar(void* registro,int tamanioRegistro);
    void abrirArchivo(std::string tipoArchivo);
    void cerrarArchivo();
};

#endif /* ARCHIVO_H_ */
