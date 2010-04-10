/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"


Table::Table() {


}

Table::~Table() {
}
int Table::hash(int key){
  return (key % this->sizeTable);
}
int Table::readTable(fstream *fileTable)
{
	return 1;
}



int Table::duplicateTable()
{


	return 1;
}



int Table::redispersableCubes(INT_UNSIGNED offsetCube)
{
	return 1;
}



Record *Table::search(int key)
{
	return new Record(0,0);
}

void Table::print(fstream *output)
{

}



int Table::writeTable(fstream *fileTable)
{
	return 1;
}





Cube *Table::getNewCube(fstream *fileCubes)
{
	return new Cube(0);
}



Cube *Table::getCurrentCube(INT_UNSIGNED offsetCube,fstream* fileCubo)
{
	return new Cube(0);
}

int Table::deleteCube(INT_UNSIGNED offsetCube)
{
	return 1;
}

