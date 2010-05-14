/*
 * TestHash.cpp
 *
 *  Created on: 01/05/2010
 *      Author: richy
 */

#include "TestHash.h"
#include <iostream>
#include <fstream>
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../src.datos.hash/HashExtensible.h"
#include "../src.datos.utils/ParserInput.h"
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
using namespace std;

string fileName = "files/outputFolder/hashTest";
string printFileName = "files/outputFolder/hashPrint";

TestHash::TestHash() {
	// TODO Auto-generated constructor stub

}

TestHash::~TestHash() {
	// TODO Auto-generated destructor stub
}
void TestHash::runInsertFile(){
	HashExtensible* hash = new HashExtensible();
	hash->create(fileName);
	fstream file;
	ParserInput* parser = new ParserInput();
	file.open("files/inputFolder/input.hash.dat",ios::in|ios::out);

	string line;

	while(!file.eof()){
		getline(file,line);
		if(line.length()!=0){
			parser->parser(line);
			if(hash->insert(parser->getKey(),parser->getData().c_str())){
				cout << "Inserto el dato con la clave = " << parser->getKey() << endl;
			}else{
				cout << "No se inserto el dato " << parser->getKey() << endl;
			}
		}
	}
	file.close();
	hash->print(printFileName);
	hash->close();
	delete hash;
	delete parser;
	cout<<"FIN TEST OK "<<endl;
}
void TestHash::runCreateAndInsertTest(){
	HashExtensible* hash = new HashExtensible();
	hash->create(fileName);
	string cadena="r";
	for (int var = 0; var < 500; ++var) {
		cadena.append(StringUtils::convertIntToString(var));
		hash->insert(var,(char*)cadena.c_str());
		cadena="reg";
	}
	hash->print(printFileName);
	hash->close();

	delete hash;
	cout<<"FIN TEST OK "<<endl;
}
void TestHash::runSearchTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open(fileName);
	cout<<"resultado:"<<hash->search(3)<<endl;
	cout<<"resultado:"<<hash->search(99)<<endl;
	cout<<"resultado:"<<hash->search(17)<<endl;
	cout<<"resultado:"<<hash->search(80)<<endl;
	cout<<"resultado:"<<hash->search(37)<<endl;
	cout<<"resultado:"<<hash->search(124125235)<<endl;
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;

}
void TestHash::runRemoveTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open(fileName);
	vector<int> numVector;

	numVector.push_back(300);
	numVector.push_back(780);
	numVector.push_back(620);
	numVector.push_back(900);
	numVector.push_back(484);
	numVector.push_back(244);
	numVector.push_back(100);
	numVector.push_back(2452);
	numVector.push_back(9012);
	numVector.push_back(4404);
	numVector.push_back(5044);
	numVector.push_back(68);
	numVector.push_back(3948);
	numVector.push_back(2356);
	numVector.push_back(4908);
	numVector.push_back(6532);
	numVector.push_back(9876);
	numVector.push_back(4132);
	numVector.push_back(127);
	numVector.push_back(639);
	numVector.push_back(4567);
	numVector.push_back(111);
	numVector.push_back(9863);
	numVector.push_back(15);
	numVector.push_back(2111);
	numVector.push_back(7);
	numVector.push_back(1231);
	numVector.push_back(1239);

	int num;
	for(unsigned int i = 0; i < numVector.size() ; i++){
		num = numVector.at(i);
		if(hash->remove(num))
			cout<<"clave "<<num<<" borrada correctamente"<<endl;
		else
			cout<<"no se encontro la clave "<<num<<endl;
	}
	hash->print(printFileName+"1");
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;

}
void TestHash::runUpdateTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open(fileName);
	string cadena = "San Angeles Team";
	cout<<"resultado:"<<hash->update(3, (char*)cadena.c_str())<<endl;;
	hash->print(printFileName);
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;

}
void TestHash::runPrintTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open(fileName);
	hash->print(printFileName);
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;
}
void TestHash::runExampleCatedraTest(){
	HashExtensible* hash = new HashExtensible();
	hash->create(fileName);
	//ejemplo del archivo Dispersion Extensible Modular.txt
	//+123, +915, +629, +411, +200, +863, -629, +408, +34, +510, -863, +775
	string cadena1 = "r123";
	string cadena2 = "r915";
	string cadena3 = "r629";
	string cadena4=  "r411";
	string cadena5 = "r200";
	string cadena6 = "r863";
	string cadena7 = "r408";
	string cadena8 = "re34";
	string cadena9 = "r510";
	string cadena10 = "r775";
	hash->insert(123,(char*)cadena1.c_str());
	hash->insert(915,(char*)cadena2.c_str());
	hash->insert(629,(char*)cadena3.c_str());
	hash->insert(411,(char*)cadena4.c_str());
	hash->insert(200,(char*)cadena5.c_str());
	hash->insert(863,(char*)cadena6.c_str());
	hash->remove(629);
	hash->insert(408,(char*)cadena7.c_str());
	hash->insert(34,(char*)cadena8.c_str());
	hash->insert(510,(char*)cadena9.c_str());
	hash->remove(863);
	hash->insert(775,(char*)cadena10.c_str());
	hash->print(printFileName);
	hash->close();

	delete hash;
	cout<<"FIN TEST OK"<<endl;

}
