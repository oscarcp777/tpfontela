/*
 * testHashExtensible1.cpp
 *
 *  Created on: 03/04/2010
 *      Author: richy
 */
#include "Table.h"
#include "Hash2.h"
#include <string>

int main(){

	int result;
	string keys[15] = {"bill" , "lee" , "pauline", "alan", "julie", "mike", "elizabeth", "mark", "ashley", "peter","joan","john","charles","mary","emily"};


	string nombre = "files/archivoHashExtensible";
	Table table(4);
	result = table.create(nombre);

	if(result == 0){
		std::cout<<"borre los archivos e intente nuevamente"<<std::endl;
		return 0;
	}

	const int numKeys = 15;
	for(int i=0; i<numKeys; i++){
		std::cout<<keys[i]<<" "<<makeAddress(keys[i].length(),table.getDepth())<<std::endl;
		result = table.insert((char*)(keys[i]).c_str(),100+i);
		if(result == 0)
			std::cout<<" insert for "<<keys[i]<<" failed"<<std::endl;

	}
	table.print();
	table.close();

	return 1;

}

