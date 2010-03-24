/*
 * Archivo.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "File.h"



using namespace std;
File::File():Storage(){

}
void File::crear(){
	if(true){
			    //si no hubo éxito en la apertura...
			    //limpia los flags de control de estado del File
				  this->file.clear();

			    //crea el file
				  this->file.open(this->getPath().c_str(),ios::out);
				  this->file.close();
		}else{
				/* limpia los flags de control de estado del file */
			    this->file.clear();
			    /* crea el file */
			    this->file.open(this->getPath().c_str(),ios::out | ios::binary);
			    if (! this->file.is_open())
			    		    	 cout<<"El file no pudo ser creado "<<endl;
			    else
								 this->file.close();


		}
}
void File::abrir(){

	if(true){
		//intenta abrir el File en modo lectura - escritura
		this->file.open(this->getPath().c_str(),ios::out|ios::in);

		    if (!this->file.is_open()){
		      // si no se pudo crear el file arroja una excepción/
		      cout<<"El file no pudo ser abierto "<<endl;
		      throw std::ios_base::failure("El file no pudo ser abierto");
		    }
	}else{
		  /* abre el file en modo lectura - escritura binario*/
		  this->file.open(this->getPath().c_str(),ios::in |ios::out |ios::binary);
		    /* verifica que haya podido crear el file */
		    if (! this->file.is_open()){
		    	 cout<<"El file no pudo ser abierto "<<endl;
		      /* arroja una excepción */
		      throw string("El file no pudo ser abierto");
		    }
	}

}
void File::cerrar(){
	this->file.close();

}



int File::guardar(std::string registro, int pos){
	/* verifica que el file esta abierto */
	int dir = -1;
		if (this->file.is_open()) {

			if(pos >=0){
				this->file.seekp(pos);
			}
			else
				this->irAlFinal();

			//intenta escribir la cadena en el file
			dir = this->file.tellg();
			this->file.flush();
			this->file << registro<<endl;


			if (file.fail())
				// si se produjo un error, arroja una excepción
				throw std::ios_base::failure("No se pudo escribir correctamente la cadena");

		} else {
			/* arroja una excepción porque el file no está abierto */
			throw string("El file no esta abierto");
		}
		return dir;
}

int File::guardar(char* buffer, int pos){

     int dir=-1;
	if (this->file.is_open()) {

		if (pos < 0)
			this->irAlFinal();
		else{
			this->file.seekp(pos);
			//this->file.seekg(pos);
		}
		int dir = this->file.tellg();

		this->file.write(buffer,this->getTamanio());
		return dir;

	}
 return dir;
}
void File::guardar(char* buffer, int pos,int tamanio){

	if (this->file.is_open()) {

		if (pos < 0)
			this->irAlFinal();
		else{
			this->file.seekp(pos);
		//	this->file.seekg(pos);
		}
		this->file.write(buffer,tamanio);


	}

}
bool File::fin() {

  /* para comprobar el fin lee un char del buffer, sin retirarlo y lo
     compara con el fin de file */
  bool esEof = (this->file.peek() == char_traits<char>::eof());

  if (esEof)
    /* si llegó al fin del file limpia los flags */
    this->file.clear();

  return esEof;
}

void File::leer(std::string& datos, int pos){
	char linea[MAX_LINEA];
  /* verifica que el file esté abierto */
  if (this->file.is_open()) {

	  if(pos>=0)
		  /* lee del file una linea */
		  this->file.seekg(pos);
		  this->file.getline((char*)&linea, MAX_LINEA, '\n');
		  datos = linea;
		  /* chequea si se ha producido un error */
	  if (this->file.fail())
		  /* arroja una excepción ante la imposibilidad de leer un reg */
		  throw string("No se pudo leer correctamente el registro");
  }
  else {
    /* arroja una excepción porque el file no está abierto */
    throw string("El file no está abierto");
  }
}


void File::leer(char* buffer, int pos){


	  if (this->file.is_open()) {
		  if(pos>=0)
		  this->file.seekg(pos);
		  this->file.read(buffer,this->getTamanio());

	  }
	  else {
	      /* arroja una excepción porque el file no está abierto */
	      throw string("El file no está abierto");
	    }

}
void File::leer(char* buffer, int pos,int tamanio){


	  if (this->file.is_open()) {
		  if(pos>=0)
		  this->file.seekg(pos);
		  this->file.read(buffer,tamanio);



	  }
	  else {
	      /* arroja una excepción porque el file no está abierto */
	      throw string("El file no está abierto");
	    }

}


File::~File() {

}
std::string File::toString(){
	return "File";
}

std::string File::getClass(){
	return "File";
}


/**
 * Posiciona el cursor al comienzo del File
 */
void File::irAlPrincipio() {
	this->file.tellg();
	this->file.clear();
	this->file.seekg(0);
	this->file.seekp(0);
	this->file.tellg();
}

/**
 * Posiciona el cursor al final del file
 */
void File::irAlFinal() {
	this->file.tellg();
	this->file.clear();
	this->file.seekg(0, ios::end);
	this->file.seekp(0, ios::end);
	this->file.tellg();
}
/*----------------------------------------------------------------------------*/
long int File::posicion(int tamanioRegistro) {

  long int pos = 0;

  /* verifica que el file esté abierto */
  if (this->file.is_open())

    /* calcula el número de registro según la posición del byte actual */
    pos = this->file.tellg() / tamanioRegistro;

  else
    /* arroja una excepción porque el file no está abierto */
    throw string("El file no está abierto");

  return pos;
}
/*----------------------------------------------------------------------------*/
void File::posicionarse(long int posicion,int tamanioRegistro) {

  /* verifica que el file esté abierto */
  if (this->file.is_open()) {

    /* mueve la posición actual según sea el tamano del registro */
	  this->file.seekg(posicion * tamanioRegistro,ios_base::beg);

    /* chequea si se ha producido un error */
    if (this->file.fail())
      /* arroja una excepción ante la imposibilidad de leer un reg */
      throw string("No se pudo posicionar correctamente el registro");
  }
  else
    /* arroja una excepción porque el file no está abierto */
    throw string("El file no está abierto");
}
int File::leerRegistroVariable(string& registro,int posicion){
	int tamanioRegistro=0;
	this->leer((char*)&tamanioRegistro,posicion,sizeof(tamanioRegistro));
	char* buffer = new char[tamanioRegistro];
	memset(buffer,0,tamanioRegistro);
	this->leer(buffer,-1,tamanioRegistro);
	registro=buffer;
	registro= registro.substr(0,tamanioRegistro);
	delete buffer;
	return this->file.tellp();
}


void File::escribirRegistroVariable(string registro){
	int tamanioRegistro;
	tamanioRegistro =registro.length();
	this->guardar((char*)&tamanioRegistro,-1,sizeof(tamanioRegistro));
	this->guardar((char*)registro.c_str(),-1,tamanioRegistro);
}
void File::escribirRegistroVariableConPosicion(string registro,int pos){
	int tamanioRegistro;
	tamanioRegistro =registro.length();
	this->guardar((char*)&tamanioRegistro,pos,sizeof(tamanioRegistro));
	this->guardar((char*)registro.c_str(),pos+sizeof(tamanioRegistro),tamanioRegistro);
}
