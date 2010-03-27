/*
 * TestIOFile.cpp
 *
 *  Created on: 27/03/2010
 *      Author: Santiago
 */

#include "TestIOFile.h"

#define BUFFER_SIZE 1024

TestIOFile::TestIOFile() {

}

TestIOFile::~TestIOFile() {

}

void TestIOFile::runBinaryFileTest(){

	BinaryFile* bFile = new BinaryFile();
	char* buffer = new char[BUFFER_SIZE];

	memcpy (&buffer[0],"Santiago Donikian, 31993745, Argentina",BUFFER_SIZE);

	bFile->create("files/binaryTest");
	bFile->write(buffer,0,BUFFER_SIZE);
	bFile->close();

	memset(buffer,0,BUFFER_SIZE);
	try{
		bFile->open("files/binaryTest");

		bFile->read(buffer,0,BUFFER_SIZE);
		cout << buffer;
		bFile->close();

	}catch (string& e){
		cerr << e << endl;
		return 1;
	}
}

void TestIOFile::runTextFileTest(){
	TextFile* text= new TextFile();
	text->open("files/textFile");
	string datos;
	//	text->read(datos);
	text->write("esto es para vos nelson castro 3333");
	text->close();
}

int main(){
	TestIOFile* test = new TestIOFile();
	test->runBinaryFileTest();
//	test->runTextFileTest();

	return 0;
}
