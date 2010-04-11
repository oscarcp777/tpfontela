/*
 * Bucket.h
 *
 *  Created on: 28/03/2010
 *      Author: Oscar
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <list>
#include <fstream>
#include "Record.h"
#include "../src.datos.utils/Define.h"
#include "../src.datos.storage/BinaryFile.h"
#include "../src.datos.storage/TextFile.h"
#include "../src.datos.storage/Buffer.h"
#include "Hash.h"
using namespace std;
typedef struct metadataCube {
	INT_UNSIGNED sizeFree;
	INT_UNSIGNED sizeOfDispersion;
	INT_UNSIGNED numberOfRecords;

}METADATA_CUBE;
class Cube {
private:
	INT_UNSIGNED sizeOfDispersion;
	INT_UNSIGNED numberOfRecords;
	INT_UNSIGNED offsetCube;
	INT_UNSIGNED sizeFree;
	list<Record*> records;
	int sizeCube;
	Buffer* buffer;
	METADATA_CUBE metadata;//estructura donde se escribe y se lee la metada en un solo read
	int loadMetadata();
	int writeMetadata();
	int getDiskPosition();
public:
	Cube( INT_UNSIGNED sizeOfDispersion,INT_UNSIGNED offset);
	virtual ~Cube();
	/**
	 *verifica si hay el espacio minimo necesario para escribir en el bloque
	 *verificando que se preserve un espacio de resguardo para las modificaciones
	 *el tamanio del registro mas el espacio minimo necesario que debe de tener el cubo
	 *tiene que ser menor que el tamanio libre
	 *@autor Oscar
	 *@argument size tamanio del registro que se quiere agregar
	 *@return retorna true o false si hay el espacio minimo necesario o no
	 */
	bool hasSpace(int size);
	int addRecord(Record* record);
	int remove(int key);
	Record* search(int key);
	int writeCube(BinaryFile* fileCube);
	int reallocate(Cube* newCube,int sizetable);
	int loadCube(BinaryFile* fileCube,int offsetCube);
	int print(TextFile* output);
    int clear();










	int getNumberOfRecords() const
	{
		return numberOfRecords;
	}

	int getOffsetCube() const
	{
		return offsetCube;
	}

	list<Record*> getRecords() const
    		{
		return records;
    		}

	int getSizeCube() const
	{
		return sizeCube;
	}

	int getSizeFree() const
	{
		return sizeFree;
	}

	unsigned int getSizeOfDispersion() const
	{
		return sizeOfDispersion;
	}

	void setNumberOfRecords(int numberOfRecords)
	{
		this->numberOfRecords = numberOfRecords;
	}

	void setOffsetCube(int offsetCube)
	{
		this->offsetCube = offsetCube;
	}

	void setRecords(list<Record*> records)
	{
		this->records = records;
	}

	void setSizeCube(int sizeCube)
	{
		this->sizeCube = sizeCube;
	}

	void setSizeFree(int sizeFree)
	{
		this->sizeFree = sizeFree;
	}

	void setSizeOfDispersion(int sizeOfDispersion)
	{
		this->sizeOfDispersion = sizeOfDispersion;
	}

};

#endif /* CUBE_H_ */
