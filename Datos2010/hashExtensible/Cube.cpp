/*
 * Cube.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Cube.h"
#include "Table.h"




Cube::Cube(Table & table, int maxKeys):TextIndex(maxKeys), table(table) {

	this->cubeAddr = 0;
	this->depth = 0;

}
int Cube::find(const char* key){
	for(int i=0; i <numKeys; i++)
		if(strcmp(keys[i], key)) return i; //key found
		else if(strcmp(keys[i],key)>0) return -1;//not found
	return -1;//not found
}
int Cube::insert(char* key, int recAddr){

	if (numKeys < maxKeys){
		int result = TextIndex::insert(key,recAddr);
		table.storeCube(this);
		return result;

	}
	else{
		//si no tiene espacio se genera mas espacio, se hace un "split"
		split();
		return table.insert(key,recAddr);

	}


}

int Cube::remove(char* key){
	//remover key y devolver su recAddr
	int result = TextIndex::remove(key);
	if(!result) return 0; //key not in Cube
	this->tryCombine(); //attempt to combine with buddy
	table.storeCube(this);
	return 1;
}
Cube* Cube::split(){
	int newStart, newEnd;
	if(depth == table.depth)// no hay espacio para hacer split de este Cube
		table.doubleSize();
	Cube* newCube = new Cube(table, maxKeys);
	table.storeCube(newCube); //PORQUE esta linea???
	newRange(newStart,newEnd);
	table.insertCube(newCube->cubeAddr,newStart,newEnd);
	depth++;
	newCube->depth = depth;
	redistribute(*newCube);
	table.storeCube(this);
	table.storeCube(newCube);
	return newCube;
}

int Cube::findBuddy(){
	//find the table address of the Cube that is paired whit this
	if(table.depth == 0) return -1; //no buddy, empty table
			//unless Cube depth == table depth, there is no sinlge Cube to pait with
	if(depth < table.depth) return -1;
	int sharedAddress = makeAddress((int)keys[0], depth);
	//address of any key
	return sharedAddress ^ 1; //exclusive or with low bit

}

int Cube::tryCombine(){
	int result;
	int buddyIndex = findBuddy();
	if(buddyIndex == -1) return 0; //no combination posible
	//load buddy Cube into memory
	int buddyAddr = table.cubeAddr[buddyIndex];
	Cube* buddyCube = new Cube(table, maxKeys);
	table.loadCube(buddyCube, buddyAddr);
	//if the sum of the sizes of the Cubes is too big, return
	if(numKeys + buddyCube->numKeys > maxKeys) return 0;
	combine(buddyCube, buddyIndex);//collapse the 2 Cubes
	result = table.collapse();
	if(result) tryCombine(); //if collapse, may be able combine
	return 1;
}

int Cube::combine(Cube* buddy, int buddyIndex){
	//colapse this and buddy into a single Cube
	int result;
	//move keys from buddy to this
	for(int i=0; i < buddy->numKeys; i++){
	//insert the key of the budy into this
		result = insert(buddy->keys[i], buddy->recAddrs[i]);
		if(!result) return 0;
	}
	depth--;
	table.removeCube(buddyIndex,depth);
	return 1;

}
int Cube::newRange(int & newStart, int & newEnd){
	//make a range for the new split Cube
	int sharedAddr = makeAddress((int)keys[0],depth);
	int bitsToFill = table.depth - (depth+1);
	newStart = (sharedAddr << 1) | 1;
	newEnd = newStart;
	for(int j=0; j<bitsToFill; j++){
		newStart = newStart << 1;
		newEnd = (newEnd << 1) | 1;

	}
	return 1;
}

int Cube::redistribute(Cube & newCube){
	//check each key in this Cube
	for(int i= numKeys -1; i>=0; i--){
		int cubeAddr = table.find(keys[i]);//look up the cube
		if(cubeAddr != this->cubeAddr){//key belongs in the new Cube
			newCube.TextIndex::insert(keys[i], recAddrs[i]);
			TextIndex::remove(keys[i]);//delete key from this Cube

		}
	}
	return 1;
}
void Cube::print(){
	std::cout<<"Cube depth: "<<depth<<std::endl;
	std::cout<<"max keys: "<<maxKeys<<std::endl;
	std::cout<<"num keys: "<<numKeys<<std::endl;
	for(int i = 0; i<numKeys; i++)
		std::cout<<"\tKey["<<i<<"]"<<keys[i]<<" recAddr "<<recAddrs[i]<<std::endl;

}

Cube::~Cube() {
	// TODO Auto-generated destructor stub
}
