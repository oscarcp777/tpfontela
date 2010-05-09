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
using namespace std;

string fileName = "files/hashTest";
string printFileName = "files/hashPrint";

TestHash::TestHash() {
	// TODO Auto-generated constructor stub

}

TestHash::~TestHash() {
	// TODO Auto-generated destructor stub
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
	numVector.push_back(34);
	numVector.push_back(510);
//	numVector.push_back(408);
//	numVector.push_back(775);
//	numVector.push_back(78);
//	numVector.push_back(63);
//	numVector.push_back(31);
//	numVector.push_back(24);
//	numVector.push_back(88);
//	numVector.push_back(44);
//	numVector.push_back(19);

	int num;
	for(unsigned int i = 0; i < numVector.size() ; i++){
		num = numVector.at(i);
		if(hash->remove(num))
			cout<<"clave "<<num<<" borrada correctamente"<<endl;
		else
			cout<<"no se encontro la clave "<<num<<endl;
	}
   	hash->print(printFileName);
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
