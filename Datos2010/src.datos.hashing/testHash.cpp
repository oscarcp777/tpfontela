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

	int result;
	string keys[15] = {"bill" , "lee" , "pauline", "alan", "julie", "mike", "elizabeth", "mark", "ashley", "peter","joan","john","charles","mary","emily"};


	string nombre = "files/archivoHash";
	Directory dir(4);
	result = dir.create((char*)nombre.c_str());

	if(result == 0){
		std::cout<<"borre los archivos e intente nuevamente"<<std::endl;
		return 0;
	}

	const int numKeys = 15;
	for(int i=0; i<numKeys; i++){
		std::cout<<keys[i]<<" "/*<<hash((char*)(keys[i]).c_str())<<*/" "<<makeAddress((char*)(keys[i]).c_str(),dir.getDepth())<<std::endl;
		result = dir.insert((char*)(keys[i]).c_str(),100+i);
		if(result == 0)
			std::cout<<" insert for "<<keys[i]<<" failed"<<std::endl;
		dir.print();
	}

	return 1;

}
