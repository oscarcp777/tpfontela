/*
 * BinaryFile.h
 *
 *  Created on: 24/03/2010
 *      Author: Santiago
 */

#ifndef BINARYFILE_H_
#define BINARYFILE_H_

#include "File.h"

class BinaryFile: public File {
public:
	BinaryFile();
	virtual ~BinaryFile();

	void create(string fileName);
	void open(string fileName);

};

#endif /* BINARYFILE_H_ */
