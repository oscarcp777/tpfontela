/*
 * Define.h
 *
 *  Created on: 04/10/2009
 *      Author: oscar
 */

#ifndef DEFINE_H_
#define DEFINE_H_
#define CLAVE_TAMANIO "|tamanio=|"
#define CLAVE_ALMACENAMIENTO "almacenamiento=|"
#define CLAVE_TAG_PRIMARIA "|clavePrimaria=|"
#define PRIMER_BLOQUE "0=|"
#define PRIMER_REGISTRO "|0|"
#define PORCENTAJE_ESPACIO_LIBRE_BLOQUE 0.1
#define ESTRATEGIA_ALMACENAMIENTO_TEXTO "estrategiaAlmacTexto"
#define ESTRATEGIA_ALMACENAMIENTO_REGISTROS "estrategiaAlmacRegistros"
#define ESTRATEGIA_ALMACENAMIENTO_BLOQUES "estrategiaAlmacBloques"
#define ARCHIVO "archivo"
#define BUFFER "buffer"
#define BINARIO "binario"
#define TEXTO "texto"
#define DELIMITADOR "|"
#define DELIMITADOR_SHARP "#"
#define COMPUESTO "compuesto"
#define ALMACENAMIENTO_ARCHIVO 0
#define ALMACENAMIENTO_BUFFER 1
#define TAM_BUFFER 1024
#define INDEXADO_HASH_EXTENSIBLE "indexadoHashExtensible"
#define INDEXADO_BSHARP "indexadoBSharp"
#define METADATA "MetaData"
#define ESTRATEGIA_ALMACENAMIENTO "almacenamiento"
#define TIPO_INDEXACION "indexacion"
#define CLAVE_INDEXACION "|indexacion=|"
#define TAMANIO "tamanio"
#define CLAVE_PRIMARIA "clavePrimaria"
class Define{
public:
	static const char DELIMITADOR1 = '|';
};


#endif /* DEFINE_H_ */
