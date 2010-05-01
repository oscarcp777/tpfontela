/*
 * Table.cpp
 *
 *  Created on: 24/03/2010
 *      Author: Richard
 */

#include "Table.h"


Table::Table() {
	this->fileCubes = new BinaryFile();
	//this->fileCubesFree = new BinaryFile();
	offsetFreeCubes = new FreeBlockController(SIZE_CUBE);
	this->fileTable = new BinaryFile();
	this->currentCube = new Cube(1,-1);
	this->buffer= new Buffer(SIZE_CUBE);
	//this->SecondarycurrentCube = new Cube(1,-1); NO VA, SE HACE INSTANCIA CUANDO SE USA
	this->output=new TextFile();
	this->countsCubes = 1;
	this->sizeTable = 1;
	this->offsetCubes.size();
	this->countElementFirstCube = (SIZE_CUBE - sizeof(int)*4) / sizeof(int);
	this->countElementsCubes = (SIZE_CUBE - sizeof(int)) / sizeof(int);
    this->modifiedCubeTable=false;
    this->modifiedTable=false;

}
void Table::clearIndexOffsetModified(){
	vector<RangeController*>::iterator it;
		for (it=this->indexOffsetModified.begin(); it!=this->indexOffsetModified.end(); ++it){
			RangeController* range =*it;
            delete range;
		}
  this->indexOffsetModified.clear();
}
int Table::updateTable()
{

	vector<RangeController*>::iterator it;
	this->buffer->clear();
	buffer->setBufferSize(SIZE_CUBE);
	for (it=this->indexOffsetModified.begin(); it!=this->indexOffsetModified.end(); ++it){
		RangeController* range =*it;
		if(range->isModificate()){
			int indexOffset= range->getMinumun();
			int* pIndexOffset=&indexOffset;
          this->packCubeTable(buffer,range->getMaximun(),pIndexOffset);
          this->fileTable->write(buffer->getData(),buffer->getMaxBytes());
		}
		this->buffer->clear();
	}

	this->setModifiedTable(false);
	return 1;
}
int Table::writeHeaderTable(Buffer* buffer){
	buffer->packField(&this->sizeTable,sizeof(this->sizeTable));
	buffer->packField(&this->countsCubes,sizeof(this->countsCubes));
	this->countCubeFileTable = 1;
	int elements = this->sizeTable;
	if(elements > this->countElementFirstCube){
		elements-= this->countElementFirstCube;
		this->countCubeFileTable+= (elements/this->countElementsCubes);
		if(elements % this->countElementsCubes)
			this->countCubeFileTable++;
	}

	buffer->packField(&this->countCubeFileTable,sizeof(this->countCubeFileTable));
	return 1;
}
int Table::reWriteTable(){
	this->buffer->clear();
	this->clearIndexOffsetModified();
	buffer->setBufferSize(SIZE_CUBE);
	int indexOffset = 0;
	int* pIndexOffset= &indexOffset;
	int count=0;
	int position=0;
	this->writeHeaderTable(buffer);
	for(int j=0; j<this->countCubeFileTable; j++){

		if(this->countCubeFileTable > 1){
			if(j==0){
				buffer->packField(&this->countElementFirstCube,sizeof(this->countElementFirstCube));
				this->packCubeTable(buffer,this->countElementFirstCube,pIndexOffset);
				count=this->sizeTable-this->countElementFirstCube;
				this->fileTable->write(buffer->getData(),buffer->getMaxBytes(),0);
				RangeController* range=new RangeController(position,this->countElementFirstCube);
				this->indexOffsetModified.push_back(range);
				position+=this->countElementFirstCube+1;
			}
			else{
				if(count > this->countElementsCubes){
					buffer->clear();
					buffer->packField(&this->countElementsCubes,sizeof(this->countElementsCubes));
					this->packCubeTable(buffer,this->countElementsCubes,pIndexOffset);
					count-= this->countElementsCubes;
					this->fileTable->write(buffer->getData(),buffer->getMaxBytes());
					RangeController* range=new RangeController(position,this->countElementFirstCube);
					this->indexOffsetModified.push_back(range);
					position+=this->countElementsCubes+1;
				}else{
					buffer->clear();
					buffer->packField(&count,sizeof(count));
					this->packCubeTable(buffer,count,pIndexOffset);
					this->fileTable->write(buffer->getData(),buffer->getMaxBytes());
					RangeController* range=new RangeController(position,this->sizeTable);
					this->indexOffsetModified.push_back(range);
				}


			}
		}else{
			buffer->packField(&this->sizeTable,sizeof(this->sizeTable));
			this->packCubeTable(buffer,this->sizeTable,pIndexOffset);
			count=this->sizeTable-this->countElementFirstCube;
			this->fileTable->write(buffer->getData(),buffer->getMaxBytes(),0);
			RangeController* range=new RangeController(position,this->sizeTable);
			this->indexOffsetModified.push_back(range);

		}


	}
	this->setModifiedCubeTable(false);
	return 1;
}

