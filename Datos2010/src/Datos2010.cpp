//============================================================================
// Name        : Datos2010.cpp
// Author      : Oscar
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../hashExtensible/HashExtensible.h"
using namespace std;

int main() {





/*	BinaryFile* file=  new BinaryFile();
	file->open("files/binary");
	Buffer* buffer= new Buffer(18);
	buffer->setBufferSize(18);
	file->read(buffer->getData(),18);
	char* pvar=new char[10];
	 int num=0;
	 int num2=0;
	  buffer->unPackField(pvar,10);
	  buffer->unPackField(&num,sizeof(num));
	  buffer->unPackField(&num2,sizeof(num));
	  cout << "!!!var!!!  :"<<pvar<<endl;
	  cout << "!!!var1!!!  :"<<num<<endl;
	  cout << "!!!var2!!!  :"<<num2<<endl;
	  delete pvar;*/
	/*
  Buffer* buffer= new Buffer(25);
  buffer->packField("0123456789");
  int num=10;
  int num2=113;
  buffer->packField(&num,sizeof(num));
  buffer->packField(&num2,sizeof(num));
  buffer->print();
  file->write(buffer->buffer,buffer->bufferSize);
  file->close();
  buffer->init();
  char* pvar=new char[10];
  num=0;
  num2=0;
  buffer->unPackField(pvar,10);
  buffer->unPackField(&num,sizeof(num));
  buffer->unPackField(&num2,sizeof(num));
  cout << "!!!var!!!  :"<<pvar<<endl;
  cout << "!!!var1!!!  :"<<num<<endl;
  cout << "!!!var2!!!  :"<<num2<<endl;
  delete pvar;

  buffer->clear();
  buffer->print();

  delete buffer; */

	return 0;

}
