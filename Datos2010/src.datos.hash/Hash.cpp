/*
 * Hash.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */
#include "Hash.h"
int Hash::hashMod(int key,int sizeTable){
   return (key % sizeTable);
}
