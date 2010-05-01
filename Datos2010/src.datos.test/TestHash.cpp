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

TestHash::TestHash() {
	// TODO Auto-generated constructor stub

}

TestHash::~TestHash() {
	// TODO Auto-generated destructor stub
}
void TestHash::runCreateAndInsertTest(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hashTest");
	string cadena="r";
	int num;
	for (int var = 0; var < 50; ++var) {
		num = rand()%100+1;
		cout<<"Inserto el valor :"<<num<<endl;
		cadena.append(StringUtils::convertIntToString(num));
		hash->insert(num,(char*)cadena.c_str());
		cadena="reg";
	}
	hash->print("files/hashPrint");
	hash->close();

	delete hash;
	cout<<"FIN TEST OK "<<endl;
}
void TestHash::runSearchTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hashTest");
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
	hash->open("files/hashTest");
	cout<<"data borrada : " <<hash->remove(22)<<endl;
	cout<<"data borrada : " <<hash->remove(70)<<endl;
	cout<<"data borrada : " <<hash->remove(38)<<endl;
	cout<<"data borrada : " <<hash->remove(24)<<endl;
	cout<<"data borrada : " <<hash->remove(93)<<endl;
	cout<<"data borrada : " <<hash->remove(78)<<endl;
	cout<<"data borrada : " <<hash->remove(63)<<endl;
	cout<<"data borrada : " <<hash->remove(31)<<endl;
	cout<<"data borrada : " <<hash->remove(24)<<endl;
	cout<<"data borrada : " <<hash->remove(88)<<endl;
	cout<<"data borrada : " <<hash->remove(44)<<endl;
   	hash->print("files/hashPrint");
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;

}
void TestHash::runUpdateTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hashTest");
	string cadena = "San Angeles Team";
	cout<<"resultado:"<<hash->update(3, (char*)cadena.c_str())<<endl;;
	hash->print("files/hashPrint");
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;

}
void TestHash::runPrintTest(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hashTest");
	hash->print("files/hashPrint");
	hash->close();
	delete hash;
	cout<<"FIN TEST OK "<<endl;
}
void TestHash::runExampleCatedraTest(){
		HashExtensible* hash = new HashExtensible();
		hash->create("files/hashTest");
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
		hash->print("files/hashPrint");
		hash->close();

		delete hash;
		cout<<"FIN TEST OK"<<endl;

}
