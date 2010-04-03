/*
 * CubeBuffer.h
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#ifndef CUBEBUFFER_H_
#define CUBEBUFFER_H_
#include "../src.datos.buffer/TextIndexBuffer.h"

class Cube;

class CubeBuffer: public TextIndexBuffer{
public:
	CubeBuffer(int keySize, int maxKeys);
	virtual ~CubeBuffer();
	int pack(const Cube& cube);
	int unPack(Cube& cube);

	friend class Cube;
};

#endif /* CUBEBUFFER_H_ */
