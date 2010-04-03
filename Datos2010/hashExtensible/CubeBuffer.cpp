/*
 * CubeBuffer.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "CubeBuffer.h"
#include "Cube.h"

CubeBuffer::CubeBuffer(int keySize, int maxKeys):TextIndexBuffer(keySize,maxKeys,1,sizeof(int)) {
	this->addField(sizeof(int));
}

CubeBuffer::~CubeBuffer() {
	// TODO Auto-generated destructor stub
}

int CubeBuffer::pack(const Cube& cube){
	int result;
	result = TextIndexBuffer::pack(cube);
	if(result == -1) return -1;
	return FixedFieldBuffer::pack(&cube.depth);


}
int CubeBuffer::unPack(Cube& cube){
	int result;
	result = TextIndexBuffer::unPack(cube);
	if(result == -1) return -1;
	return FixedFieldBuffer::unPack(&cube.depth);
}
