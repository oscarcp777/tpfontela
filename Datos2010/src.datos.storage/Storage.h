/*
 * Almacenamiento.h
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
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


public:
	Storage();
	virtual ~Storage();

	virtual void create() = 0;
	virtual void open() =0;
	virtual void read(std::string & datos, int pos) =0;
    virtual void read(char *buffer, int pos) =0;
	virtual int write(std::string registro, int pos) = 0;
	virtual int write(char* buffer, int pos = -1) = 0;
	virtual void close() =0;

	string toString();

	//evaluar existencia
    virtual void irAlPrincipio() = 0;
    virtual bool fin() = 0;

};

#endif /* STORAGE_H_ */
