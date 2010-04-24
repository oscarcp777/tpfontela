/*
 * FreeBlockList.cpp
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#include "FreeBlockList.h"

FreeBlockList::FreeBlockList(int blockSize)
	:buffer((2*blockSize)/sizeof(int),2*blockSize ),
	 bTreeFile(buffer){
	int i;
	int maxFields = (2*blockSize)/sizeof(int);
	for (i = 0; i < maxFields; ++i) {
		this->buffer.addField(sizeof(int));
	}

}

FreeBlockList::~FreeBlockList() {
	// TODO Auto-generated destructor stub
}
