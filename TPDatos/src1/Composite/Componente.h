/*
 * Componente.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef COMPONENTE_H_
#define COMPONENTE_H_
#include <iostream>

#include "../Object/Object.h"
#include "../utils/Define.h"
#include <map>
using namespace std;
class Componente :public Object {

private:
	int tamanio;
    int id;
    int posicionActual;
protected:
    string clave;
    char *buffer;
    int tamanioBuffer;
    int nextByte;
public:
    virtual void serializar(string tipo) =0;
    virtual void hidratar(string tipo) =0;
    virtual Componente* obtenerNuevaInstancia() = 0;
    virtual int compareTo(std::string clave) = 0;
    Componente();
    virtual ~Componente();
    int getTamanio();
    void setTamanio(int tamanio);
    string getClave() const;


    void setClave(string clave);

    int getPosicionActual() const;
    void setPosicionActual(int posicionActual);
    int getId() const;
    void setId(int id);
    char *getBuffer() const;
    void setBuffer(char *buffer);
    int getTamanioBuffer() const;
    void setTamanioBuffer(int tamanioBuffer);
};

#endif /* COMPONENTE_H_ */
