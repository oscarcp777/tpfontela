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
    std::string clave;
    char *buffer;
    int tamanioBuffer;
    int nextByte;
public:
    virtual void serializar() =0;
    virtual void hidratar() =0;
    Componente();
    virtual ~Componente();
    int getTamanio();
    void setTamanio(int tamanio);
    std::string getClave() const;


    void setClave(std::string clave);

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
