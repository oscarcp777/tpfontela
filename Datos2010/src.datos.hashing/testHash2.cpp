/*
 * testHash2.cpp
 *
 *  Created on: 03/04/2010
 *      Author: richy
 */
#include "Directory.h"
#include "Hash.h"
#include <string>

int main3436(){
	cout<<"se abre y se busca la clave peter"<<endl;
	string nombre = "files/archivoHash";
	string keys[15] = {"bill" , "lee" , "pauline", "alan", "julie", "mike", "elizabeth", "mark", "ashley", "peter","joan","john","charles","mary","emily"};
	Directory dir(4);

	dir.open(nombre);
	cout<<"recAddrs de peter es "<< dir.search((char*)keys[9].c_str())<<endl;
	dir.print();
	dir.close();
/*

	result = dir.remove((char*)keys[3].c_str());
		if(result == 0)
					std::cout<<" remove failed"<<std::endl;
	result = dir.remove((char*)keys[6].c_str());
		if(result == 0)
			std::cout<<" remove failed"<<std::endl;

	cout<<"se remueven las claves alan y elizrbeth"<<endl;
	dir.print();
	cout<<"recAddrs de mary es "<< dir.search((char*)keys[13].c_str())<<endl;

	cout<<"se remueven la clave mary"<<endl;
	result = dir.remove((char*)keys[13].c_str());
		if(result == 0)
					std::cout<<" remove failed"<<std::endl;
		result = dir.remove((char*)keys[5].c_str());
		if(result == 0)
			std::cout<<" remove failed"<<std::endl;
//		result = dir.remove((char*)keys[2].c_str());
//		if(result == 0)
//			std::cout<<" remove failed"<<std::endl;
		dir.print();*/
	return 1;
}
