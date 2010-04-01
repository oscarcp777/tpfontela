/*
 * BufferFile.cpp
 *
 *  Created on: 28/03/2010
 *      Author: Richard
 */

#include "BufferFile.h"

BufferFile::BufferFile() {

}

BufferFile::BufferFile(IOBuffer & from) {
	// TODO Auto-generated constructor stub

}
BufferFile::~BufferFile() {
	// TODO Auto-generated destructor stub
}
int BufferFile::open(char* filename, int mode){
	if(mode&ios::noreplace||mode&ios::trunc) return FALSE;
    this->file.open(filename,mode|ios::in|ios::nocreate|ios::binary);
    if(!file.good())return FALSE;
    file.seekg(0,ios::beg);file.seekp(0,ios::beg);
    HeaderSize=ReadHeader();
    if(!HeaderSize)return FALSE;
    file.seekg(HeaderSize,ios::beg);file.seekp(HeaderSize,ios::beg);
	return file.good();
}
int BufferFile::close(){
    file.close();
	return TRUE;
}
int BufferFile::read(int addr){
	return 0;
}
int BufferFile::write(int addr){
	return 0;
}
int BufferFile::create(char* name,int mode){
	if(!(mode&ios::out))return FALSE;
	file.open(name,mode|ios::out|ios::nocreate|ios::binary);
	if(!file.good()){
		file.close();
		return FALSE;
	}
	       HeaderSize=WriteHeader();
		return HeaderSize!=0;

}
int BufferFile::ReWind(){
    file.seekg(HeaderSize,ios::beg);file.seekp(HeaderSize,ios::beg);
	return 1;
}
int BufferFile::append(){
	return 0;
}

