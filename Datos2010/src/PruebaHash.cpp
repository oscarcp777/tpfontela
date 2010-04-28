/*
 * PruebaHash.cpp
 *
 *  Created on: 12/04/2010
 *      Author: richy
 */
#include <iostream>
#include <fstream>
#include "../src.datos.storage/Buffer.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../hashExtensible/HashExtensible.h"
using namespace std;

void createAndInsert(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hash2");
	string cadena="r";
	int num;
	for (int var = 0; var < 500; ++var) {
		num = rand()%100+1;
		cadena.append(StringUtils::convertIntToString(num));
		hash->insert(num,(char*)cadena.c_str());
		cadena="reg";
	}
	hash->print("files/hash");
	hash->close();

	delete hash;
	cout<<"todo bien "<<endl;
}
void search(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hash2");
	cout<<"resultado:"<<hash->search(3)<<endl;
	cout<<"resultado:"<<hash->search(99)<<endl;
	cout<<"resultado:"<<hash->search(17)<<endl;
	cout<<"resultado:"<<hash->search(80)<<endl;
	cout<<"resultado:"<<hash->search(37)<<endl;
	cout<<"resultado:"<<hash->search(124125235)<<endl;
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA "<<endl;
}

void update(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hash2");
	string cadena = "richardDubi";
	cout<<"resultado:"<<hash->update(3, (char*)cadena.c_str())<<endl;;
	hash->print("files/hash");
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA "<<endl;
}

void remove(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hash2");

	cout<<"data borrada : " <<hash->remove(775)<<endl;
	cout<<"data borrada : " <<hash->remove(17)<<endl;
	cout<<"data borrada : " <<hash->remove(2)<<endl;
	cout<<"data borrada : " <<hash->remove(66)<<endl;
	cout<<"data borrada : " <<hash->remove(93)<<endl;
	cout<<"data borrada : " <<hash->remove(24)<<endl;
	cout<<"data borrada : " <<hash->remove(42)<<endl;
	cout<<"data borrada : " <<hash->remove(51)<<endl;
	cout<<"data borrada : " <<hash->remove(24)<<endl;
	cout<<"data borrada : " <<hash->remove(88)<<endl;
	cout<<"data borrada : " <<hash->remove(44)<<endl;

   	hash->print("files/hash4");
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA"<<endl;
}

void ejemploCatedra(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hash3");

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
	hash->print("files/hash");
	hash->insert(775,(char*)cadena10.c_str());
	hash->print("files/hash1");
	hash->close();

	delete hash;
	cout<<"Borro todo bien "<<endl;
}
int main457(){
	/****************************************************/
	/***   IMPORTANTE EL TAMANIO DEL BLOQUE NECESITA    */
	/**    12 BYTES DE METADATA + 8 BYTES PARA GUARDAR SU TAMANIO Y CLAVE
	 *     BYTES PARA SU DATA Y BYTES PARA UN 20% LIBRE EJEMPLO
	 *     SI EL BLOQUE ES DE 60 BYTES NECESITA LIBRES 24 SOLO PARA SU
	 *     METADATA Y RESGUARDO MAS EL TAMANIO DE LOS REGISTROS
	 *   |4|4|4|-> METADATA PARA REGISTROS-> |4|4|4|4|4|4|4|4|4|4|4|4|4|4|4|     LIBRE ->|4|4|4|
	 *    ENTONCES SOLO TENGO LUGAR PARA 3 REGISTROS DE 12
	 */
//	createAndInsert();
//	search();
	remove();
//	update();
//	ejemploCatedra();


	return 0;
}
