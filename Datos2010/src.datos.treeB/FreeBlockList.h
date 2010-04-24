/*
 * FreeBlockList.h
 *
 *  Created on: 24/04/2010
 *      Author: Santiago
 */

#ifndef FREEBLOCKLIST_H_
#define FREEBLOCKLIST_H_

#include "../src.datos.buffer/FixedFieldBuffer.h"
#include "../src.datos.buffer/BufferFile.h"
#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FreeBlockList {
public:
	FreeBlockList(int blocksize);
	virtual ~FreeBlockList();


private:
	FixedFieldBuffer buffer;
	BufferFile bTreeFile;

};

#endif /* FREEBLOCKLIST_H_ */