void Table::setValueVectorOffsetCube(int position,int value){
	this->offsetCubes[position] = value;
	this->setModifiedTable(true);
	vector<RangeController*>::iterator it;
	for (it=this->indexOffsetModified.begin(); it!=this->indexOffsetModified.end(); ++it){
		RangeController* range =*it;
		if(range->isRangeValidator(position)){
           range->setModificate(true);
		}
	}
}

Table::~Table() {
	clearIndexOffsetModified();
	delete this->fileCubes;
	//delete this->fileCubesFree;
	delete offsetFreeCubes;
	delete this->fileTable;
	delete this->currentCube;
	delete this->output;
	delete this->buffer;
}
bool Table::isCreated(string fileName){
	return this->fileCubes->isCreated(fileName+EXT_CUBE) && this->offsetFreeCubes->isCreated(fileName)/*this->fileCubesFree->isCreated(fileName+EXT_FREE_CUBE)*/ && this->fileTable->isCreated(fileName+EXT_TABLE);
}
int Table::createFiles(string fileName){
	this->fileCubes->create(fileName+EXT_CUBE);
	this->offsetFreeCubes->create(fileName,ios::trunc|ios::in |ios::out |ios::binary);
	//this->fileCubesFree->create(fileName+EXT_FREE_CUBE);
	this->fileTable->create(fileName+EXT_TABLE);
	this->offsetCubes.push_back(0);
	this->writeFirstCube();
	this->reWriteTable();
	return 0;
}
int Table::openFiles(string fileName){
	this->fileCubes->open(fileName+EXT_CUBE);
	//this->fileCubesFree->open(fileName+EXT_FREE_CUBE);
	this->offsetFreeCubes->open(fileName,ios::in |ios::out |ios::binary);
	this->fileTable->open(fileName+EXT_TABLE);
	this->readTable();
	this->readFreeCubes();
	return 0;
}
int Table::close(){
	this->fileCubes->close();

	//this->fileCubesFree->clear();//hace que el archivo se pise completo
	//this->writeFreeCubes();
	this->offsetFreeCubes->close();

	this->fileTable->clear();//hace que el archivo se pise completo (es necesario por si se achica o agranda la table)
	this->reWriteTable();
	this->fileTable->close();


	return 1;
}


