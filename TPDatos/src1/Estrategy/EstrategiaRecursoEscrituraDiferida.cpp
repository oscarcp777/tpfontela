/*
 * EstrategiaRecursoEscrituraDiferida.cpp
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#include "EstrategiaRecursoEscrituraDiferida.h"

EstrategiaRecursoEscrituraDiferida::EstrategiaRecursoEscrituraDiferida() {
	// TODO Auto-generated constructor stub

}

EstrategiaRecursoEscrituraDiferida::~EstrategiaRecursoEscrituraDiferida() {
	// TODO Auto-generated destructor stub
}
int EstrategiaRecursoEscrituraDiferida::escribirArchivo(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento){
	return 0;
}
std::string EstrategiaRecursoEscrituraDiferida::toString(){
   	return "EstrategiaRecursoEscrituraDiferida";
   }
int EstrategiaRecursoEscrituraDiferida::altaComponente(vector<Almacenamiento*>& almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente){
	return 0;
}
int EstrategiaRecursoEscrituraDiferida::bajaComponente(vector<Almacenamiento*> &almacenamientos,EstrategiaAlmacenamiento* estrategiaAlmacenamiento, Componente* componente, int pos){
	return 0;
}
void EstrategiaRecursoEscrituraDiferida::busquedaSecuencial(EstrategiaAlmacenamiento* estrategiaAlmacenamiento,list<Componente*> &resultadoDeLABusqueda, Componente* componente, vector<Almacenamiento*> almacenamientos,std::string clave){


}
