//============================================================================
// Name        : ArbolBSharp.cpp
// Author      : Daniel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ArbolBSharp.h"

using namespace std;

ArbolBSharp::ArbolBSharp(int cantClaves){
	this->cantClaves=cantClaves;
	cuentas = k = 0;
	esta    = ea = false;
	this->asignarMaxMin();
	nivel   =0;
	vsam    = raiz = P = N = Xr = NULL;
	contT= contTot=bandera = bandera2 = eli =0;

}

void ArbolBSharp::asignarMaxMin(){
	MAX=cantClaves-1;
	MIN=MAX/2;
}

// Metodo refrescar
void ArbolBSharp::refrescar(){
	nivel = Altura ();
	NodoBSharp *aux = raiz;

	while (!this->arbolVacio(aux->getRama(0))){
		NodoBSharp* ptrRama = aux->getRama(0);
		aux=ptrRama;
	}

	vsam = aux;
}

// Metodo de Insertar
void ArbolBSharp::insertar (NodoRegistro* clave){
	ea = false;
	empujar (clave, raiz);
	if(ea){
		NodoBSharp *nuevo = new NodoBSharp(cantClaves);
		nuevo->setCuentas(1);
		nuevo->setNodoRegistro(1, mediana);
		nuevo->setRama(0, raiz);
		nuevo->setRama(1, Xr);
		raiz = nuevo;
	}
	refrescar();
}

// Metodo Empujar
void ArbolBSharp::empujar (NodoRegistro* clave, NodoBSharp *nodo){
	if(nodo == NULL){
		ea= true;
		mediana= clave;
		Xr= NULL;
	}
	else{
		esta = buscarNodo (clave, nodo);
		if(esta)
			std::cout << "\nCodigo Repetido: "<< clave->getClaveRegistro() << std::endl;
		else{
			empujar (clave, nodo->getRama(k));
			buscarNodo(clave, nodo);

			if(ea){
				if(nodo->getCuentas() < MAX){
					//cout << "Voy a meterhoja!" <<endl;
					ea = false;
					P = nodo;
					// Usa las variables globales
					meterHoja();
				}
				else{
					//cout << "Voy a dividir!" << endl;
					ea = true;
					P = nodo;
					// Usa las variables globales.
					dividir();
				}
			}
		}
	}
}

// Metodo Meter Hoja que usa las variables globales: Mediana, P, K, Xr
void ArbolBSharp::meterHoja(){
	for(int i = P->getCuentas(); i >= k + 1; i--){
			P->setNodoRegistro(i + 1,(P->getNodoRegistro(i)));
			P->setRama(i + 1,P->getRama(i));
	}
	P->setNodoRegistro(k + 1, mediana);
	P->setRama(k + 1, Xr);
	P->setCuentas(P->getCuentas()+1);
}

// Metodo Dividir Nodo que usa las variables asignadas por Meter Hoja Mediana, P, K, Xr.
void ArbolBSharp::dividir(){
	NodoBSharp *mde = new NodoBSharp(cantClaves);
	int pos;

	if (k <= MIN)
		pos= MIN;
	else
		pos= MIN+1;

	for(int i= pos+1; i <= MAX; i++){
		mde->setNodoRegistro(i-pos,(P->getNodoRegistro(i)));
		mde->setRama(i-pos, P->getRama(i));
	}

	mde->setCuentas(MAX-pos);
	P->setCuentas(pos);

	if (k <= MIN)
		meterHoja();
	else{
		k = k-pos;
		NodoBSharp *aux = P;
		P = mde;
		meterHoja();
		P = aux;
	}
	mediana = (P->getNodoRegistro(P->getCuentas()));

	if(arbolVacio(P->getRama(0)))
		doblar(mde);

	mde->setRama(0,P->getRama(P->getCuentas()));
	mde->setHoja(P->getHoja());
	P->setHoja(mde);

	P->setCuentas(P->getCuentas()-1);
	Xr= mde;
}

// Metodo que duplica un Nodo
void ArbolBSharp::doblar (NodoBSharp *mde){
	for(int i = mde->getCuentas(); i >= 1; i--){
		mde->setNodoRegistro(i + 1,mde->getNodoRegistro(i));
		mde->setRama(i + 1, mde->getRama(i));
	}
	mde->setNodoRegistro(1, mediana);
	mde->setCuentas(mde->getCuentas()+1);
}

// Metodo Arbol Vacio
bool ArbolBSharp::arbolVacio(NodoBSharp *nodo){
    return ((nodo == NULL) || (nodo->getCuentas() == 0));
}

// Metodo buscar que retorna si el nodo existe o no
bool ArbolBSharp::buscar(NodoRegistro* clave){
	return buscarNodo (clave, raiz);
}

