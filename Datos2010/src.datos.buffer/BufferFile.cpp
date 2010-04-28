/*
 * BufferFile.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "BufferFile.h"



BufferFile::BufferFile(IOBuffer & from):buffer(from) {
}

BufferFile::~BufferFile() {
}

int BufferFile::open(string filename,ios_base::openmode  mode){
    this->file.open(filename.c_str(),ios::in|ios::out|ios::binary);
    if(!this->file.is_open())
    	cout<<"Open File Error"<<endl;
    if(!file.good())return 0;
    file.seekg(0,ios::beg);
    file.seekp(0,ios::beg);
	return file.good();
}

int BufferFile::create(string name,ios_base::openmode mode){
	if(!(mode&ios::out))return 0;
	file.open(name.c_str(),ios::out|ios::binary);
	if(!file.good()){
		file.close();
		return 0;
	}
    this->close();
    this->open(name, mode);
	return headerSize!=0;
}

int BufferFile::close(){
    file.close();
	return 1;
}

int BufferFile::reWind(){
    file.seekg(0,ios::beg);
    file.seekp(0,ios::beg);
	return 1;
}

int BufferFile::read(int addr){
	if(addr==-1)
		return buffer.read(file);
	else
		return buffer.dRead(file,addr);
	return 0;
}

int BufferFile::write(int addr){
	if(addr==-1)
		return buffer.write(file);
	else
		return buffer.dWrite(file,addr);
	return 0;
}

int BufferFile::append(){
	file.seekp(0,ios::end);
	return buffer.write(file);
}

IOBuffer & BufferFile::getBuffer(){
return buffer;
}