int Table::duplicateTable(){

	for(int i= 0 ; i< this->sizeTable; i++ ){
		this->offsetCubes.push_back(this->offsetCubes[i]);
	}
	this->sizeTable = this->sizeTable*2;
	this->setModifiedCubeTable(true);
	return 1;
}
int Table::diferentDispersionAndSizeTable(int index){
	//tamaño sispersion <> tamaño tabla
	unsigned int dispersionSize = this->currentCube->getSizeOfDispersion();
	this->currentCube->setSizeOfDispersion(dispersionSize*2);
	//this->countsCubes++;
	int offsetNewCube;

	if(this->offsetFreeCubes->getSize() == 0)//si no tengo cubos libres le asigno el numero siguiente
		offsetNewCube = this->countsCubes;

	else{//si tengo cubos libres le asigno el primero libre y lo borro de la lista
		offsetNewCube = this->offsetFreeCubes->get();
//		offsetNewCube = this->offsetFreeCubes.at(0);
//		vector<int>::iterator it = this->offsetFreeCubes.begin();
//		this->offsetFreeCubes.erase(it);
	}

	this->SecondarycurrentCube = new Cube(dispersionSize*2,offsetNewCube);

	for(int i = index; i<this->sizeTable; i+=this->SecondarycurrentCube->getSizeOfDispersion())
		this->setValueVectorOffsetCube(i,this->SecondarycurrentCube->getOffsetCube());

	for(int j = index; j>=0; j-=this->SecondarycurrentCube->getSizeOfDispersion())
		this->setValueVectorOffsetCube(j,this->SecondarycurrentCube->getOffsetCube());

	this->currentCube->writeCube(fileCubes);
	this->SecondarycurrentCube->writeCube(fileCubes);
	this->countsCubes++;
	delete this->SecondarycurrentCube;
	return 1;
}
int Table::equalsDispersionAndSizeTable(int index){
	this->duplicateTable();
	this->currentCube->setSizeOfDispersion(this->sizeTable);

	this->SecondarycurrentCube = new Cube(this->sizeTable,this->countsCubes);


	int size = this->offsetFreeCubes->getSize();
	if(size == 0)//si no tengo cubos libres le asigno el numero siguiente
		this->offsetCubes[index] = this->countsCubes;

	else{
		//si tengo cubos libres le asigno el primero libre y lo borro de la lista
		//this->SecondarycurrentCube->setOffsetCube(this->offsetFreeCubes.at(0));
		this->SecondarycurrentCube->setOffsetCube(this->offsetFreeCubes->get());
		this->offsetCubes[index] = this->SecondarycurrentCube->getOffsetCube();
//		this->offsetCubes[index] = this->offsetFreeCubes.at(0);
//		vector<int>::iterator it = this->offsetFreeCubes.begin();
//		this->offsetFreeCubes.erase(it);
	}
	this->countsCubes++;
	this->currentCube->writeCube(fileCubes);
	this->SecondarycurrentCube->writeCube(fileCubes);
	//newCube->writeCube(fileCubes);
	delete this->SecondarycurrentCube;
	return 1;
}

