/*
 * testHash.cpp
 *
 *  Created on: 28/03/2010
 *      Author: richy
 */
#include "Directory.h"
#include "Hash.h"
#include <string>

int main(){

//	int result;
//	string keys[15] = {"bill" , "lee" , "pauline", "alan", "julie", "mike", "elizabeth", "mark", "ashley", "peter","joan","john","charles","mary","emily"};


	string nombre = "files/archivoHash";
	Directory dir(4);
/*	result = dir.create(nombre);

	if(result == 0){
		std::cout<<"borre los archivos e intente nuevamente"<<std::endl;
		return 0;
	}

	const int numKeys = 0;
	for(int i=0; i<numKeys; i++){
		std::cout<<keys[i]<<" "<<hash((char*)(keys[i]).c_str())<<" "<<makeAddress((char*)(keys[i]).c_str(),dir.getDepth())<<std::endl;
		result = dir.insert((char*)(keys[i]).c_str(),100+i);
		if(result == 0)
			std::cout<<" insert for "<<keys[i]<<" failed"<<std::endl;
		dir.print();
	}
	//dir.close();*/
	dir.open(nombre);
	dir.print();
	dir.close();
	/*result = dir.remove((char*)keys[1].c_str());
	if(result == 0)
				std::cout<<" remove failed"<<std::endl;
	cout<<"se remueve la clave lee"<<endl;
	dir.print();



	cout<<"se cierra, se abre y se busca la clave peter"<<endl;

	dir.open(nombre);
	cout<<"recAddrs de peter es "<< dir.search((char*)keys[9].c_str())<<endl;


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
