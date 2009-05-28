/*
 * Direccion.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef DIRECCION_H_
#define DIRECCION_H_

class Direccion {
public:
	Direccion();
	virtual ~Direccion();

    double getFi();
    void setFi(double fi);

private:
	double fi;
};

#endif /* DIRECCION_H_ */
