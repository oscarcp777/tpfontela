#include "IndiceHashExtensible.h"

IndiceHashExtensible::IndiceHashExtensible(PrimaryKey *primaryKey) throw(IndexException) : EstrategiaIndice(primaryKey){
	this->tabla=new vector<unsigned int>();
	this->tabla->push_back(0);
	this->bloquesLibres=new vector<unsigned int>();
	this->Cubos=new vector<Cubo*>();
	this->Cubos->push_back(new Cubo(0,1));
	this->Modificaciones=new vector<HashChange>();
}

IndiceHashExtensible::~IndiceHashExtensible(){
	delete this->tabla;
	delete this->bloquesLibres;
	delete this->Cubos;
	delete this->Modificaciones;
}

void IndiceHashExtensible::Cargar(char* datoSerializadoACargar, unsigned int tamDato) throw(IndexException){
	int tamanioClave;
	char* clave = this->primaryKey->GetKey(datoSerializadoACargar, tamanioClave);
	string strClave (clave);
	vector<unsigned int> vecBuscado = this->Buscar(strClave);
	// Si la clave no es repetida, inserto la clave
	if (vecBuscado.size()==0){
		int toEntero = atoi(clave);
		toEntero = abs(toEntero);
		unsigned long int claveEntero = (unsigned long int) (toEntero);
		unsigned int bloqueAInsertar = this->Hash(claveEntero);
		// Si el dato entra en el bloque, inserto la clave del dato
		if (!this->seDesborda(bloqueAInsertar, tamDato)){
			Cubo* aux = this->Cubos->operator [](bloqueAInsertar);
			aux->InsertarClave(claveEntero);
			vector<unsigned int>* espLibres = Buffer::getInstance()->getListEspaciosLibres();
			espLibres->operator[](bloqueAInsertar)=(espLibres->operator[](bloqueAInsertar))-tamDato;
			HashChange Cambio(claveEntero,bloqueAInsertar,bloqueAInsertar);
			this->Modificaciones->push_back(Cambio);
		}else{ // Si el dato no entra en ese bloque, o sea se desborda el bloque 
			while ((this->seDesborda(bloqueAInsertar, tamDato)) && (this->Modificaciones->size()==0)){
				this->desbordeEnBloque(bloqueAInsertar, claveEntero);
				bloqueAInsertar = this->Hash(claveEntero);
			}
			// Luego de redispersar, inserto la clave
			unsigned int blqInsertar = this->Hash(claveEntero);
			Cubo* aux = this->Cubos->operator [](bloqueAInsertar);
			aux->InsertarClave(claveEntero);
			HashChange Cambio(claveEntero,blqInsertar,blqInsertar);
			this->Modificaciones->push_back(Cambio);	
		}
	}
}

void IndiceHashExtensible::Modificar(char* DatoSerializadoSinModificar, char* DatoSerializadoModificado, 
										unsigned int id){
	
}

void IndiceHashExtensible::Modificar(char* DatoSerializadoSinModificar, char* DatoSerializadoModificado, 
										unsigned int tamDatoSinModificar, unsigned int tamDatoModificado){
	int tamanioClave;
	char* clave = this->primaryKey->GetKey(DatoSerializadoSinModificar, tamanioClave);
	int toEntero = atoi(clave);
	toEntero = abs(toEntero);
	unsigned long int claveEntero = (unsigned long int) (toEntero);
	unsigned int bloqueAInsertar = this->Hash(claveEntero);
	// Si se achica el dato
	if ((tamDatoModificado-tamDatoSinModificar)<=0){
		unsigned int bytesAchicados = tamDatoSinModificar - tamDatoModificado;
		vector<unsigned int>* espLibres = Buffer::getInstance()->getListEspaciosLibres();
		espLibres->operator[](bloqueAInsertar) = espLibres->operator[](bloqueAInsertar) + bytesAchicados;
		HashChange cambio(claveEntero,bloqueAInsertar,bloqueAInsertar);
		this->Modificaciones->push_back(cambio);
	}else{
		unsigned int bytesAgrandados = tamDatoModificado-tamDatoSinModificar;
		vector<unsigned int>* espLibres = Buffer::getInstance()->getListEspaciosLibres();
		// Me fijo si el datoModificado entra en ese bloque
		if (espLibres->operator[](bloqueAInsertar)>=(unsigned int) bytesAgrandados){
			espLibres->operator[](bloqueAInsertar)=(espLibres->operator[](bloqueAInsertar))-bytesAgrandados;
			HashChange Cambio(claveEntero,bloqueAInsertar,bloqueAInsertar);
			this->Modificaciones->push_back(Cambio);
		}else{ // No entra al bloque
			while ((this->seDesborda(bloqueAInsertar, bytesAgrandados)) && (this->Modificaciones->size()==0)){
				this->desbordeEnBloque(bloqueAInsertar, claveEntero);
				bloqueAInsertar = this->Hash(claveEntero);
			}
		}
	}
}

