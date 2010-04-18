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
	this->output=new TextFile();
	this->countsCubes = 1;
	this->sizeTable = 1;
	this->offsetCubes.size();


}

Table::~Table() {
	delete this->fileCubes;
	delete this->fileCubesFree;
	delete this->fileTable;
	delete this->currentCube;
}
bool Table::isCreated(string fileName){
	return this->fileCubes->isCreated(fileName+EXT_CUBE) && this->fileCubesFree->isCreated(fileName+EXT_FREE_CUBE) && this->fileTable->isCreated(fileName+EXT_TABLE);
}
int Table::createFiles(string fileName){
	this->fileCubes->create(fileName+EXT_CUBE);
	this->fileCubesFree->create(fileName+EXT_FREE_CUBE);
	this->fileTable->create(fileName+EXT_TABLE);
	this->offsetCubes.push_back(0);
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


	return 1;
}


int Table::duplicateTable(){

	for(int i= 0 ; i< this->sizeTable; i++ ){
		this->offsetCubes.push_back(this->offsetCubes[i]);
	}
	this->sizeTable = this->sizeTable*2;
	return 1;
}
int Table::diferentDispersionAndSizeTable(int index){
	Cube* newCube;
	//tamaño sispersion <> tamaño tabla
	unsigned int dispersionSize = this->currentCube->getSizeOfDispersion();
	this->currentCube->setSizeOfDispersion(dispersionSize*2);
	//this->countsCubes++;
	int offsetNewCube;

	if(this->offsetFreeCubes.size() == 0)//si no tengo cubos libres le asigno el numero siguiente
		offsetNewCube = this->countsCubes;

	else{//si tengo cubos libres le asigno el primero libre y lo borro de la lista
		offsetNewCube = this->offsetFreeCubes.at(0);
		vector<int>::iterator it = this->offsetFreeCubes.begin();
		this->offsetFreeCubes.erase(it);
	}

	newCube = new Cube(dispersionSize*2,offsetNewCube);

	for(int i = index; i<this->sizeTable; i+=newCube->getSizeOfDispersion())
		this->offsetCubes[i] = newCube->getOffsetCube();

	for(int j = index; j>=0; j-=newCube->getSizeOfDispersion())
		this->offsetCubes[j] = newCube->getOffsetCube();

	this->currentCube->writeCube(fileCubes);
	newCube->writeCube(fileCubes);
	this->countsCubes++;
	delete newCube;
	return 1;
}
int Table::equalsDispersionAndSizeTable(int index){
	Cube* newCube;
	this->duplicateTable();
	this->currentCube->setSizeOfDispersion(this->sizeTable);

	newCube = new Cube(this->sizeTable,this->countsCubes);

	int size = this->offsetFreeCubes.size();
	if(size == 0)//si no tengo cubos libres le asigno el numero siguiente
		this->offsetCubes[index] = this->countsCubes;

	else{
		//si tengo cubos libres le asigno el primero libre y lo borro de la lista
		newCube->setOffsetCube(this->offsetFreeCubes.at(0));
		this->offsetCubes[index] = this->offsetFreeCubes.at(0);
		vector<int>::iterator it = this->offsetFreeCubes.begin();
		this->offsetFreeCubes.erase(it);
	}
	this->countsCubes++;
	this->currentCube->writeCube(fileCubes);
	newCube->writeCube(fileCubes);
	delete newCube;
	return 1;
}

