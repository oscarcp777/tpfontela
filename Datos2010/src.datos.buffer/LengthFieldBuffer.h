/*
 * LengthFieldBuffer.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef LENGTHFIELDBUFFER_H_
#define LENGTHFIELDBUFFER_H_


class LengthFieldBuffer {
public:
	LengthFieldBuffer();
	virtual ~LengthFieldBuffer();
	int clear();
	int pack(const void* field, unsigned int size=-1);
	int unPack(void* field, unsigned int maxBytes=-1);
};

#endif /* LENGTHFIELDBUFFER_H_ */
