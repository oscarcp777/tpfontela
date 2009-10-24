/*
 * Metadata.h
 *
 *  Created on: 23/10/2009
 *      Author: oscar
 */
#include <map>
#include <vector>
#include <string>
#ifndef METADATA_H_
#define METADATA_H_
using namespace std;
class Metadata {
private:
    string nombreArchivo;
    string contenido;
    map<string,string> mapaAtributosArchivo;
    vector<string> atributosRegistro;
    int metadataSize;
public:
	Metadata();
	virtual ~Metadata();
};

#endif /* METADATA_H_ */
