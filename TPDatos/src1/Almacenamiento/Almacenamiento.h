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
using namespace std;
class Almacenamiento:public Object{


private:
    Compuesto *compuesto;
    string nombreArchivo;
    int cantidadRegistrosEnMemoria;
    int tamanio;
    string tipoArchivo;
    string clavePrimaria;
public:

    Almacenamiento();
    virtual ~Almacenamiento();
    Compuesto *getCompuesto();
   string toString();
    virtual string getClass();
    void agregarComponente(Componente *componente);

    virtual void irAlPrincipio() = 0;
    virtual bool fin() = 0;
    void setNombreArchivo(std::string nombreArchivo);
    void setRuta(std::string ruta);
    int getTamanio();
    void setTamanio(int tamanio);
    void setTipoArchivo(std::string tipoArchivo);
   string getTipoArchivo();

    virtual void guardar(std::string registro) = 0;
    virtual void guardar() = 0;

    virtual void leer(void *datos, int tamanio) =0;
    virtual void abrir() =0;
    virtual void cerrar() =0;
    int getExisteMetaData();
    virtual string leerMetadata() =0;
    virtual void escribirMetadata(std::string metadata) =0;
    int getCantidadRegistrosEnMemoria();

    void setCantidadRegistrosEnMemoria(int cantidadRegistrosEnMemoria);
    string getClavePrimaria() ;

    void setClavePrimaria(string clavePrimaria);

protected:
	fstream  archivo;
	string ruta;
	int metadataSize;
	string metaData;

	string getPath();

};

#endif /* ALMACENAMIENTO_H_ */
