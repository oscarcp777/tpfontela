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

void TestIOFile::runTextFileTest(){
	TextFile* text= new TextFile();
	text->open("files/textFile");
	string datos;
	//	text->read(datos);
	text->write("esto es para vos nelson castro 3333");
	text->close();
}
