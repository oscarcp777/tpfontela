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

    float getFi();
    void setFi(float fi);

private:
		float fi;
};

#endif /* DIRECCION_H_ */
