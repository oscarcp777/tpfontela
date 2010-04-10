/*
 * KeyPar.h
 *
 *  Created on: 07/04/2010
 *      Author: oscar
 */

#ifndef KEYPAR_H_
#define KEYPAR_H_
#include "../src.datos.utils/Define.h"
class KeyPar {
private:
	INT_UNSIGNED position;
	INT_UNSIGNED offsetCube;
public:
	KeyPar(INT_UNSIGNED position,INT_UNSIGNED offsetCube);
	KeyPar();
	KeyPar* clone();
	virtual ~KeyPar();


	INT_UNSIGNED getOffsetCube() const
    {
        return offsetCube;
    }

	INT_UNSIGNED getPosition() const
    {
        return position;
    }

    void setOffsetCube(INT_UNSIGNED offsetCube)
    {
        this->offsetCube = offsetCube;
    }

    void setPosition(INT_UNSIGNED position)
    {
        this->position = position;
    }

};

#endif /* KEYPAR_H_ */
