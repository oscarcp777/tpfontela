/*
 * RecordFile.h
 *
 *  Created on: 02/04/2010
 *      Author: oscar
 */

#ifndef RECORDFILE_H_
#define RECORDFILE_H_

#include "BufferFile.h"
#include "FixedFieldBuffer.h"
template <class RecType>
class RecordFile: public BufferFile {
public:

	RecordFile(IOBuffer& buffer):BufferFile(buffer){}

	int read(RecType&record,int recaddr = -1){
		int readAddr,result;
		readAddr=BufferFile::read(recaddr);
		if(!readAddr)return -1;
		result=record.unpack(this->buffer);
		if(!result)return -1;
		return readAddr;
	}

	int read(FixedFieldBuffer & buffer){
		return buffer.read(file);
	}

	int append(const RecType &record){
		int result;
		result=record.pack(this->buffer);
		if(!result) return -1;
		return BufferFile::append();
	}

	int write(const RecType&record,int recaddr = -1){
		int result;
		result= record.pack(this->buffer);
		if(!result) return -1;
		return BufferFile::write(recaddr);

	}

	int write(FixedFieldBuffer & buffer){
			return buffer.write(file);
	}

};


#endif /* RECORDFILE_H_ */
