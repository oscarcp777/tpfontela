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
class Object {
public:
	Object();
	virtual std::string toString();
	virtual ~Object();
};

#endif /* OBJECT_H_ */
