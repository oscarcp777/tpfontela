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
#include "../utils/StringUtils.h"
#include "Archivo.h"
#ifndef METADATA_H_
#define METADATA_H_

using namespace std;

class Metadata:public Archivo{

private:
    string primerRegistro;
    string segundoRegistro;
    string tercerRegistro;
    vector<string> mapaAtributosFijos;
    map<int,int> mapaTamanioBloques;
    map<int,int> mapaPosicionesAInsertarTexto;
    vector<string> vectorAtributosVariables;
    vector<string> atributosRegistro;
    int metadataSize;
    bool archivo;
    string tipo;
public:
	Metadata();
	virtual ~Metadata();
	int getSize();
	void getPosicionBloque(int tamanioBuscado,vector<int>& posiciones);
	void hidratarMetadata();
	string getContenido();
    void setMetadataSize(int metadataSize);
    void leerMetadata();
     void escribirMetadata(string estrAlmacenamiento,int tamanio,string clavePrimaria,string tipoIndexacion,string nombreAtributos);
    string getValorAtributosFijos(string clave);
    string getClavePrimaria();
    int getEspacioLibreEnBloque(int bloque);
    int getNumeroEtiqueta(std::string etiqueta);
    void guardarMapaAtributosVariables(map<int,int> mapaAtributosVariables);
    int getPosicionLibreRegistro();
    void setPosicionLibreRegistro(int posicionRegistroLibre);
    void guardarVectorAtributosVariables();
    void hidratarMetadataEnBuffer(string registroAtributos,int tamanio);
    void actualizarMapaAtributosVariables(int posicion,int espacioLiberado);
    void setPosicionLibreEnTexto(int posicionEnDisco,int espacioOcupado);
    void getPosicionLibreEnTexto(int tamanioBuscado,vector<int>& posiciones);
    void actualizarMetadata(string estrategiaAlmacenamiento);
    string getTipo() const
    {
        return tipo;
    }

    void setTipo(string tipo)
    {
        this->tipo = tipo;
    }

    bool isArchivo()
    {
        return archivo;
    }

    void setArchivo(bool archivo)
    {
        this->archivo = archivo;
    }

    int getMetadataSize()
    {
        return metadataSize;
    }

    string getPrimerRegistro()
    {
        return primerRegistro;
    }

    string getSegundoRegistro()
    {
        return segundoRegistro;
    }

    string getTercerRegistro()
    {
        return tercerRegistro;
    }

    void setPrimerRegistro(string primerRegistro)
    {
        this->primerRegistro = primerRegistro;
    }

    void setSegundoRegistro(string segundoRegistro)
    {
        this->segundoRegistro = segundoRegistro;
    }

    void setTercerRegistro(string tercerRegistro)
    {
        this->tercerRegistro = tercerRegistro;
    }

};


#endif /* METADATA_H_ */