vector<unsigned int> IndiceHashExtensible::Buscar(std::string claveABuscar){
	vector<unsigned int> resultado;
	char* clave = new char [claveABuscar.size()+1];
	strcpy (clave, claveABuscar.c_str());
	int toEntero = atoi(clave);
	toEntero = abs(toEntero);
	unsigned long int claveEntero = (unsigned long int) (toEntero);
	unsigned int bloqueClave = this->Hash(claveEntero);
	Cubo* aux = this->Cubos->operator [](bloqueClave);
	vector<unsigned long int>* vecClaves = aux->getClaves();
	for (unsigned int i=0; i<vecClaves->size(); i++){
		if (vecClaves->operator[](i)==claveEntero){
			resultado.push_back(bloqueClave);
		}
	}
	return resultado;
}

void IndiceHashExtensible::Eliminar(char* DatoSerializadoAEliminar){
	int tamanioClave;
	char* clave = this->primaryKey->GetKey(DatoSerializadoAEliminar, tamanioClave);
	string claveABuscar(clave);
	vector<unsigned int> vecBuscado = this->Buscar(claveABuscar);
	// Busco el dato, si encuentro en algun bloque lo elimino
	if (vecBuscado.size()!=0){ // Encontrado
		int toEntero = atoi(clave);
		toEntero = abs(toEntero);
		unsigned long int claveEntero = (unsigned long int) (toEntero);
		unsigned int posTabla = this->posicionTabla(claveEntero);
		unsigned int bloqueDato = this->Hash(claveEntero);
		// Notifico al cambio
		HashChange eliminado(claveEntero,bloqueDato,bloqueDato);
		this->Modificaciones->push_back(eliminado);
		// Me fijo si el bloque quedo vacio
		Cubo* aux = this->Cubos->operator [](bloqueDato);
		aux->EliminarClave(claveEntero);
		if (aux->estaVacio()){
			// Recorro circularmente la tabla con saltos de (td del bloqueVacio/2)
			unsigned int saltos = aux->getTd();
			saltos = saltos / 2;
			unsigned int adelante = posTabla + saltos;
			if (adelante>=(this->tabla->size())){
				adelante = adelante - this->tabla->size();
			}
			int atrasAux = posTabla - saltos;
			if (atrasAux < 0){
				atrasAux = atrasAux + this->tabla->size();
			}
			unsigned int atras = (unsigned int) atrasAux;
			// Veo si las referencias de la tabla son iguales
			unsigned int bloqueAdelante = this->tabla->operator [](adelante);
			unsigned int bloqueAtras = this->tabla->operator [](atras);
			// Si son iguales entonces puedo liberar al bloque vacio
			if (bloqueAdelante == bloqueAtras){
				// Asigno la referencia de la tabla del bloque vacio con el bloqueAdelante
				this->tabla->operator [](posTabla) = this->tabla->operator [](bloqueAdelante);
				// Agrego el numero del bloque vacio al vector de bloques libres
				this->bloquesLibres->push_back(bloqueDato);
				// Veo si se puede compactar la tabla
				this->compactarTabla();
			}
		}
	}
}

