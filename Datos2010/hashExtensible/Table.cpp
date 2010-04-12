/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"


Table::Table() {
	this->fileCubes = new BinaryFile();
	this->fileCubesFree = new BinaryFile();
	this->fileTable = new BinaryFile();
	this->currentCube = new Cube(1,0);
	this->countsCubes = 1;
	this->sizeTable = 1;
	this->offsetCubes.push_back(0);
	//	this->countsCubes = 4;
	//	this->sizeTable = 4;
	//	this->offsetCubes.push_back(2);
	//	this->offsetCubes.push_back(1);
	//	this->offsetCubes.push_back(4);
	//	this->offsetCubes.push_back(3);
}

Table::~Table() {
	delete this->fileCubes;
	delete this->fileCubesFree;
	delete this->fileTable;
	delete this->currentCube;
}
int Table::createFiles(string fileName){
	this->fileCubes->create(fileName+EXT_CUBE);
	this->fileCubesFree->create(fileName+EXT_FREE_CUBE);
	this->fileTable->create(fileName+EXT_TABLE);
	this->writeFirstCube();
	return 0;
}
int Table::openFiles(string fileName){
	this->fileCubes->open(fileName+EXT_CUBE);
	this->fileCubesFree->open(fileName+EXT_FREE_CUBE);
	this->fileTable->open(fileName+EXT_TABLE);
	this->readTable();
	this->readFreeCubes();
	return 0;
}
int Table::close(){
	this->fileCubes->close();

	this->fileCubesFree->clear();//hace que el archivo se pise completo
	this->writeFreeCubes();
	this->fileCubesFree->close();

	this->fileTable->clear();//hace que el archivo se pise completo (es necesario por si se achica o agranda la table)
	this->writeTable();
	this->fileTable->close();

	this->print(NULL);//TODO borrar el print
	return 1;
}


int Table::duplicateTable(){
	for(unsigned int i= 0 ; i< this->sizeTable; i++ ){
		this->offsetCubes.push_back(this->offsetCubes[i]);
	}
	this->sizeTable = this->sizeTable*2;

	return 1;
}

int Table::insert(Record* record){
	int index = Hash::hashMod(record->getKey(),this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset);
	int add;
	if(result == 1){//si pudo cargar el cubo
		add =this->currentCube->addRecord(record);
		if(add != 1){//si no agrego es porque no hay lugar

			Cube* newCube;
			if(this->currentCube->getSizeOfDispersion() == this->sizeTable){//tamaño sispersion = tamaño tabla
				this->duplicateTable();
				this->currentCube->setSizeOfDispersion(this->sizeTable);
				this->countsCubes++;
				newCube = new Cube(this->sizeTable,this->countsCubes);

				int size = this->offsetFreeCubes.size();
				if(size == 0)//si no tengo cubos libres le asigno el numero siguiente
					this->offsetCubes[index] = this->countsCubes-1;

				else{
					//si tengo cubos libres le asigno el primero libre y lo borro de la lista
					this->offsetCubes[index] = this->offsetFreeCubes.at(0);
					vector<int>::iterator it = this->offsetFreeCubes.begin();
					this->offsetFreeCubes.erase(it);
				}

				cout<<"hola"<<endl;
			}
			else{//tamaño sispersion <> tamaño tabla
				unsigned int dispersionSize = this->currentCube->getSizeOfDispersion();
				this->currentCube->setSizeOfDispersion(dispersionSize*2);
				this->countsCubes++;
				int offsetNewCube;

				if(this->offsetFreeCubes.size() == 0)//si no tengo cubos libres le asigno el numero siguiente
					offsetNewCube = this->countsCubes-1;

				else{//si tengo cubos libres le asigno el primero libre y lo borro de la lista
					offsetNewCube = this->offsetFreeCubes.at(0);
					vector<int>::iterator it = this->offsetFreeCubes.begin();
					this->offsetFreeCubes.erase(it);
				}

				newCube = new Cube(dispersionSize*2,offsetNewCube);

				for(unsigned int i = index; i<this->sizeTable; i+=newCube->getSizeOfDispersion())
					this->offsetCubes[i] = newCube->getOffsetCube();

				for(int j = index; j>=0; j-=newCube->getSizeOfDispersion())
					this->offsetCubes[j] = newCube->getOffsetCube();



			}
			//redistribuir y guardar los cubos en disco
			this->currentCube->reallocate(newCube,this->sizeTable);
			this->currentCube->writeCube(this->fileCubes);
			newCube->writeCube(fileCubes);
			delete newCube;
			return 1;
		}
		else{
			this->currentCube->writeCube(this->fileCubes);
		}

	}
	else{//no pudo cargar el cubo
		return -1;
	}


	return 1;
}

int Table::loadCube(int offset){
	int res = this->currentCube->loadCube(fileCubes,offset);
	return res;
}

