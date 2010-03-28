/*
 * Object.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef OBJECT_H_
#define OBJECT_H_
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include "Define.h"
#include "../src.datos.logger/Logger.h"

class Object {
public:
	Object();
	virtual std::string toString();
	virtual ~Object();
};

#endif /* OBJECT_H_ */