// Metodo buscar que retorna si el nodo existe o no
bool ArbolBSharp::buscar(NodoRegistro* clave, NodoBSharp *nodo){
	if(nodo->getCuentas() == 0)
		esta = false;
	else{
		buscarNodo(clave, nodo);
		if(esta)
			N= nodo;
		else
			esta = buscar(clave, nodo->getRama(k));
	}
	return esta;
}

// Metodo buscar nodo
bool ArbolBSharp::buscarNodo(NodoRegistro* clave, NodoBSharp *nodo){
        if(nodo == NULL)
        	return false;
        else{
			if(clave->getClaveRegistro()<nodo->getNodoRegistro(1)->getClaveRegistro()){
					k = 0;
					return esta = false;
			}
			else{
				k = nodo->getCuentas();
				while((k > 1) && (clave->getClaveRegistro()<nodo->getNodoRegistro(k)->getClaveRegistro()))
					k--;

				esta = (clave->getClaveRegistro()==nodo->getNodoRegistro(k)->getClaveRegistro());
			}
			return esta;
        }
}

// Realiza un Imprimir Recursivo
void ArbolBSharp::print_rec (){
    if (!arbolVacio(raiz)){
        print_rec_aux(raiz);
        cout << endl;
    }
    else
    	cout << "\nEl Arbol B+ esta Vacio!" << endl;
}

// Metodo auxiliar de print_rec
void ArbolBSharp::print_rec_aux (NodoBSharp *nodo){
	if(!arbolVacio(nodo)){
		print_rec_aux (nodo->getRama(0));
		for(int i = 1; i <= nodo->getCuentas(); i++){
			cout << nodo->getNodoRegistro(i)->getClaveRegistro() << " ";
			print_rec_aux (nodo->getRama(i));
		}
	}
}

// Metodo que retorna la Altura del arbol B+
int ArbolBSharp::Altura (){
	int res = 0;
	NodoBSharp *aux = raiz;
	if (arbolVacio(aux)){
		cout << "\nEl Arbol B+ esta Vacio!" << endl;
		return 0;
	}
	else{
		while (!arbolVacio(aux)){
			res++;
			aux = aux->getRama(0);
		}
		return res;
	}
}


// Realiza el recorrido en Anchura
void ArbolBSharp:: Anchura(){
	int largo = Altura();
	int con = 1;
	NodoBSharp *pg = raiz;
	cout<<"Impresion del arbol B+ en anchura:"<<endl;
	Anchura_aux (pg, largo, con);
	cout << endl;
}

// Metodo auxiliar de Anchura
void ArbolBSharp:: Anchura_aux (NodoBSharp *nodo, int largo, int con){
	if (arbolVacio(nodo)){
	}
	else{
		if (largo >= con){
			ImprimeNivel (nodo, con);
			con++;
			Anchura_aux(nodo,largo, con);
		}
	}
}

void ArbolBSharp::ImprimeNivel (NodoBSharp *nodo, int con){
	if(arbolVacio(nodo)){
	}
	else{
		if (con == 1){
			for(int i= 1; i<= nodo->getCuentas(); i++){
				cout<<nodo->getNodoRegistro(i)->getClaveRegistro()<<" ";
			}
		}
		else{
			con--;
			for(int r= 0; r <= nodo->getCuentas(); r++)
				ImprimeNivel(nodo->getRama(r), con);
		}
	}
}

// Metodo Imprimir Arbol B+
void ArbolBSharp ::Imprimir (){
	NodoBSharp *aux= vsam;
	if (arbolVacio(aux))
		cout << "\nEl Arbol B+ esta Vacio!" << endl;
	else{
		cout<<"Impresion del arbol B+:"<<endl;
		while (!arbolVacio(aux)){
			for (int i= 1; i <= aux->getCuentas(); i++)
				cout<<aux->getNodoRegistro(i)->getClaveRegistro()<<" ";
			aux = aux->getHoja();
		}
	}
	cout << endl;
}

/****************************/

bool ArbolBSharp::Buscar(int c){
    int i;

    NodoBSharp *nodo = vsam;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->getCuentas()); i++){
            if (nodo->getNodoRegistro(i)->getClaveRegistro()==c){
                return  true;
            }
        }
        nodo = nodo->getHoja();
    }
    return false;
}

//ve si el el codigo c existe
int ArbolBSharp:: Esta(int c){
    int i;
    NodoBSharp *nodo = vsam;
    while (nodo != NULL){
        i = 0;
        for(; i <= ((nodo->getCuentas()) - 1); i++){
            if (nodo->getNodoRegistro(i)->getClaveRegistro()==c)
            return  true;
        }
        nodo = nodo->getHoja();
    }
    return false;
}

