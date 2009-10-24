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

public:
	Metadata();
	virtual ~Metadata();
	int getSize();
	string leer();
	void escribir(std::string dato);

};


#endif /* METADATA_H_ */
