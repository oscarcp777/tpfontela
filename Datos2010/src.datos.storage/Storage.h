/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef STORAGE_H_
#define STORAGE_H_



#include <stdio.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include "../src.datos.utils/Object.h"
#include "../src.datos.utils/Define.h"
using namespace std;
class Storage:public Object{


private:

	string nombreArchivo;
	int cantidadRegistrosEnMemoria;
	int tamanio;
	string tipoArchivo;
	string clavePrimaria;
public:

	Storage();
	virtual ~Storage();
	string toString();
	virtual string getClass();

	virtual void irAlPrincipio() = 0;
	virtual bool fin() = 0;
	void setNombreArchivo(std::string nombreArchivo);
	void setRuta(std::string ruta);
	int getTamanio();
	void setTamanio(int tamanio);
	void setTipoArchivo(std::string tipoArchivo);
	string getTipoArchivo();

	virtual int guardar(std::string registro, int pos) = 0;

	virtual int guardar(char* buffer, int pos = -1) = 0;
	virtual void crear() = 0;
	//virtual void leer(void *datos, int tamanio) =0;
	virtual void leer(std::string& datos, int pos)=0;
	virtual void leer(char* buffer, int pos) = 0;
	virtual void abrir() =0;
	virtual void cerrar() =0;
	int getCantidadRegistrosEnMemoria();

	void setCantidadRegistrosEnMemoria(int cantidadRegistrosEnMemoria);
	string getClavePrimaria() ;

	void setClavePrimaria(string clavePrimaria);






protected:

	fstream  file;
	string ruta;
	string getPath();

};

#endif /* STORAGE_H_ */
