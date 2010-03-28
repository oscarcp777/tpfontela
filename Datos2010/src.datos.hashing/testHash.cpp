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
	string keys[15] = {"osky" , "nelson" , "santy", "dani", "richy", "caceres", "ramos", "donikian", "sivori", "dubini","maja","paucartambo","datos","hash","kit"};


	string nombre = "archivoHash";
	Directory dir(4);
	result = dir.create((char*)nombre.c_str());

	if(result == 0){
		std::cout<<"borre los archivos e intente nuevamente"<<std::endl;
		return 0;
	}

	const int numKeys = 15;
	for(int i=0; i<numKeys; i++){
		std::cout<<keys[i]<<" "<<(void*)hash((char*)(keys[i]).c_str())<<" "<<(void*)makeAddress((char*)(keys[i]).c_str(),16)<<std::endl;
		result = dir.insert((char*)(keys[i]).c_str(), 100+i);
		if(result == 0)
			std::cout<<" insert for "<<keys[i]<<" failed"<<std::endl;
	}
	dir.print();
	return 1;

}
