/*
 * Metadata.h
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */
#include <map>
#include <vector>
#include <string>
#include <fstream>
#include <stdio.h>

#include "../utils/Define.h"
#ifndef METADATA_H_
#define METADATA_H_

using namespace std;

class Metadata {
private:
    string nombreArchivo;
    string contenido;
    map<string,string> mapaAtributosFijos;
    map<string,string> mapaAtributosVariables;

    vector<string> atributosRegistro;
    int metadataSize;
    fstream  archivo;

public:public:
	Metadata();
	virtual ~Metadata();
	int getSize();
	string leer();
	void escribir(std::string dato);
	string getContenido();
    string getNombreArchivo();
    void setAtributoFijos(string clave,string valor);
    void setAtributoVariable(string clave,string valor);
    void setMetadataSize(int metadataSize);
    void setNombreArchivo(string nombreArchivo);
    void abrirArchivo();
    void cerrarArchivo();
    void crearArchivo();
    void escribirArchivo(const void* registro, int tamanio);
    void irAlPrincipio();
    void irAlFinal();
    void guardar(std::string registro);
    void guardarPrimeraLinea(std::string registro);




};


#endif /* METADATA_H_ */
