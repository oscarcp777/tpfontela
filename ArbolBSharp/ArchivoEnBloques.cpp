/*
 * ArchivoEnBloques.cpp
 *
 *  Created on: Oct 24, 2009
 *      Author: dan
 */


#include "ArchivoEnBloques.h"


	/**
	 * Constructor con parametros.
	 * El bloque cero se usa para datos de control. NO utlizar el bloque cero para guardar bloques.
	 * Si el archivo no existe, se crea, y se verifica que el tamaño de bloque sea el correcto.
	 *
	 * @param n El tamaño del bloque que sale de hacer 2^n. n >= 7, es decir, bloques mayores o iguales a 128 bytes.
	 * @param path El path completo al archivo.
	 * @throws IOException Lanzada si existe un error en la creacion o apertura de archivo.
	 * @throws IllegalArgumentException Se lanza si el parametro n no cumple las restricciones.
	 */
	 ArchivoEnBloques::ArchivoEnBloques(int n, string path){
		//if (n < 7) this.lanzarExcepcionErrorN();
		tamBloque = (int)pow(2.0, n);
		byte* bloque = new byte[tamBloque];

		//Verifico si el archivo existe, sino lo junto con su bloque 0, que contiene el tamaño del bloque del archivo.
		if (lstat(path.c_str(), &datosDeArchivo)) {
			//Abro el archivo
			//stream = new RandomAccessFile(this.archivo,"rw");
			archivo.open(path.c_str(),fstream::out);
			//Verifico que exista el bloque 0 del tamaño correcto.
			/*if (archivo.length() < this.tamBloque) {
				this.cerrar();
				throw new IOException("El archivo especificado no contiene el bloque de encabezado necesario, o el tamaño de bloque especificado no coincide con el indicado en el bloque de encabezado del archivo.");
			}*/

			//Leo el bloque 0 y verifico que el tamaño de bloque especificado sea el mismo
			archivo.seekp(0);
			archivo.read(static_cast<const char*>(StringUtils::arrayToString(bloque,tamBloque).c_str()),tamBloque);
			if (tamBloque != BloqueUtils::byteArrayToInt(bloque, 0)) {
				cerrar();

			}

		}
		else
		{
			//Creo el archivo
			//stream = new RandomAccessFile(this.archivo,"rw");

			archivo.open(path.c_str(),fstream::in);
			//Inicializo el bloque 0 con el tamaño de bloque del archivo
			byte* entero = BloqueUtils::intToByteArray(tamBloque);
			int i;
			for (i = 0; i < 4; i++) bloque[i] = entero[i];
			archivo.seekp(0);
			archivo.write(StringUtils::arrayToString(bloque,tamBloque).c_str(), tamBloque);
		}
		stat(path.c_str(),&datosDeArchivo);//para obtener la informacion del archivo
	}

	/**
	 * Cierra el archivo
	 *
	 * @throws IOException
	 */
	void ArchivoEnBloques::cerrar(){
		archivo.close();
	}

	/**
	 * Retorna el tamanio de los bloques del archivo.
	 * @return Retorna el tamanio de los bloques del archivo.
	 */
	int ArchivoEnBloques::getTamanioBloque() { return tamBloque; }

	/**
	 * Retorna la cantidad de bloques de datos del archivo, incluido al bloque 0.
	 * @return Retorna la cantidad de bloques de datos del archivo.
	 */
	int ArchivoEnBloques::getCantidadBloques() { return (int)(datosDeArchivo.st_size/tamBloque); }

	/**
	 * Agrega un nuevo bloque al final del archivo.
	 * @param b El byte array con el bloque a agregar.
	 * @return Retorna el numero del nuevo bloque.
	 * @throws IOException Lanzada si existe un error en el acceso al archivo.
	 * @throws IllegalArgumentException Se lanza si el tamaño del bloque es menor que el tamaño de bloque del archivo.
	 *
	 */
	int ArchivoEnBloques::agregarBloque(byte b[],int tamanioB){
		//if (this.tamBloque > b.length) this.lanzarExcepcionErrorTamanioBloque();   ver despues
		archivo.seekp(datosDeArchivo.st_size);
		archivo.write(StringUtils::arrayToString(b,tamanioB).c_str(), tamBloque);
		return (getCantidadBloques() - 1);
	}

	/**
	 * Reescribe un bloque en el archivo
	 * @param bloque El bloque a reescribir
	 * @param n El número de bloque a reescribir. n >= 1.
	 * @throws IOException Lanzada si existe un error en el acceso al archivo.
	 * @throws IllegalArgumentException Se lanza si el parametro n no cumple las restricciones, o si el tamaño del bloque es menor que el tamaño de bloque del archivo.
	 */
	void ArchivoEnBloques::modificarBloque(byte b[], int tamanioB, int n){
		//if (n <= 0) this.lanzarExcepcionErrorN();
		//if (this.tamBloque > b.length) this.lanzarExcepcionErrorTamanioBloque(); ver despues
		int posicion = n * tamBloque;
		//if (posicion >= this.stream.length()) throw new IOException("El número de bloque dado no existe en el archivo.");
		//else ver despues
		//{
			archivo.seekp(posicion);
			archivo.write(StringUtils::arrayToString(b,tamanioB).c_str(), tamBloque);
		//}

	}

	/**
	 *
	 * @param b El byte array donde escribir el bloque. Debe ser al menos el tamaño de bloque del archivo.
	 * @param n El número de bloque a leer. n >= 1.
	 * @return Retorna el bloque con los datos del bloque leido.
	 * @throws IOException Lanzada si existe un error en el acceso al archivo.
	 * @throws IllegalArgumentException Se lanza si el parametro n no cumple las restricciones, o si el tamaño del bloque es menor que el tamaño de bloque del archivo.
	 */
	byte* ArchivoEnBloques::leerBloque(byte b[], int tamanioB, int n){
		int cantbytesleidos=0;
		//if (n <= 0) this.lanzarExcepcionErrorN();
		//if (this.tamBloque > b.length) this.lanzarExcepcionErrorTamanioBloque();
		int posicion = n * tamBloque;
		//if (posicion >= this.stream.length()) throw new IOException("El número de bloque dado no existe en el archivo.");
		//else
		//{
			archivo.seekp(posicion);
			 archivo.read((char*)StringUtils::arrayToString(b,tamanioB).c_str(), tamBloque);
			  cantbytesleidos =archivo.tellp();
			  cantbytesleidos=cantbytesleidos-posicion;
		//	if (cantbytesleidos != tamBloque) throw new IOException("La cantidad de bytes leidos es distinta al tamaño de bloque del archivo.");
		//}
		return b;
	}
