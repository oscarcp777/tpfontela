/*
 * Hash.h
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#ifndef HASH2_H_
#define HASH2_H_
#include "../src.datos.utils/Object.h"

//create the primary hash value from a string
int hash(int key);

//get the primary hash, reverse the bits, return an address of depth bits
int makeAddress(int key, int depth);


#endif /* HASH_H_ */
