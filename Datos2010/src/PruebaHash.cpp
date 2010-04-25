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
	hash->open("files/hash2");

	string cadena = "Oscar Caceres BOSTERO";
	//	string cadena2 = "Richard Marco Dubini";
	//	string cadena3 = "santiago raul Donikian";
	//	string cadena4 = "Nelson castro Arekipa";
	//	string cadena5 = " Daniel pablo Sivori";
	//	string cadena6 = "maradona";
	//	string cadena7 = "pedro jose ladron de guevarra ortiz de orue";
	//	string cadena8 = "juan paez";
	//	string cadena9 = "boca rey de copas el mas grande de todos los tiempos y mas alla";
	//	hash->insert(86534,(char*)cadena.c_str());
	//	hash->insert(85440,(char*)cadena2.c_str());
	//	hash->insert(85789,(char*)cadena3.c_str());
	//	hash->insert(82289,(char*)cadena4.c_str());
	//	hash->insert(45739,(char*)cadena5.c_str());
	//	hash->insert(11739,(char*)cadena6.c_str());
	//	hash->insert(56739,(char*)cadena7.c_str());
	//	hash->insert(87346,(char*)cadena8.c_str());
	hash->update(86534,(char*)cadena.c_str());
	//	hash->remove(86534);
	hash->print("files/hash");
	hash->close();

	delete hash;
	cout<<"Borro todo bien "<<endl;
}
void createHashTable2(){
	HashExtensible* hash = new HashExtensible();
	cout<<"CREATE"<<endl;
	hash->create("files/hash4");

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
	//hash->search(915);
	hash->insert(915,(char*)cadena2.c_str());
	hash->insert(629,(char*)cadena3.c_str());
	hash->insert(411,(char*)cadena4.c_str());
	hash->insert(200,(char*)cadena5.c_str());
	cout<<"FIN INSERTS"<<endl;
//	hash->insert(863,(char*)cadena6.c_str());
//	hash->remove(629);
//	hash->insert(408,(char*)cadena7.c_str());
//	hash->insert(34,(char*)cadena8.c_str());
//	hash->insert(510,(char*)cadena9.c_str());
//	hash->remove(863);
//	hash->insert(775,(char*)cadena10.c_str());
//		hash->remove(123);
//		hash->remove(915);
//		hash->remove(411);
//		hash->remove(775);
//	hash->print("files/hash");
	cout<<"CLOSE"<<endl;
		hash->close();

		delete hash;
		cout<<"todo bien "<<endl;
	}
void createHashTable4(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hash3");
	string cadena="r";
	int num;
	for (int var = 0; var < 200; ++var) {
		num = rand() %100 +1;
		cadena.append(StringUtils::convertIntToString(num));
		hash->insert(num,(char*)cadena.c_str());
		cadena="r";
	}
	hash->print("files/hash");
	hash->close();

	delete hash;
	cout<<"todo bien "<<endl;
}
void createHashTable3(){
	HashExtensible* hash = new HashExtensible();
	hash->create("files/hash4");

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
	hash->close();

	delete hash;
	cout<<"Borro todo bien "<<endl;
}
void openHashTable2(){
	HashExtensible* hash = new HashExtensible();
	//hash->open("files/hash2");
	hash->open("files/hash4");
//	cout<<"data encontrada : " <<hash->search(112)<<endl;
//	cout<<"data encontrada : " <<hash->search(400)<<endl;
//	cout<<"data encontrada : " <<hash->search(222)<<endl;
//	cout<<"data encontrada : " <<hash->search(456)<<endl;
//	cout<<"data encontrada : " <<hash->search(290)<<endl;
//	cout<<"data encontrada : " <<hash->search(467)<<endl;
//	cout<<"data encontrada : " <<hash->search(179)<<endl;
//	for(int i= 0; i <500; i++)
//		hash->remove(i);
	hash->search(915);
//	hash->remove(34);
//	hash->remove(510);
//	hash->print("files/hash");
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA "<<endl;
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
void colapsarTabla(){
	HashExtensible* hash = new HashExtensible();
	hash->open("files/hash4");

	/*cout<<"data borrada : " <<hash->remove(2)<<endl;
    cout<<"data borrada : " <<hash->remove(111)<<endl;
    cout<<"data borrada : " <<hash->remove(129)<<endl;
    cout<<"data borrada : " <<hash->remove(75)<<endl;
    cout<<"data borrada : " <<hash->remove(923)<<endl;
    cout<<"data borrada : " <<hash->remove(274)<<endl;
    cout<<"data borrada : " <<hash->remove(423)<<endl;
    cout<<"data borrada : " <<hash->remove(118)<<endl;
    cout<<"data borrada : " <<hash->remove(275)<<endl;
    cout<<"data borrada : " <<hash->remove(10)<<endl;*/

	hash->print("files/hash");
	hash->close();
	delete hash;
	cout<<"FIN PRUEBA colapsar"<<endl;
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
	//createHashTable2();
	//openHashTable2();
	//colapsarTabla();

	return 0;
}