//encuentra y retorna el nodo buscado
NodoRegistro* ArbolBSharp::Encontrar(int c){
    int i;
    NodoBSharp *nodo = vsam;
    NodoRegistro *siesta;
    while (nodo != NULL){
        i = 0;

        for(; i <= (nodo->getCuentas()); i++){
            if (nodo->getNodoRegistro(i)->getClaveRegistro()==c){
                siesta = new NodoRegistro (nodo->getNodoRegistro(i)->getClaveRegistro(),
				nodo->getNodoRegistro(i)->getPosicionRegistro());/////ojo
                return  siesta;
            }
        }
        nodo = nodo->getHoja();
    }
    return NULL;
}

/*******************************************************************************************/
/*******************************************************************************************/

void ArbolBSharp::preOrdenRecursivo(NodoBSharp *raiz){
	preOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativa */
void ArbolBSharp::preOrdenRecursivoAux(NodoBSharp *raiz){

	NodoBSharp *pg = raiz;

	if( raiz != NULL ){

		cout << pg->getNodoRegistro(1)->getClaveRegistro() << " ";

		// llamada recursiva por la primera hoja
		this->preOrdenRecursivoAux(pg->getRama(0));

		if(pg->getRama(0) != NULL){
			// llamada recursiva por la primera hoja
			this->preOrdenRecursivoAux(pg->getRama(1));
		}

		for(int i = 2; i <= pg->getCuentas(); i++){

			cout << pg->getNodoRegistro(i)->getClaveRegistro() << " ";
			this->preOrdenRecursivoAux(pg->getRama(i));
		}
	}

}

//fstream file7("PostOrRecBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBSharp::postOrdenRecursivo(NodoBSharp *raiz){
	postOrdenRecursivoAux(raiz);
}

/* Realiza un recorrido del arbol de forma recursiva */
void ArbolBSharp::postOrdenRecursivoAux(NodoBSharp *raiz){

	NodoBSharp *pg = raiz;

	if( raiz != NULL ){

		// llamada recursiva por la primera hoja
		this->postOrdenRecursivoAux(pg->getRama(0));

		if(pg->getRama(0) != NULL){
			// llamada recursiva por la primera hoja
			this->postOrdenRecursivoAux(pg->getRama(1));
		}

		cout << pg->getNodoRegistro(1)->getClaveRegistro() << " ";

		for(int i = 2; i <= pg->getCuentas(); i++){
			this->postOrdenRecursivoAux(pg->getRama(i));
			cout << pg->getNodoRegistro(i)->getClaveRegistro() << " ";

		}
	}
}
/**************************************************************/

//fstream file8("PreOrIteBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBSharp::preOrdenIterativo(NodoBSharp *raiz){
	preOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void ArbolBSharp::preOrdenIterativoAux(NodoBSharp *raiz){
	NodoBSharp *pg = raiz;

	if( raiz != NULL ){

		cout << pg->getNodoRegistro(1)->getClaveRegistro() << " ";

		// llamada recursiva por la primera hoja
		this->preOrdenIterativoAux(pg->getRama(0));

		if(pg->getRama(0) != NULL){
				// llamada recursiva por la primera hoja
				this->preOrdenIterativoAux(pg->getRama(1));
		}

		for(int i = 2; i <= pg->getCuentas(); i++){

			cout << pg->getNodoRegistro(i)->getClaveRegistro() << " ";
			this->preOrdenIterativoAux(pg->getRama(i));
		}
	}

}

//fstream file9("PostOrIteBmas.txt", ios::out); //archivo salida de recorrido

void ArbolBSharp::postOrdenIterativo(NodoBSharp *raiz){
	postOrdenIterativoAux(raiz);
}

/* Realiza un recorrido del arbol de forma iterativo */
void ArbolBSharp::postOrdenIterativoAux(NodoBSharp *raiz){
	NodoBSharp *pg = raiz;

	if( raiz != NULL ){

		// llamada recursiva por la primera hoja
		this->postOrdenIterativoAux(pg->getRama(0));

		if(pg->getRama(0) != NULL){
			// llamada recursiva por la primera hoja
			this->postOrdenIterativoAux(pg->getRama(1));
		}

		cout << pg->getNodoRegistro(1)->getClaveRegistro() << " ";

		for(int i = 2; i <= pg->getCuentas(); i++){
			this->postOrdenIterativoAux(pg->getRama(i));
			cout << pg->getNodoRegistro(i)->getClaveRegistro() << " ";
		}
	}
}

ArbolBSharp::~ArbolBSharp(){
	/*NodoBSharp *aux = raiz;
	int i=0;

	while (!this->arbolVacio(aux->getRama(0))){
			NodoBSharp* ptrRama = aux->getRama(0);
			aux=ptrRama;
	}*/
}