int Table::insert(Record* record){

	int index = Hash::hashMod(record->getKey(),this->sizeTable);
	int offset = this->offsetCubes[index];
	//Si hay lugar en el cubo, hago el alta sin problemas
	if(!this->existOverflow(offset,record)){

		if(this->currentCube->addRecord(record))
			if(this->currentCube->writeCube(this->fileCubes))
				return 1;


	}else{
		// duplico la table hasta encontar lugar para poner el nuevo registro
		//y redistribuyo solo los registros del cubo que esta en overflow
		do {
			this->overFlowInCube(index,offset);
			index = Hash::hashMod(record->getKey(),this->sizeTable);
			offset = this->offsetCubes[index];

		} while (this->existOverflow(offset,record));


		// cuando ya redistribui todo y ya se que hay lugar inserto el nuevo registro
		index = Hash::hashMod(record->getKey(),this->sizeTable);
		offset = this->offsetCubes[index];
		this->loadCube(offset,this->currentCube);
		if(this->currentCube->addRecord(record))
			if(this->currentCube->writeCube(this->fileCubes)){
				this->writeTable();
				return 1;
			}




	}
	return 0;
}
int Table::update(Record* record){
	int index = Hash::hashMod(record->getKey(),this->sizeTable);
	int offset = this->offsetCubes[index];
	this->loadCube(offset,this->currentCube);
	//Carga el cubo y si encuentra el registro lo borra y lo agrega nuevamente
	if(this->currentCube->search(record->getKey()) != NULL){
		if(this->currentCube->remove(record->getKey()))
			this->insert(record); //agrega el registro
		 return TRUE;
	}
	return FALSE;


//	//Si existe lo actualizo
//	if(this->currentCube->update(record)){
//		this->currentCube->writeCube(this->fileCubes);
//		return TRUE;
//	}
//
//	return FALSE;
}
bool Table::existOverflow(int offsetCube,Record*  record){
	if(this->currentCube->getOffsetCube() != offsetCube)
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
	//Cube* newCube= new Cube(1,-1);
	this->SecondarycurrentCube = new Cube(1,-1);
	this->loadCube(offsetCubeOverFlow,this->currentCube);

	list<Record*>::iterator iterRecord = this->currentCube->getIteratorRecord();
	Record* record;
	int max=this->currentCube->getNumberOfRecords();
	for (int var = 0; var < max; var++) {
		record = *iterRecord;
		int newOffset = this->offsetCubes[Hash::hashMod(record->getKey(),this->sizeTable)];

		if(offsetCubeOverFlow != newOffset){
			this->loadCube(newOffset,this->SecondarycurrentCube);
			//newCube->addRecordList(record);
			this->SecondarycurrentCube->addRecordList(record);
			this->currentCube->eraseRecordList(iterRecord,record);
			iterRecord--;
			this->SecondarycurrentCube->writeCube(fileCubes);
			//newCube->writeCube(fileCubes);
		}
		iterRecord++;
	}
	this->currentCube->writeCube(this->fileCubes);
	delete this->SecondarycurrentCube;
	//delete newCube;
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

	if((*indexUp) < 0)
		(*indexUp) = this->sizeTable + *indexUp;

	if((*indexDown) > this->sizeTable)
		(*indexDown) = (*indexDown) - this->sizeTable;

	return 1;
}
int Table::remove(int key){
	int index = Hash::hashMod(key,this->sizeTable);
	int offset = this->offsetCubes[index];
	int result = this->loadCube(offset,this->currentCube);
	if(result){
		int noDelete=this->currentCube->remove(key);
		if(noDelete==0)
			return 0;//SI NO EXISTE LA CLAVE SALE

		if(this->currentCube->getNumberOfRecords() == 0 && this->countsCubes>1){//si queda vacio
			int indexUp;
			int indexDown;
			this->calculateIndex(&indexUp, &indexDown,index);
			//comparo los indices dedsde el indice donde estaba (td/2) hacia arriba y hacia abajo
			//si NO son iguales no puedo borrar el cubo por lo que queda vacio
			if( this->offsetCubes[indexUp] == this->offsetCubes[indexDown] ){
				//agrego el numero de cubo (offset) a la lista de cubos libres porque ya no se lo referencia mas

				//this->offsetFreeCubes.push_back(this->currentCube->getOffsetCube());
				this->offsetFreeCubes->add(this->currentCube->getOffsetCube());

				this->countsCubes--;
				//actualizo la tabla
				this->setValueVectorOffsetCube(index,this->offsetCubes[indexUp]);
				this->loadCube(this->offsetCubes[index],this->currentCube);

				for(int i = index; i<this->sizeTable; i+=this->currentCube->getSizeOfDispersion()){
					this->setValueVectorOffsetCube(i,this->currentCube->getOffsetCube());
				}
				for(int j = index; j>=0; j-=this->currentCube->getSizeOfDispersion()){
					this->setValueVectorOffsetCube(j,this->currentCube->getOffsetCube());
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
			this->writeTable();
			return 1;
		}else{
			this->currentCube->writeCube(this->fileCubes);
			return 1;
		}

	}
	else{
		return 0;// NO PUDO HACER LOAD DEL CUBO
	}

	this->currentCube->writeCube(this->fileCubes);
	this->writeTable();
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
	this->setModifiedCubeTable(true);
}
void Table::printCubes(){
	string buffer;
	cout<<"************* CUBOS *************"<<endl;
	this->output->write("************* CUBOS *************");
	for(int i=0; i< (this->countsCubes + this->offsetFreeCubes->getSize()); i++){
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
	buffer.append(StringUtils::convertirAString(this->offsetFreeCubes->getSize()));
	cout<<buffer<<endl;
	this->output->write(buffer);
	buffer.clear();
//	for(int i=0; i<this->offsetFreeCubes->getSize(); i++){
//		buffer.append(StringUtils::convertirAString(this->offsetFreeCubes.at(i)));
//		buffer.append(" | ");
//
//	}
	this->offsetFreeCubes->print(this->output->getStream());
	this->offsetFreeCubes->print(cout);
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
	this->buffer->clear();
	buffer->setBufferSize(SIZE_CUBE);
	this->fileTable->read(buffer->getData(),SIZE_CUBE);

	int countElementCubeFile = 0;
	buffer->unPackField(&this->sizeTable,sizeof(this->sizeTable));
	buffer->unPackField(&this->countsCubes,sizeof(this->countsCubes));
	buffer->unPackField(&this->countCubeFileTable,sizeof(this->countCubeFileTable));
	buffer->unPackField(&countElementCubeFile,sizeof(countElementCubeFile));

	int num=0;
	for(int j=0; j<this->countCubeFileTable; j++){
		if(this->countCubeFileTable > 1 && j>0){
			buffer->clear();
			this->fileTable->read(buffer->getData(),SIZE_CUBE);
			buffer->unPackField(&countElementCubeFile,sizeof(countElementCubeFile));
		}
		for(int i=0; i<countElementCubeFile ; i++){

			buffer->unPackField(&num,sizeof(num));
			this->offsetCubes.push_back(num);

		}
	}

	return 1;
}


int Table::writeTable(){
	//para escirbir la tabla me fijo que haya sido modificada
	if(this->isModifiedCubeTable()){
		//aca ase modificaron los cubos es decir se duplico o se colapso
		this->reWriteTable();
	}else{
		if(this->isModifiedTable()){
			//aca solo se modifico un valor de la tabla
			this->updateTable();
		}


	}
	return 1;
}
int Table::packCubeTable(Buffer* buffer,int count,int* indexOffset){
	int num=0;
	for(int i=0; i<count; i++){
		num =this->offsetCubes.at(*indexOffset) ;
		//cout<<"Elemento["<<(*indexOffset)<<"]="<<num<<endl;
		buffer->packField(&num,sizeof(num));
		(*indexOffset)++;
	}
	return 0;
}

int Table::readFreeCubes(){
//	Buffer* buffer= new Buffer(4);
//	buffer->setBufferSize(4);
//	this->fileCubesFree->read(buffer->getData(),sizeof(int));
//	int freeCubes = 0;
//	buffer->unPackField(&freeCubes,sizeof(freeCubes));
//	delete buffer;
//
//	if(freeCubes > 0){//si el archivo no esta vacio
//		buffer = new Buffer(sizeof(int)*freeCubes);
//		buffer->setBufferSize(sizeof(int)*freeCubes);
//		this->fileCubesFree->read(buffer->getData(),sizeof(int)*freeCubes,sizeof(int));
//		int num;
//		for(int i=0; i<freeCubes; i++){
//			buffer->unPackField(&num,sizeof(num));
//			this->offsetFreeCubes.push_back(num);
//
//		}
//
//		delete buffer;
//		return 1;
//	}

	return 1;
}
int Table::writeFreeCubes(){
//	Buffer* buffer= new Buffer(sizeof(int)*(this->offsetFreeCubes.size()+1));
//	buffer->setBufferSize(sizeof(int)*(this->offsetFreeCubes.size()+1));
//	int size = this->offsetFreeCubes.size();
//	int num;
//	buffer->packField(&size,sizeof(size));
//
//	for(unsigned int i=0; i<this->offsetFreeCubes.size(); i++){
//		num =this->offsetFreeCubes.at(i) ;
//		buffer->packField(&num,sizeof(num));
//
//	}
//
//	this->fileCubesFree->write(buffer->getData(),buffer->getBufferSize(),0);
//	delete buffer;
	return 1;
}
int Table::writeFirstCube(){
	this->currentCube->writeCube(this->fileCubes);
	return 1;
}
