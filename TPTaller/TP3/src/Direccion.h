/*
 * Direccion.h
 *
 *  Created on: 25/05/2009
 *      Author: oscar
 */

#ifndef __DIRECCION_H__
#define __DIRECCION_H__

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
