/*
 * FabricaDeRecursosDeAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include <iostream>
#include "../Composite/Componente.h"
#include "../Almacenamiento/Metadata.h"
#ifndef FABRICADERECURSOSDEALMACENAMIENTO_H_
#define FABRICADERECURSOSDEALMACENAMIENTO_H_
#include <map>
#include "../fabricas/FabricaAbstracta.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
using namespace std;
class FabricaDeRecursosDeAlmacenamiento {
private:
	static FabricaDeRecursosDeAlmacenamiento* unicaInstanciaFabrica;
	FabricaDeRecursosDeAlmacenamiento();

private:
	map<string , FabricaAbstracta*> mapaFabricas;

public:
	/**
	 * Enumerado de elementos posibles, para poder utilizar como claves de la fabrica
	 */

	FabricaAbstracta* getFabrica(string clave);
	static FabricaDeRecursosDeAlmacenamiento* obtenerInstancia();
	virtual ~FabricaDeRecursosDeAlmacenamiento();

	/**
	 * pre: ninguna
	 * post: este metodo se encarga de crear un  recurso de almacenamiento para :
	 * 1.- guardar registros en archivos de texto,
	 * 2.- guardar registros de tamanio fijo  en  archivos binarios
	 * 3.- guardar  bloques con registro de tamanio variable en archivos binarios
	 *
	 *    string estrategiaAlmacenamiento:estrategia para almacenar los registros en disco esta puede ser ESTRATEGIA_ALMACENAMIENTO_TEXTO,
	 *                                    ESTRATEGIA_ALMACENAMIENTO_REGISTROS,ESTRATEGIA_ALMACENAMIENTO_BLOQUES
	 *
	 *   int tamanio: tamanio ingresado segun corresponda con la estrategia seleccionada, de los registros de tamanio fijo
	 *                o de los bloques con registros variables en el caso de la ESTRATEGIA_ALMACENAMIENTO_TEXTO este parametro
	 *                no es utilizado
	 *
	 *   string ruta: ruta donde guardar el archivo
	 *   string nombreArchivo: nombre con el cual se persisitira el archivo
	 *
	 *   string clavePrimaria: nombre del campo del registro que se usara como clave primaria de los registros que se persitiran en el archivo,
	 *                        en caso de que esta este conformada por mas de un campo debera ingresarse separados por espacios
	 *                        Ejemplo: "dni padron apellido"
	 *
	 *   string tipoIndexacion: tipo de indexacion a selecionar pudiendo ser : INDEXADO_BSHARP O INDEXADO_HASH_EXTENSIBLE
	 *   Componente* componente: instancia del componente que va ser persistido como registro debera tener implemetado el metodo serializar
	 */
	RecursoDeAlmacenamiento* crearRecursoDeAlmacenamientoEnArchivo(string estrategiaAlmacenamiento,int tamanio,string ruta,
			string nombreArchivo,string clavePrimaria,string tipoIndexacion,Componente* componente);
	/**
	 * pre: ninguna
	 * post:  este metodo se encarga de crear un  recurso de almacenamiento para :
	 * 1.- guardar registros en buffer,
	 * 2.- guardar registros de tamanio fijo  en  buffer
	 * 3.- guardar  bloques con registro de tamanio variable en buffer
	 *
	 *    string estrategiaAlmacenamiento:estrategia para almacenar los registros en buffer esta puede ser ESTRATEGIA_ALMACENAMIENTO_TEXTO,
	 *                                    ESTRATEGIA_ALMACENAMIENTO_REGISTROS,ESTRATEGIA_ALMACENAMIENTO_BLOQUES
	 *
	 *   int tamanio: tamanio ingresado segun corresponda con la estrategia seleccionada, de los registros de tamanio fijo
	 *                o de los bloques con registros variables en el caso de la ESTRATEGIA_ALMACENAMIENTO_TEXTO este parametro
	 *                no es utilizado
	 *
	 *   string clavePrimaria: nombre del campo del registro que se usara como clave primaria de los registros que se persitiran en el archivo,
	 *                        en caso de que esta este conformada por mas de un campo debera ingresarse separados por espacios
	 *                        Ejemplo: "dni padron apellido"
	 *   Componente* componente: instancia del componente que va ser persistido como registro debera tener implemetado el metodo serializar
	 */
	RecursoDeAlmacenamiento* crearRecursoDeAlmacenamientoEnBuffer(string estrategiaAlmacenamiento,int tamanio,string clavePrimaria,Componente* componente);
	/**
	 * pre: ninguna
	 * post:  este metodo se encarga de crear un  recurso de almacenamiento para :
	 * 1.- guardar registros en archivos de texto y en un buffer,
	 * 2.- guardar registros de tamanio fijo  en  archivos binarios y en un buffer
	 * 3.- guardar  bloques con registro de tamanio variable en archivos binarios y en un buffer
	 *
	 *    string estrategiaAlmacenamiento:estrategia para almacenar los registros en disco y en un buffer esta puede ser
	 *                                    ESTRATEGIA_ALMACENAMIENTO_TEXTO,ESTRATEGIA_ALMACENAMIENTO_REGISTROS,ESTRATEGIA_ALMACENAMIENTO_BLOQUES
	 *
	 *   int tamanio: tamanio ingresado segun corresponda con la estrategia seleccionada, de los registros de tamanio fijo
	 *                o de los bloques con registros variables en el caso de la ESTRATEGIA_ALMACENAMIENTO_TEXTO este parametro
	 *                no es utilizado
	 *   int cantidadRegistrosEnMemoria : cantidad de registros/ bloques que seran almacenados en memoria en el buffer
	 *
	 *   string ruta: ruta donde guardar el archivo
	 *   string nombreArchivo: nombre con el cual se persisitira el archivo
	 *
	 *   string clavePrimaria: nombre del campo del registro que se usara como clave primaria de los registros que se persitiran en el archivo,
	 *                        en caso de que esta este conformada por mas de un campo debera ingresarse separados por espacios
	 *                        Ejemplo: "dni padron apellido"
	 *   string tipoIndexacion: tipo de indexacion a selecionar pudiendo ser : INDEXADO_BSHARP# O INDEXADO_HASH_EXTENSIBLE
	 *    Componente* componente: instancia del componente que va ser persistido como registro debera tener implemetado el metodo serializar
	 */
	RecursoDeAlmacenamiento* crearRecursoDeAlmacenamientoEnArchivoConBuffer(string estrategiaAlmacenamiento,int tamanio,string ruta,int cantidadRegistrosEnMemoria
			,string nombreArchivo,string clavePrimaria,string tipoIndexacion,Componente* componente);

	/**
	 *
	 * pre: el archivo a abrir ya debe de existir previamente y conservara las caracteristicas  que se ingresaron
	 * durante su creacion en caso de no existir el archivo el metodo lanzara una excepcion
	 * post: este metodo se encarga de abrir un  recurso de almacenamiento para :
	 * 1.- guardar registros en archivos de texto existentes previamente,
	 * 2.- guardar registros de tamanio fijo  en  archivos binarios existentes previamente,
	 * 3.- guardar  bloques con registro de tamanio variable en archivos binarios existentes previamente,
	 *   string ruta: ruta donde se encontrara  el archivo a abrir
	 *   string nombreArchivo: nombre del archivo que sera abierto
	 */
	RecursoDeAlmacenamiento* abrirRecursoDeAlmacenamientoEnArchivo(string ruta,string nombreArchivo);
	/**
	 *
	 * pre: el archivo a abrir ya debe de existir previamente y conservara las caracteristicas  que se ingresaron
	 * durante su creacion, en caso de no existir el archivo el metodo lanzara una excepcion
	 * post: este metodo se encarga de abrir un  recurso de almacenamiento para :
	 * 1.- guardar registros en archivos de texto existentes previamente y en memoria en un buffer,
	 * 2.- guardar registros de tamanio fijo  en  archivos binarios existentes previamente y en memoria en un buffer,
	 * 3.- guardar  bloques con registro de tamanio variable en archivos binarios existentes previamente y en memoria en un buffer,
	 *   string ruta: ruta donde se encontrara  el archivo a abrir
	 *   string nombreArchivo: nombre del archivo que sera abierto
     *   int cantidadRegistrosEnMemoria : cantidad de registros/ bloques que seran almacenados en memoria en el buffer
	 *
	 */
	RecursoDeAlmacenamiento* abrirRecursoDeAlmacenamientoEnArchivoConBuffer(string ruta,string nombreArchivo,int cantidadRegistrosEnMemoria);
};

#endif /* FABRICADERECURSOSDEALMACENAMIENTO_H_ */
