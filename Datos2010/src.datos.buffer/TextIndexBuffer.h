/*
 * TextIndexBuffer.h
 *
 *  Created on: 02/04/2010
 *      Author: richy
 */

#ifndef TEXTINDEXBUFFER_H_
#define TEXTINDEXBUFFER_H_
#include "FixedFieldBuffer.h"
#include "TextIndex.h"


class TextIndexBuffer: public FixedFieldBuffer {
public:
	TextIndexBuffer(int keySize, int maxKeys= 100, int extraFields=0, int extraSize=0);
	virtual ~TextIndexBuffer();
	int pack(const TextIndex& index);
	int unPack(TextIndex& index);
	void print();
protected:
	int keySize;
	int maxKeys;
	char *dummy; //space for dummy in pack and unpack

};

#endif /* TEXTINDEXBUFFER_H_ */
