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
	Archivo();
	std::string toString();
	virtual ~Archivo();
    void guardar(std::string registro);
    void guardar(const char* registro,int tamanioRegistro);
    
    void abrirArchivo(std::string tipoArchivo);
    void cerrarArchivo();
    void leer(void* datos, int tamanio);
    bool fin();
    int getExisteMetaData();
    void setExisteMetaData(int existeMetaData);

private:
    int existeMetaData;
};

#endif /* ARCHIVO_H_ */