int Table::insert(Record* record){

	int index = Hash::hashMod(record->getKey(),this->sizeTable);
	int offset = this->offsetCubes[index];
	//Si hay lugar en el cubo, hago el alta sin problemas
	if(!this->existOverflow(offset,record)){
		this->currentCube->addRecord(record);
		this->currentCube->writeCube(this->fileCubes);
	}else{
		// duplico la table hasta encontar lugar para poner el nuevo registro
		//y redistribuyo solo los registros del cubo que esta en overflow
		while(this->existOverflow(offset,record)){
			this->overFlowInCube(index,offset);
			index = Hash::hashMod(record->getKey(),this->sizeTable);
			offset = this->offsetCubes[index];
		}
		cout<<"hola"<<endl;
		// cuando ya redistribui todo y ya se que hay lugar inserto el nuevo registro
		index = Hash::hashMod(record->getKey(),this->sizeTable);
		offset = this->offsetCubes[index];
		this->loadCube(offset,this->currentCube);
		this->currentCube->addRecord(record);
		this->currentCube->writeCube(this->fileCubes);


	}
	return 1;
}
bool Table::existOverflow(int offsetCube,Record*  record){
	this->loadCube(offsetCube,this->currentCube);
	return (!this->currentCube->hasSpace(record->getSizeRecord()));
}
int Table::overFlowInCube(int index,int offsetCubeOverFlow ){
	/*	Si no hay lugar
			    1. Tamaño de dispersión = tamaño de tabla*/
	if(this->currentCube->getSizeOfDispersion() == this->sizeTable){
		this->equalsDispersionAndSizeTable(index);
	}
	else{
		// Tamaño de dispersión <> tamaño de tabla
		this->diferentDispersionAndSizeTable(index);
	}
	/*Se vuelven a dispersar todos los elementos del cubo desbordado con el
			nuevo tamaño de dispersión*/
	this->reallocate(offsetCubeOverFlow);
	return 1;
}
int Table::reallocate(int offsetCubeOverFlow){
	//TODO aca habria que igual que en el reallocate del cubo disérsar todos los regostros del
	// del bloque debordado solo esos y nos el que queremos ingresar por que eso lo hacemos depues
	// cuanddo encontremos donde
	Cube* newCube= new Cube(0,0);
	this->loadCube(offsetCubeOverFlow,this->currentCube);
	list<Record*>::iterator iterRecord = this->currentCube->getIteratorRecord();
	Record* record;
	int max=this->currentCube->getNumberOfRecords();
	for (int var = 0; var < max; var++) {
		record = *iterRecord;
		int newOffset = this->offsetCubes[Hash::hashMod(record->getKey(),this->sizeTable)];

		if(offsetCubeOverFlow != newOffset){
			this->loadCube(newOffset,newCube);
			newCube->addRecordList(record);
			this->currentCube->eraseRecordList(iterRecord,record);
			iterRecord--;
			newCube->writeCube(fileCubes);
		}
		iterRecord++;
	}

	this->currentCube->writeCube(this->fileCubes);
	delete newCube;
	return 1;
}
int Table::loadCube(int offset ,Cube* cube){
	int res = cube->loadCube(fileCubes,offset);
	return res;
}

Record *Table::search(int key)
{
	int index = Hash::hashMod(key,this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset,this->currentCube);
	if(result)
		return this->currentCube->search(key);
	else
		return NULL;
}

