/*
 * Hashing.cpp
 *
 *  Created on: 08/11/2009
 *      Author: santiago
 */

#include <string>
#include "Hashing.h"

Hashing::Hashing() {
}

void Hashing::Crear(string *filePathName) throw (exception) {
	try	{
		//creo los archivos de Tabla y Cubos para el hashing
		//escribo los datos de control
		this->tabla = Tabla(); //ver si hay que inicializar
		string prefijo = "Tabla_";
		string PathNameTabla = prefijo += *filePathName;
		prefijo = "Cubos_";
		string PathNameCubos = prefijo += *filePathName;
		this->fileTabla = new fstream((char*)PathNameTabla.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
		this->fileCubos =  new fstream((char*)PathNameCubos.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
		this->cantCubos = 0;
		this->tamanioTabla = 0;
		this->ultimoCubo = 0;

		this->fileTabla->seekp(0);
		this->fileCubos->seekp(0);
		this->fileTabla->write((char*)(this->tamanioTabla), sizeof(int));
		this->fileCubos->write((char*)(this->cantCubos), sizeof(int));
		this->fileCubos->write((char*)(this->ultimoCubo), sizeof(int));
	} catch(exception e) {
		throw e;
	}
}

void Hashing::Abrir(string* filePathName) throw (exception) {
	try	{
		string prefijo = "Tabla_";
		string PathNameTabla =  prefijo += *filePathName;
		prefijo = "Cubos_";
		string PathNameCubos = prefijo += *filePathName;
		this->fileTabla = new fstream((char*)PathNameTabla.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
		this->fileCubos =  new fstream((char*)PathNameCubos.c_str(), ios::in | ios::out | ios::trunc | ios::binary);
		this->fileTabla->seekp(0);
		this->fileCubos->seekp(0);
		this->fileTabla->read(reinterpret_cast<char*>(this->tamanioTabla), sizeof(this->tamanioTabla));
		this->fileCubos->read(reinterpret_cast<char*>(this->cantCubos), sizeof(this->cantCubos));
		this->fileCubos->read(reinterpret_cast<char*>(this->ultimoCubo), sizeof(this->ultimoCubo));
	} catch (exception e) {
		throw e;
	}
}

Tabla Hashing::GetTabla(){
    return (this->tabla.CargarTabla(this->fileTabla));
}

void Hashing::SaveTabla() throw (exception){
   try{
	   this->tabla.SaveTabla(this->fileTabla);
   }catch(exception e){
	   throw e;
   }
}

void Hashing::Cerrar() throw (exception) {
	try	{
		this->fileTabla->close();
		this->fileCubos->close();
	} catch(exception e) {
		throw e;
	}
}

RegistroClaveHash Hashing::ObtenerRegistro(string *clave) throw (exception){
   try{
       int offsetCubo = tabla.Buscar(*clave);
       int offsetCuboTemp;
       int TamanioDispersionTemp;
       int cantClavesTemp;
       string clave;
       int offset;
       RegistroClaveHash regTemp;
       this->fileCubos->flush();
       this->fileCubos->seekp(offsetCubo+1, ios::beg);
       fileCubos->read(reinterpret_cast<char*>(&(offsetCuboTemp)), sizeof(offsetCuboTemp));
       fileCubos->read(reinterpret_cast<char*>(&(TamanioDispersionTemp)), sizeof(TamanioDispersionTemp));
       fileCubos->read(reinterpret_cast<char*>(&(cantClavesTemp)), sizeof(cantClavesTemp));
       fileCubos->read(reinterpret_cast<char*>(&(clave)), sizeof(clave));
       fileCubos->read(reinterpret_cast<char*>(&(offset)), sizeof(offset));
       regTemp.setClave(clave);
       regTemp.setOffset(offset);
       return regTemp;
   }catch(exception e){
	   throw e;
  }
}

void Hashing::AddClave(RegistroClaveHash* reg) throw (exception){
   try{
	    tabla.AddClave(reg);
   }catch(exception e){
	   throw e;
   }
}

Hashing::~Hashing() {
	// TODO Auto-generated destructor stub
}
