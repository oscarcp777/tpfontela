/*
 * Hash.h
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#ifndef HASH_H_
#define HASH_H_
#include "../src.datos.utils/Object.h"
class Hash{
public:
//create the primary hash value from a string
int static hash(char* key);

//get the primary hash, reverse the bits, return an address of depth bits
int static makeAddress(char* key, int depth);
int static hashMod(int key,int sizeTable);
};

#endif /* HASH_H_ */