void IndiceHashExtensible::desbordeEnBloque(unsigned int bloqueAInsertar, unsigned long int claveEntero){
	Cubo* aux = this->Cubos->operator [](bloqueAInsertar);
	unsigned int posTabla = this->posicionTabla(claveEntero);
	unsigned int tamTabla = this->tabla->size();
	if (aux->getTd()==tamTabla){ // Si el td del cubo es == al tamanio de la tabla
		// Duplico la tabla
		for (unsigned int i=0; i<tamTabla; i++){
			this->tabla->push_back(this->tabla->operator [](i));
		}
		// Veo si hay algunos bloques libres
		if (this->bloquesLibres->size()==0){
			// Si no hay bloques libres
			unsigned int numCubo = this->Cubos->size();
			this->tabla->operator [](posTabla) = numCubo;
			// Multiplico el td del bloqueAInsertar por 2
			aux->setTd(aux->getTd()*2);
			// Creo un nuevo bloque
			Cubo* nuevoBloque = new Cubo(numCubo,aux->getTd());
			this->Cubos->push_back(nuevoBloque);
			this->redispersarBloque(bloqueAInsertar);
		}else{
			// Hay bloques libres
			unsigned int bloqueLibre = this->bloquesLibres->operator [](0);
			this->bloquesLibres->erase(this->bloquesLibres->begin());
			this->tabla->operator [](posTabla) = bloqueLibre;
			// Multiplico el td del bloqueAInsertar por 2
			aux->setTd(aux->getTd()*2);
			// Pongo el mismo td al bloque libre
			Cubo* bloqLibre = this->Cubos->operator [](bloqueLibre);
			bloqLibre->setTd(aux->getTd());
			this->redispersarBloque(bloqueAInsertar);
		}
	}else{ // Si el td del cubo < tamanio de la tabla
		// Multiplico el td del cubo desbordado
		aux->setTd(aux->getTd()*2);
		// Recorro la tabla en aux->getTd() pasos hacia adelante y atras
		unsigned int adelante = posTabla + aux->getTd();
		if (adelante >= this->tabla->size()){
			adelante = adelante - this->tabla->size();
		}
		int atrasAux = posTabla - aux->getTd();
		if (atrasAux < 0){
			atrasAux = atrasAux + this->tabla->size();
		}
		unsigned int atras = (unsigned int) atrasAux;
		// Veo si hay algunos bloques libres
		if (this->bloquesLibres->size()==0){
			// No hay bloques libres
			// Creo un nuevo bloque
			unsigned int numCubo = this->Cubos->size();
			Cubo* bloqueNuevo = new Cubo (numCubo,aux->getTd());
			this->Cubos->push_back(bloqueNuevo);
			// Asigno las referencias de la tabla a un bloque nuevo
			this->tabla->operator [](posTabla) = numCubo;
			this->tabla->operator [](adelante) = numCubo;
			this->tabla->operator [](atras) = numCubo;
			this->redispersarBloque(bloqueAInsertar);
		}else{
			// Hay bloques libres
			unsigned int bloqueLibre = this->bloquesLibres->operator [](0);
			this->bloquesLibres->erase(this->bloquesLibres->begin());
			// Modifico el td del bloque libre
			Cubo* bloqLibre = this->Cubos->operator [](bloqueLibre);
			bloqLibre->setTd(aux->getTd());
			// Asigno las referencias de la tabla a un bloque libre
			this->tabla->operator [](posTabla) = bloqueLibre;
			this->tabla->operator [](adelante) = bloqueLibre;
			this->tabla->operator [](atras) = bloqueLibre;
			this->redispersarBloque(bloqueAInsertar);
		}
	}
}

bool IndiceHashExtensible::seDesborda(unsigned int bloqueAInsertar, unsigned int tamDato){
	bool resultado = false;
	vector<unsigned int>* espLibres = Buffer::getInstance()->getListEspaciosLibres();
	// Me fijo si el dato entra en ese bloque
	if (espLibres->operator[](bloqueAInsertar)<tamDato){
		resultado = true;
	}
	return resultado;
}

void IndiceHashExtensible::compactarTabla(){
	bool estaDuplicada = true;
	unsigned int mitad = (this->tabla->size()/2);
	for (unsigned int i=0; i<mitad; i++){
		if (this->tabla->operator [](i)!=this->tabla->operator [](i+mitad)){
			estaDuplicada = false;
		}
	}
	if (estaDuplicada){
		this->tabla->erase(this->tabla->begin()+mitad, this->tabla->end());
	}
}

void IndiceHashExtensible::redispersarBloque(unsigned int bloque){
	Cubo* cubo = this->Cubos->operator [](bloque);
	vector<unsigned long int>* claves = cubo->getClaves();
	for (unsigned int i=0; i<(cubo->getClaves()->size()); i++){
		//Aca empiezo a redispersar las claves del bloque
		unsigned long int aux = claves->operator[](i);
		unsigned int bloqueNuevo = this->Hash(aux);
		if (bloqueNuevo!=bloque){ // Se redisperso en otro bloque
			HashChange cambio(aux,bloque,bloqueNuevo);
			this->Modificaciones->push_back(cambio);
			cubo->EliminarClave(aux);
			Cubo* cuboDestino = this->Cubos->operator [](bloqueNuevo);
			cuboDestino->InsertarClave(aux);
		}
	}
}

unsigned int IndiceHashExtensible::posicionTabla(unsigned long int clave){
	unsigned int pos;
	pos = clave % (this->tabla->size());
	return pos;
}

unsigned int IndiceHashExtensible::Hash(unsigned long int clave){
	unsigned int pos;
	unsigned int resultado;
	pos = clave % (this->tabla->size());
	resultado = this->tabla->operator [](pos);
	return resultado;
}

vector<HashChange>* IndiceHashExtensible::getModificaciones(){
	return this->Modificaciones;
}
