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
void createHashTable(){
	HashExtensible* hash = new HashExtensible();
	hash->create("hash2");

	string cadena = "Oscar Caceres Paredes";
	string cadena2 = "Richard Marco Dubini";
	string cadena3 = "santiago raul Donikian";
	string cadena4 = "Nelson castro Arekipa";
	string cadena5 = " Daniel pablo Sivori";
	string cadena6 = "maradona";
	string cadena7 = "pedro jose ladron de guevarra ortiz de orue";
	string cadena8 = "juan paez";
	string cadena9 = "boca rey de copas el mas grande de todos los tiempos y mas alla";
	hash->insert(86534,(char*)cadena.c_str());
	hash->insert(85440,(char*)cadena2.c_str());
	hash->insert(85789,(char*)cadena3.c_str());
	hash->insert(82289,(char*)cadena4.c_str());
	hash->insert(45739,(char*)cadena5.c_str());
	hash->insert(11739,(char*)cadena6.c_str());
	hash->insert(56739,(char*)cadena7.c_str());
	hash->insert(87346,(char*)cadena8.c_str());
	hash->insert(87345,(char*)cadena9.c_str());
	hash->print(NULL);

	hash->close();

	delete hash;
	cout<<"Borro todo bien "<<endl;
}
void createHashTable2(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hash3");

	//+123, +915, +629, +411, +200, +863, -629, +408, +34, +510, -863, +775
	string cadena1 = "reg1";
	string cadena2 = "reg2";
	string cadena3 = "reg3";
	string cadena4=  "reg4";
	string cadena5 = "reg5";
	string cadena6 = "reg6";
	string cadena7 = "reg7";
	string cadena8 = "reg8";
	string cadena9 = "reg9";
	string cadena10 = "re10";
	hash->insert(123,(char*)cadena1.c_str());
	hash->insert(915,(char*)cadena2.c_str());
	hash->insert(629,(char*)cadena3.c_str());
	hash->insert(411,(char*)cadena4.c_str());
	hash->insert(200,(char*)cadena5.c_str());
	hash->insert(863,(char*)cadena6.c_str());
	hash->insert(408,(char*)cadena7.c_str());
	hash->insert(34,(char*)cadena8.c_str());
	hash->insert(510,(char*)cadena9.c_str());
	hash->insert(775,(char*)cadena10.c_str());
	hash->print(NULL);

	hash->close();

	delete hash;
	cout<<"Borro todo bien "<<endl;
}
void openHash(){
	HashExtensible* hash = new HashExtensible();
	//hash->open("files/hash2");
	hash->open("hash2");
	cout<<"data encontrada : " <<hash->search(86534)<<endl;
	cout<<"data encontrada : " <<hash->search(85440)<<endl;
	cout<<"data encontrada : " <<hash->search(85789)<<endl;
	cout<<"data encontrada : " <<hash->search(82289)<<endl;
	cout<<"data encontrada : " <<hash->search(45739)<<endl;
	cout<<"data encontrada : " <<hash->search(11739)<<endl;
	cout<<"data encontrada : " <<hash->search(56739)<<endl;
	cout<<"data encontrada : " <<hash->search(87346)<<endl;
	cout<<"data encontrada : " <<hash->search(87345)<<endl;

	hash->close();
	delete hash;
	cout<<"FIN PRUEBA "<<endl;
}
int main(){
   /****************************************************/
	/***   IMPORTANTE EL TAMANIO DEL BLOQUE NECESITA    */
	/**    12 BYTES DE METADATA + 8 BYTES PARA GUARDAR SU TAMANIO Y CLAVE
	 *     BYTES PARA SU DATA Y BYTES PARA UN 20% LIBRE EJEMPLO
	 *     SI EL BLOQUE ES DE 60 BYTES NECESITA LIBRES 24 SOLO PARA SU
	 *     METADATA Y RESGUARDO MAS EL TAMANIO DE LOS REGISTROS
	 *   |4|4|4|-> METADATA PARA REGISTROS-> |4|4|4|4|4|4|4|4|4|4|4|4|4|4|4|     LIBRE ->|4|4|4|
	 *    ENTONCES SOLO TENGO LUGAR PARA 3 REGISTROS DE 12
	 */
	createHashTable2();
	//openHash();

	return 0;
}
