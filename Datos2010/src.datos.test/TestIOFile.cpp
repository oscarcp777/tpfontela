/*
 * TestIOFile.cpp
 *
 *  Created on: 27/03/2010
 *      Author: Santiago
 */

#include "TestIOFile.h"

#define BUFFER_SIZE 1024
#define BLOCK_SIZE	256

TestIOFile::TestIOFile() {

}

TestIOFile::~TestIOFile() {

}

void TestIOFile::runBinaryFileTest(){

	//TODO reemplazar al char* buffer por un objeto Buffer

	BinaryFile* bFile = new BinaryFile();
	char* buffer = new char[BUFFER_SIZE];

	//Datos a guardar
	string inputData1 = "Santiago Donikian, 31993745, Argentina";
	int inputData2 = 85689;

	//Tamaño cadena, necesario para recuperar informacion
	int lenght = strlen(inputData1.c_str());

	//Guardando en buffer
	//Bloque 1
	memcpy (&buffer[0],inputData1.c_str(),BLOCK_SIZE);
	//Bloque 2
	memcpy (&buffer[BLOCK_SIZE], &inputData2, sizeof(int));

	//Escribiendo en disco
	bFile->create("files/binaryTest");
	//Bloque 1
	bFile->write(&buffer[0],BLOCK_SIZE);
	//Bloque 2
	bFile->write(&buffer[BLOCK_SIZE],BLOCK_SIZE);
	bFile->close();

	//Vaciando Buffer
	memset(buffer,0,BUFFER_SIZE);

	//Datos a recuperar
	string outputData1;
	int outputData2;

	//Recuperando datos
	try{
		bFile->open("files/binaryTest");
		//Bloque 1
		bFile->read(&buffer[0],BLOCK_SIZE);
		//Bloque 2
		bFile->read(&buffer[BLOCK_SIZE],BLOCK_SIZE);
		bFile->close();

		//Cargando del buffer
		char aux[100];
		memcpy(aux,&buffer[0],lenght);
		outputData1 = aux;
		cout << outputData1 << endl;
		memcpy(&outputData2,&buffer[BLOCK_SIZE],sizeof(int));
		cout << outputData2 << endl;

	}catch (string& e){
		cerr << e << endl;
	}
}

void TestIOFile::runBinaryFileTest2(){

	//TODO reemplazar al char* buffer por un objeto Buffer

	BinaryFile* bFile = new BinaryFile();
	char* buffer = new char[BUFFER_SIZE];
	char** data = new char*[3];


	//Datos a guardar
	string inputData1 = "Santiago Donikian, 31993745, Argentina";
	string inputData2 = "Juanjo Donikian, 31, Argentina";
	string inputData3 = "Fede Donikian, 5, Argentina";
	data[0]=new char[strlen(inputData1.c_str())];
	data[1]=new char[strlen(inputData2.c_str())];
	data[2]=new char[strlen(inputData3.c_str())];

	//Tamaño cadena, necesario para recuperar informacion
	short lenght1 = strlen(inputData1.c_str());
	short lenght2 = strlen(inputData2.c_str());
	short lenght3 = strlen(inputData3.c_str());
	memcpy(data[0],inputData1.c_str(),lenght1);
	memcpy(data[1],inputData2.c_str(),lenght2);
	memcpy(data[2],inputData3.c_str(),lenght3);
	int nextByte=0;
	//Guardando en buffer
	//Bloque 1
	memcpy (&buffer[0],&lenght1,sizeof(short));
	memcpy (&buffer[0+sizeof(short)],data[0],lenght1);
	nextByte+=sizeof(short)+lenght1;
	//Bloque 2
	memcpy (&buffer[nextByte],&lenght2,sizeof(short));
	memcpy (&buffer[nextByte+sizeof(short)], data[1], lenght2);
	nextByte+=sizeof(short)+lenght2;
	//Bloque 3
	memcpy (&buffer[nextByte],&lenght3,sizeof(short));
	memcpy (&buffer[nextByte+sizeof(short)], data[2], lenght3);

	//Escribiendo en disco
	bFile->create("files/binaryTest");
	//Bloque 1
	bFile->write(&buffer[0],BUFFER_SIZE);
	//	//Bloque 2
	//	bFile->write(&buffer[BLOCK_SIZE],BLOCK_SIZE);
	//	//Bloque 2
	//	bFile->write(&buffer[BLOCK_SIZE],BLOCK_SIZE);
	bFile->close();

	//Vaciando Buffer
	for (int i = 0; i < 3; i++) {
		delete data[i];
	}
	memset(buffer,0,BUFFER_SIZE);

	//Datos a recuperar
	string outputData1;
	string outputData2;
	string outputData3;


	//Recuperando datos
	try{
		bFile->open("files/binaryTest");
		//Bloque 1
		bFile->read(&buffer[0],BUFFER_SIZE);
		//		//Bloque 2
		//		bFile->read(&buffer[BLOCK_SIZE],BLOCK_SIZE);
		bFile->close();

		//Cargando del buffer
		nextByte=0;
		int len;
		char aux[100];
		memcpy(&len,&buffer[0],sizeof(short));
		cout << "Len1: " << len << endl;
		data[0]=new char[len];
		memcpy(aux,&buffer[0+sizeof(short)],len);
		memcpy(data[0],aux,strlen(aux));
		//		outputData1 = aux;
		cout << "Dato1: " << data[0] << endl;
		nextByte +=len+sizeof(short);
		memset(aux,0,100);

		memcpy(&len,&buffer[nextByte],sizeof(short));
		cout << "Len2: " << len << endl;
		data[1]=new char[len];
		memcpy(aux,&buffer[nextByte+sizeof(short)],len);
		memcpy(data[1],aux,strlen(aux));
		//		outputData2 = aux;
		cout << "Dato2: " << data[1] << endl;
		nextByte +=len+sizeof(short);
		memset(aux,0,100);

		memcpy(&len,&buffer[nextByte],sizeof(short));
		cout << "Len3: " << len << endl;
		data[2]=new char[len];
		memcpy(aux,&buffer[nextByte+sizeof(short)],len);
		memcpy(data[2],aux,strlen(aux));
		//		outputData3 = aux;
		cout << "Dato3: " << data[2] << endl;

		for (int i = 0; i < 3; i++) {
			delete data[i];
		}
		delete data;


	}catch (string& e){
		cerr << e << endl;
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