Record *Table::search(int key)
{
	int index = Hash::hashMod(key,this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset);
	if(result)
		return this->currentCube->search(key);
	else
		return NULL;
}
int Table::remove(int key){
	int index = Hash::hashMod(key,this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset);
	if(result){
		this->currentCube->remove(key);
		if(this->currentCube->getNumberOfRecords() == 0){//si queda vacio
			int indexUp = index - (this->currentCube->getSizeOfDispersion()/2);
			int indexDown = index + (this->currentCube->getSizeOfDispersion()/2);
			//comparo los indices dedsde el indice donde estaba (td/2) hacia arriba y hacia abajo
			//si NO son iguales no puedo borrar el cubo por lo que queda vacio
			if( this->offsetCubes[indexUp] == this->offsetCubes[indexDown]){
				//agrego el numero de cubo (offset) a la lista de cubos libres porque ya no se lo referencia mas
				this->offsetFreeCubes.push_back(this->currentCube->getOffsetCube());

				//actualizo la tabla
				this->offsetCubes[index] = this->offsetCubes[indexUp];
				this->loadCube(this->offsetCubes[index]);

				for(unsigned int i = index; i<this->sizeTable; i+=this->currentCube->getSizeOfDispersion()){
					this->offsetCubes[i] = this->currentCube->getOffsetCube();
				}
				for(int j = index; j>=0; j-=this->currentCube->getSizeOfDispersion()){
					this->offsetCubes[j] = this->currentCube->getOffsetCube();
				}
				int sizeDisp = this->currentCube->getSizeOfDispersion();
				this->currentCube->setSizeOfDispersion(sizeDisp/2);
				//guardo el cubo con su nuevo numero de dispersion
				this->currentCube->writeCube(this->fileCubes);

				if(isTableDuplicate() == 1){//comparo las dos mitades de la tabla
					//truncandola a la mitad porque son iguales
					collapse();

				}
			}
			return 1;
		}

	}
	else
		return -1;

	this->currentCube->writeCube(this->fileCubes);
	return 1;
}
int Table::isTableDuplicate(){
	int num = this->offsetCubes.size()/2;
	for(int i=0; i<num; i++){
		if(this->offsetCubes.at(i) != this->offsetCubes.at(num+i))
			return 0;
	}
	return 1;
}
void Table::collapse(){
	this->sizeTable = this->sizeTable/2;
	this->offsetCubes.resize(this->sizeTable);

}
void Table::print(fstream *output){
	cout<<"*************TABLA*************"<<endl;
	cout<<"tamaño tabla= "<<this->sizeTable<<" || cant. Cubos="<<this->countsCubes<<endl;
	for(unsigned int i=0; i<this->sizeTable; i++)
		cout<<"["<<i<<"] = "<<this->offsetCubes[i]<<endl;

	cout<<"cant. Cubos libres= "<<this->offsetFreeCubes.size()<<endl;
	for(unsigned int i=0; i<this->offsetFreeCubes.size(); i++)
		cout<<this->offsetFreeCubes[i]<<endl;
	cout<<"*************FIN  TABLA*************"<<endl;
}

int Table::readTable(){
	Buffer* buffer= new Buffer(8);
	buffer->setBufferSize(8);
	this->fileTable->read(buffer->getData(),sizeof(int)*2);
	int size=0,count=0;
	buffer->unPackField(&size,sizeof(size));
	buffer->unPackField(&count,sizeof(count));

	this->countsCubes = count;
	this->sizeTable = size;
	delete buffer;
	buffer = new Buffer(sizeof(int)*this->countsCubes);
	buffer->setBufferSize(sizeof(int)*this->countsCubes);
	this->fileTable->read(buffer->getData(),sizeof(int)*this->countsCubes,sizeof(int)*2);
	for(unsigned int i=0; i<this->sizeTable; i++)
		buffer->unPackField(&this->offsetCubes[i],sizeof(this->offsetCubes[i]));
	delete buffer;
	return 1;
}


int Table::writeTable(){
	Buffer* buffer= new Buffer(sizeof(int)*this->sizeTable+8);
	buffer->setBufferSize(sizeof(int)*this->sizeTable+8);
	int size = this->sizeTable;
	int count = this->countsCubes;
	int num;
	buffer->packField(&size,sizeof(size));
	buffer->packField(&count,sizeof(count));

	for(unsigned int i=0; i<this->sizeTable; i++){
		num =this->offsetCubes.at(i) ;
		buffer->packField(&num,sizeof(num));

	}

	this->fileTable->write(buffer->getData(),buffer->getBufferSize(),0);
	delete buffer;
	return 1;
}


int Table::readFreeCubes(){
	Buffer* buffer= new Buffer(4);
	buffer->setBufferSize(4);
	this->fileCubesFree->read(buffer->getData(),sizeof(int));
	int freeCubes = 0;
	buffer->unPackField(&freeCubes,sizeof(freeCubes));
	delete buffer;
	if(freeCubes > 0){//si el archivo no esta vacio
		buffer = new Buffer(sizeof(int)*freeCubes);
		buffer->setBufferSize(sizeof(int)*freeCubes);
		this->fileCubesFree->read(buffer->getData(),sizeof(int)*freeCubes,sizeof(int));
		for(int i=0; i<freeCubes; i++)
			buffer->unPackField(&this->offsetFreeCubes[i],sizeof(this->offsetFreeCubes[i]));

		delete buffer;
	}
	return 1;
}
int Table::writeFreeCubes(){
	Buffer* buffer= new Buffer(sizeof(int)*(this->offsetFreeCubes.size()+1));
	buffer->setBufferSize(sizeof(int)*(this->offsetFreeCubes.size()+1));
	int size = this->offsetFreeCubes.size();
	int num;
	buffer->packField(&size,sizeof(size));

	for(unsigned int i=0; i<this->offsetFreeCubes.size(); i++){
		num =this->offsetFreeCubes.at(i) ;
		buffer->packField(&num,sizeof(num));

	}

	this->fileCubesFree->write(buffer->getData(),buffer->getBufferSize(),0);
	delete buffer;
	return 1;
}
int Table::writeFirstCube(){
	this->currentCube->writeCube(this->fileCubes);
	return 1;
}
