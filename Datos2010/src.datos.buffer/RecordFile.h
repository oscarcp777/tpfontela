/*
 * RecordFile.h
 *
 *  Created on: 02/04/2010
 *      Author: oscar
 */

#ifndef RECORDFILE_H_
#define RECORDFILE_H_

#include "BufferFile.h"
template <class RecType>
class RecordFile: public BufferFile {
public:

	int read(RecType&record,int recaddr);
	int write(const RecType &record,int recaddr);
   int append(const RecType &record);
   RecordFile(IOBuffer& buffer):BufferFile(buffer){}

};
template <class RecType>
int RecordFile<RecType>::read(RecType&record,int recaddr=-1){
 int readAddr,result;
 readAddr=BufferFile::read(recaddr);
 if(!readAddr)return -1;
 result=record.unpack(this->buffer);
 if(!result)return -1;
 return readAddr;
}
template <class RecType>
int RecordFile<RecType>::write(const RecType &record,int recaddr=-1){
	int result;
	result=record.pack(this->buffer);
	if(!result) return -1;
	return BufferFile::write(recaddr);

}
template <class RecType>
 int RecordFile<RecType>::append(const RecType &record){
	int result;
		result=record.pack(this->buffer);
		if(!result) return -1;
		return BufferFile::append();
}
#endif /* RECORDFILE_H_ */