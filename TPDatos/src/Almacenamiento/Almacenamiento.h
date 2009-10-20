/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ALMACENAMIENTO_H_
#define ALMACENAMIENTO_H_



#include "../Composite/Compuesto.h"
#include "../Composite/Componente.h"
#include "../utils/Define.h"
#include "../Object/Object.h"
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>

class Almacenamiento:public Object{


private:
    Compuesto *compuesto;
    std::string nombreArchivo;

    int tamanio;
    std::string tipoArchivo;

public:

    Almacenamiento();
    virtual ~Almacenamiento();
    Compuesto *getCompuesto();
    std::string toString();
    virtual std::string getClass();
    void agregarComponente(Componente *componente);

    void setNombreArchivo(std::string nombreArchivo);
    void setRuta(std::string ruta);
    int getTamanio();
    void setTamanio(int tamanio);
    void setTipoArchivo(std::string tipoArchivo);
    std::string getTipoArchivo();

    virtual void guardar(std::string registro) = 0;
    virtual void guardar(const char* registro,int tamanioRegistro) = 0;
   // virtual std::string leer () = 0;
    virtual void leer(void* datos, int tamanio) = 0;

    virtual void abrir() = 0;
    virtual void cerrar() = 0;


    int getExisteMetaData();
    virtual std::string leerMetadata();
    virtual void escribirMetadata(std::string metadata);

protected:
	std::fstream  archivo;
	std::string ruta;
	int metadataSize;
	std::string metaData;

};

#endif /* ALMACENAMIENTO_H_ */