int Table::calculateIndex(int* indexUp, int* indexDown, int index){
	int numberOfMovements=(this->currentCube->getSizeOfDispersion()/2);
	(*indexUp) = index -numberOfMovements;
	(*indexDown) = index + numberOfMovements;
	cout<<" indexUp"<<(*indexUp)<<endl;
	cout<<" indexDown"<<(*indexDown)<<endl;
	if((*indexUp) < 0)
		(*indexUp) = this->sizeTable + *indexUp;

	if((*indexDown) > this->sizeTable)
		(*indexDown) = (*indexDown) - this->sizeTable;
	cout<<" indexUp"<<(*indexUp)<<endl;
	cout<<" indexDown"<<(*indexDown)<<endl;
	return 1;
}
int Table::remove(int key){
	int index = Hash::hashMod(key,this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset,this->currentCube);
	if(result){
		int goodDelete=this->currentCube->remove(key);
		if(goodDelete==0)
			return 0;
		//TODO ESTA LINEA NO VA PROBAR this->currentCube->writeCube(this->fileCubes);
		if(this->currentCube->getNumberOfRecords() == 0){//si queda vacio
			int indexUp;
			int indexDown;
			this->calculateIndex(&indexUp, &indexDown,index);
			//comparo los indices dedsde el indice donde estaba (td/2) hacia arriba y hacia abajo
			//si NO son iguales no puedo borrar el cubo por lo que queda vacio
			if( this->offsetCubes[indexUp] == this->offsetCubes[indexDown]){
				//agrego el numero de cubo (offset) a la lista de cubos libres porque ya no se lo referencia mas
				this->offsetFreeCubes.push_back(this->currentCube->getOffsetCube());
				this->countsCubes--;
				//actualizo la tabla
				this->offsetCubes[index] = this->offsetCubes[indexUp];
				this->loadCube(this->offsetCubes[index],this->currentCube);

				for(int i = index; i<this->sizeTable; i+=this->currentCube->getSizeOfDispersion()){
					this->offsetCubes[i] = this->currentCube->getOffsetCube();
				}
				for(int j = index; j>=0; j-=this->currentCube->getSizeOfDispersion()){
					this->offsetCubes[j] = this->currentCube->getOffsetCube();
				}
				int sizeDisp = this->currentCube->getSizeOfDispersion();
				this->currentCube->setSizeOfDispersion(sizeDisp/2);

				if(isTableDuplicate() == 1){//comparo las dos mitades de la tabla
					//truncandola a la mitad porque son iguales
					this->collapse();

				}
			}
			//guardo el cubo con su nuevo numero de dispersion
			this->currentCube->writeCube(this->fileCubes);
			return 1;
		}else{
			this->currentCube->writeCube(this->fileCubes);
		}

	}
	else{
		return -1;
	}

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
void Table::printCubes(){
	string buffer;
	cout<<"************* CUBOS *************"<<endl;
	this->output->write("************* CUBOS *************");
	for(unsigned int i=0; i< (this->countsCubes + this->offsetFreeCubes.size()); i++){
		this->loadCube(i,this->currentCube);
		this->currentCube->print(this->output);
	}
	cout<<"*************FIN  CUBOS *************"<<endl;
	this->output->write("*************FIN CUBOS *************");

}
void Table::print(string fileName,bool cubes){

	this->output->open(fileName);
	string buffer;
	this->output->write("*************TABLA*************");
	cout<<"*************TABLA*************"<<endl;
	buffer.append("tamaño tabla= ");
	buffer.append(StringUtils::convertirAString(this->sizeTable));
	buffer.append(" || cant. Cubos=");
	buffer.append(StringUtils::convertirAString(this->countsCubes));
	cout<<buffer<<endl;
	this->output->write(buffer);
	buffer.clear();
	for(int i=0; i<this->sizeTable; i++){
		buffer.append("[");
		buffer.append(StringUtils::convertirAString(i));
		buffer.append("] = ");
		buffer.append(StringUtils::convertirAString(this->offsetCubes[i]));
		cout<<buffer<<endl;
		this->output->write(buffer);
		buffer.clear();
	}

	buffer.append("cant. Cubos libres= :");
	buffer.append(StringUtils::convertirAString(this->offsetFreeCubes.size()));
	cout<<buffer<<endl;
	this->output->write(buffer);
	buffer.clear();
	for(unsigned int i=0; i<this->offsetFreeCubes.size(); i++){
		buffer.append(StringUtils::convertirAString(this->offsetFreeCubes[i]));
		buffer.append(" | ");

	}
	cout<<buffer<<endl;
	this->output->write(buffer);
	cout<<"*************FIN  TABLA*************"<<endl;
	this->output->write("*************FIN  TABLA*************");
	if(true){
		this->printCubes();
	}
	this->output->close();

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
	buffer = new Buffer(sizeof(int)*this->sizeTable);
	buffer->setBufferSize(sizeof(int)*this->sizeTable);

	this->fileTable->read(buffer->getData(),buffer->getBufferSize());

	int num=0;
	for(int i=0; i<this->sizeTable; i++){
		buffer->unPackField(&num,sizeof(num));
		this->offsetCubes.push_back(num);
	}

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

	for(int i=0; i<this->sizeTable; i++){
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
		int num;
		for(int i=0; i<freeCubes; i++){
			buffer->unPackField(&num,sizeof(num));
			this->offsetFreeCubes.push_back(num);

		}

		delete buffer;
		return 1;
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
