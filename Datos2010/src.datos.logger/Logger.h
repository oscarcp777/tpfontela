/*
 *  Logger.h
 *
 *  Created on: 26/03/2010
 *      Author: nelson ramos
 */

#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <fstream>
#include "../src.datos.utils/Define.h"

using namespace std;

class Logger{

private:

	static Logger* logger;
	fstream file;
	char* date;
	int sizeFile;
	int coutFiles;

	/*
	 * Apertura del archivo, si este está creado lo abre,
	 * si no esta creado lo crea y lo deja en un estado
	 * valido para su utilizacion.
	 *
	 * @param	file: Archivo que se va a abrir.
	 * @param	fileName: Nombre del archivo que se va a abrir.
	 */
	void open(fstream* file, string fileName);

	/*
	 * Escritura del archivo, si este no existe el logger
	 * lo crea y lo deja en un estado valido para su escritura.
	 * Si el archivo existe simplemente escribe sobre este.
	 *
	 * @param	file: Archivo que se va a escribir.
	 * @param	fileName: Nombre del archivo que se va a escribir.
	 */
	void write(fstream* file,string cadena);
	/*
	 * Funcion auxiliar del logger que proporciona
	 * la fecha y hora del sistema operativo almacenada en un
	 * string.
	 *
	 * @return	Retorna la fecha y hora del sistema.
	 */
	string getTimeSystem();
	/*
	 * Metodo privado del logger que realiza un split del archivo
	 * actual copiando todo el contenido de este hacia otro nuevo.
	 *
	 * @param	cadena: String que se copia en el archivo actual
	 * 			luego de terminar el split.
	 *
	 */
	void split(string cadena);
	/*
	 * Constructor privado que permite realizar una sola instancia
	 * del logger mediante el metodo getInstance().
	 *
	 * @param	sizeFile: Tamanio maximo del archivo. Por defaul sera de
	 * 			512 Bytes, pero el usuario podra cambiar este
	 * 			tamanio invocando al metodo setSizeFile(...).
	 */
	Logger(int sizeFile = MAX_FILE_SIZE);

public:
	int countRead;
	int countWrite;
	/*
	 * Instanciacion del logger. Se obtiene una unica instancia de
	 * este.
	 *
	 * @return	Se obtiene un puntero a la unica instancia del logger.
	 *
	 */
	static Logger* getUnicaInstancia();
	/*
	 * Modifica el tamaño maximo del archivo, se recomienda llamar a
	 * este metodo luego de pedir una instancia de logger y no
	 * volverlo a llamar.
	 *
	 * @param	fileSize: Tamanio maximo que tendra el archivo.
	 *
	 */
	void setSizeFile(int fileSize);
	/*
	 * Escribe en el archivo del logger, un string que se desea loggear.
	 *
	 * @param	cadena: String que se desea almacenar en el archivo.
	 */
	void info(string cadena);
	/*
	 * Escribe en un nuevo archivo, todo el logger.
	 *
	 * @param	fileName: Nombre del archivo en el cual se va a escribir
	 * 			toda la informacion que contiene el logger.
	 */
	void print(string fileName);
	/*
	 * Busca dentro del logger la cadena solicitada retornando la
	 * linea donde hay coincidencia mostrandola por salida estandar.
	 *
	 * @param	cadena: String que se buscara dentro del logger.
	 */
	void search(string cadena);
	/*
	 * Libera los recursos solicitados por el logger. Ya sea el
	 * cierre de archivos abiertos como liberacion de memoria
	 * pedida por el logger.
	 *
	 */
	~Logger();
};

#endif /* LOGGER_H_ */
