/*
 * Nota.h
 *
 *  Created on: 11/10/2009
 *      Author: richy
 */

#ifndef NOTA_H_
#define NOTA_H_

#include "../Composite/Registro/Registro.h"
#include <sstream>

class Nota : public Registro{
public:
	Nota(int n);
	virtual ~Nota();

	void serializar();
	void hidratar();

private:
	int nota;

};

#endif /* NOTA_H_ */
