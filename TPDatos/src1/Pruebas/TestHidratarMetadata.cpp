/*
 * TestHidratarMetadata.cpp
 *
 *  Created on: 24/10/2009
 *      Author: oscar
 */
#include "../Almacenamiento/Metadata.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
using namespace std;

int main134124(){
	Metadata* metadata= new Metadata();
	metadata->setNombreArchivo("archivoRegistrosMetaData");
	metadata->setRuta("../TPDatos/files/");
	metadata->abrir();
	metadata->hidratarMetadata();
	metadata->cerrar();
	cout<<"posicion libre :" << metadata->getPosicionLibreRegistro()<<endl;
	metadata->setPosicionLibreRegistro(80);

	//	// metadata->crear();

	//	string registro1="almacenamiento=|estrategiaAlmacBloques|tamanio=|1000|clavePrimaria=|padron";
	//	string registro2="padron|dni|nombre|apellido|direccion|pais|cuidad";
	//	string registro3="0=|800|1=|100|2=|10|3=|100|4=|20|5=|40|6=|89|7=|500";
	//	metadata->irAlPrincipio();
	//	/*    metadata->escribirRegistroVariable(registro1);
	//    metadata->escribirRegistroVariable(registro2);
	//    metadata->escribirRegistroVariable(registro3);*/
	//	metadata->hidratarMetadata();
	//	metadata->getPosicionBloque(10,vec);
	//	cout<<"posicion del bloque :"<<vec[0]<<endl;
	//	cout<<"posicion dentro del bloque :"<<vec[1]<<endl;
	//	//	metadata->guardar(registro2);
	//	//	metadata->guardar(registro3);
	//	vec.clear();
	//	string registro4="1=|20000000|2=|200|3=|200|4=|200|5=|20000000000000000000000000|6=|200|7=|200000000000000";
	//	metadata->getPosicionBloque(10,vec);
	//	cout<<"posicion del bloque 2 :"<<vec[0]<<endl;
	//	cout<<"posicion dentro del bloque 2 :"<<vec[1]<<endl;
	//	vec.clear();
	//	metadata->getPosicionBloque(10,vec);
	//	cout<<"posicion del bloque 3 :"<<vec[0]<<endl;
	//	cout<<"posicion dentro del bloque 3 :"<<vec[1]<<endl;
	//	metadata->guardarMapaAtributosVariables();
	// 	  metadata->escribirMetadata(registro1);
	//   metadata->hidratarMetadata();
	//    cout<<"tamanio : "<<metadata->getValorAtributosFijos(TAMANIO)<<endl;
	//    cout<<"ESTRATEGIA_ALMACENAMIENTO : "<<metadata->getValorAtributosFijos(ESTRATEGIA_ALMACENAMIENTO)<<endl;
	//    cout<<"CLAVE_PRIMARIA : "<<metadata->getValorAtributosFijos(CLAVE_PRIMARIA)<<endl;
	//    cout<<"tamanio vacio en bloque : "<<metadata->getValorAtributosVariables("1")<<endl;
	//    metadata->guardarPrimeraLinea(registro1);
	//    cout<<"tamanio vacio en bloque : "<<metadata->getValorAtributosVariables("1")<<endl;*/

	//    Alumno* alumno2 = new Alumno("oscar","Richard Dubini","entre rios");
	//    alumno2->serializarBinario();
	//    cout<<"tags: "<<alumno2->getNombreAtributos()<<endl;
	//    delete alumno2;
//	metadata->cerrar();
	delete metadata;
	cout<<"se escribio el archivo"<<endl;
	return 0;
}
