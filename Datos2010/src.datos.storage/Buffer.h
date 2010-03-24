/*
 * Buffer.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef BUFFER_H_
#define BUFFER_H_

#include "Storage.h"
#include <stdio.h>

using namespace std;
class Buffer: public Storage {

private:
	char* datos;
	int posicionActual;
	int posicionActualLectura;
	int cantElementos;
	int cantLineas;
	int cantlineasLeidas;
	bool binario;
	bool texto;
	int size;

public:
	Buffer();
	virtual ~Buffer();
	std::string toString();
	std::string getClass();
	void open();
	void close();
	void irAlPrincipio();
	bool fin();
	void create();
	int write(std::string registro, int pos);
	int write(char* buffer, int pos = -1);
	void read(std::string& datos, int pos);
	void read(char* buffer, int pos);



};

#endif /* BUFFER_H_ */
