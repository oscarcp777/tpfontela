//============================================================================
// Name        : ArbolBSharp.cpp
// Author      : Daniel
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "ArbolBSharp.h"

	/**
	 * Constructor
	 *
	 */

	ArbolBSharp::ArbolBSharp() {
		archivo= NULL;
	}

	/**
	 * Abre el arbol. Si no existe lo crea guardando la raiz vacia.
	 * @throws IOException
	 */

	void ArbolBSharp::abrir(){

		archivo = new ArchivoEnBloques(TAMANO_BLOQUE,ARCH_ARBOL);
		//TAMANO_BLOQUE_BYTES= archivo.getTamanioBloque();
		if (archivo->getCantidadBloques() == 1){
			crear();
		}
	}

	/**
	 * Cierra el arbol
	 * @throws IOException
	 */

	void ArbolBSharp::cerrar(){

		archivo.cerrar();

	}

	/**
	 * Busca un termino en el arbol
	 * @param termino Termino a buscar
	 * @return RegistroIndice: registro buscado
	 * @throws IOException
	 * @throws RegistroNoEncontradoException
	 */
	RegistroIndice ArbolBSharp::buscarTermino(string termino){
		Nodo hoja= obtenerHojaDelTermino(termino, BLOQUE_RAIZ);
		return ((NodoHoja)hoja).obtenerRegistroIndice(termino);
	}

	/**
	 * Modifica el registro
	 * @param registro Registro a modificar
	 * @throws IOException
	 * @throws RegistroNoEncontradoException
	 */

	void ArbolBSharp::modificarRegistro(RegistroIndice registro){

		Nodo hoja= obtenerHojaDelTermino(registro.getTermino(), BLOQUE_RAIZ);
		((NodoHoja)hoja).modificarRegistro(registro);
		//archivo.modificarBloque(hoja.getBuffer(), hoja.getBloque());
	}

	/**
	 * Inserta el registro en el arbol
	 * @param registro Registro a insertar
	 * @throws IOException
	 * @throws ClaveExistenteException
	 */

	void ArbolBSharp::insertar(RegistroIndice registro){

		try {
			this->buscarTermino(registro.getTermino());
			throw new ClaveExistenteException();
		} catch (RegistroNoEncontradoException e) {}

		byte* buffer= archivo.leerBloque(new byte[archivo.getTamanioBloque()], archivo.getTamanioBloque, BLOQUE_RAIZ);
		int nivel= buffer[0];
		Nodo nodoModificado= NULL;
		if (nivel == 0){
			nodoModificado= insert(registro,new NodoHoja(buffer,BLOQUE_RAIZ),NULL);
		}else{
			nodoModificado= insert(registro,new NodoInterno(buffer,BLOQUE_RAIZ,nivel),NULL);
		}
		if (nodoModificado != NULL){

			archivo.modificarBloque(nodoModificado.getBuffer(), BLOQUE_RAIZ);
		}

	}



	Nodo ArbolBSharp::insert(RegistroIndice registro,Nodo nodoLeido,Nodo nodoPadre){


		int nivel= nodoLeido.getNivel();
	    if (nivel == 0){
	    	byte* bufferModificado= ((NodoHoja)nodoLeido).agregarRegistro(registro);
	    	int proxHoja= BloqueUtils::byteArrayToInt(nodoLeido.getBuffer(), archivo.getTamanioBloque()-4);
	    	if (hayOverflowHoja(bufferModificado)){
	    		bufferModificado= BloqueUtils::concatena(bufferModificado, BloqueUtils::intToByteArray(proxHoja));
	    		Nodo nodoModificado= new NodoHoja(bufferModificado,nodoLeido.getBloque());
	    		return balancear(nodoModificado,nodoPadre, nodoLeido);
	    	}else{
	    		bufferModificado= BloqueUtils::concatena(bufferModificado, new byte[archivo.getTamanioBloque()-4-((NodoHoja)nodoLeido).getTamanioBuffer()+1]); //tamanio buffer +1 porque se agrego un registro igual esta incrementacion se debe hacer en el nodo hoja
	    		bufferModificado= BloqueUtils::concatena(bufferModificado, BloqueUtils::intToByteArray(proxHoja));
	    		archivo.modificarBloque(bufferModificado, ((NodoHoja)nodoLeido).getTamanioBuffer()+1,nodoLeido.getBloque()); //tamanio buffer +1 porque se agrego un registro igual esta incrementacion se debe hacer en el nodo hoja
	    		return NULL;
	    	}
	    }else{
	    	int bloque= NodoInterno.obtenerBloque(nodoLeido.getBuffer(),registro.getTermino());
	    	byte* bytes= archivo.leerBloque(new byte[archivo.getTamanioBloque()],archivo.getTamanioBloque(), bloque);
	    	int nivelHijo= bytes[0];
	    	Nodo nodoModificado= NULL;
	    	if (nivelHijo == 0){
	    		nodoModificado= insert(registro,new NodoHoja(bytes,bloque),nodoLeido);
	    	}else{
	    		nodoModificado= insert(registro,new NodoInterno(bytes,bloque,nivelHijo),nodoLeido);
	    	}
	    	if (nodoModificado != NULL){
	    		if (hayOverflowNodo(nodoModificado.getBuffer())){
	    			return balancear(nodoModificado,nodoPadre,nodoLeido);
	    		}else{
	    			byte* bufferModificado= NodoInterno.completarBuffer(nodoModificado.getBuffer());
	    			archivo.modificarBloque(bufferModificado, nodoLeido.getBloque());
	    			return NULL;
	    		}

	    	}
	    	return nodoModificado;
	    }

	}

	int ArbolBSharp::cuantoOverflow(Nodo nodoModificado,int tipo) {
		int nivel= nodoModificado.getBuffer()[0];
		if (nivel== 0){
			RegistroIndice* registros= ((NodoHoja)nodoModificado).obtenerRegistros();
			int i= 0;
			bool listo= false;
			while (!listo){
				if (tipo == 0){
					registros= NodoHoja.eliminarPrimerRegistro(registros);
				}else{
					registros= NodoHoja.eliminarUltimoRegistro(registros);
				}
				byte* bytes= NodoHoja.obtenerByteArrayRegistros(registros);
				bytes= BloqueUtils::concatena(new byte[1], bytes);
				if (!hayOverflowHoja(bytes)){
					listo= true;
				}
				i++;

			}
			return i;
		}else{
			return 1;
		}

	}

	bool ArbolBSharp::hayOverflowHoja(byte buffer[],int tamanioBuffer) {
		return (tamanioBuffer+4 > archivo.getTamanioBloque());
	}

	bool ArbolBSharp::hayOverflowNodo(byte buffer[]) {
		int cantidadClaves= buffer[1];
		return cantidadClaves > CLAVES_MAX;
	}

	Nodo ArbolBSharp::balancear(Nodo nodoModificado,Nodo nodoPadre, Nodo nodoLeido){
		if (nodoPadre == NULL){
			return partirRaiz(nodoModificado);
		}else{
			int bloqueVecinoDerecho= buscarVecinoDerecho(nodoPadre, nodoLeido);
			if (bloqueVecinoDerecho != 0){
				return balancearConVecino(nodoModificado, nodoPadre, bloqueVecinoDerecho,1,cuantoOverflow(nodoModificado,1));
			}else{
				int bloqueVecinoIzquierdo= buscarVecinoIzquierdo(nodoPadre, nodoLeido);
				return balancearConVecino(nodoModificado,nodoPadre,bloqueVecinoIzquierdo,0,cuantoOverflow(nodoModificado,0));
			}
		}
	}

	Nodo ArbolBSharp::partirRaiz(Nodo nodoModificado){
		int nivel= nodoModificado.getNivel();
		byte* bufferRaiz= new byte[2];
		bufferRaiz[0]= (byte)(nivel + 1);
		bufferRaiz[1]= 1;
		int tamanioBufferRaiz=2;
		string clave=NULL;
		if (nivel == 0){
			RegistroIndice* registros= ((NodoHoja)nodoModificado).obtenerRegistros();
			list<RegistroIndice*> listaRegistros= NodoHoja.dividirRegistrosIndice(registros,2);
			list<byte*> listaBuffers= new list<byte*>();
			iterator<RegistroIndice*> iterador;
			iterador=listaRegistros.begin();
			while (iterador != listaRegistros.end()) {
				RegistroIndice* registro = *iterador;
				listaBuffers.add(NodoHoja.obtenerByteArrayRegistros(registro));
				clave= registro[0].getTermino();
				iterador++;
			}
			int bloqueProxHoja= archivo.getCantidadBloques()+1;
			Iterator<byte*> iteradorBuffer;
			for (iteradorBuffer = listaBuffers.begin(); listaBuffers.end();iteradorBuffer++) {
				byte* bufferRegistro =  *iteradorBuffer;
				byte* bufferBloque= new byte[1];
				bufferBloque[0]= 0;
				bufferBloque= BloqueUtils::concatena(bufferBloque, bufferRegistro);
				int bloqueHijo= archivo.agregarBloque(NodoHoja.completarBuffer(bufferBloque,bloqueProxHoja));
				bufferRaiz= BloqueUtils::concatena(bufferRaiz, BloqueUtils::intToByteArray(bloqueHijo),tamanioBufferRaiz,&4); //tamanio buffer raiz 2, tamanio bloque hijo 4
				tamanioBufferRaiz=tamanioBufferRaiz+4;
				if (bloqueProxHoja != 0){
					byte* bufferClave= StringUtils::stringToArray(clave);
					bufferClave= BloqueUtils::concatena(bufferClave, new byte[TAMANO_ELEMENTO-4-strlen(clave.c_str())],strlen(clave.c_str()));
					bufferRaiz= BloqueUtils::concatena(bufferRaiz, bufferClave,tamanioBufferRaiz,&(TAMANO_ELEMENTO-4));
					tamanioBufferRaiz=tamanioBufferRaiz+TAMANO_ELEMENTO-4;
				}
				bloqueProxHoja= 0;

			}
		}else{
			Elemento* elementos= ((NodoInterno)nodoModificado).obtenerElementos();
			list<Elemento*> listaElementos= NodoInterno.dividirElementos(elementos,2);
			iterator<Elemento*> iterador = listaElementos.begin();
			Elemento* elementosIzquierda= *iterador; //obtengo el primer elemento de la coleccion
			byte* bytesNivelHijos= new byte[1];
			bytesNivelHijos[0]= (byte)nivel;
			byte* bytesElementosIzquierda= NodoInterno.obtenerByteArrayElementos(elementosIzquierda);
			byte* bufferElementosIzquierda= NodoInterno.completarBuffer(bytesElementosIzquierda);
			int bloqueIzquierdo= archivo.agregarBloque(BloqueUtils::concatena(bytesNivelHijos,bufferElementosIzquierda));
			iterador++;
			Elemento* elementosDerecha= *iterador;
			Elemento elementoRaiz= elementosDerecha[0];
			byte* bytesElementosDerecha= NodoInterno.obtenerByteArrayElementos(NodoInterno.eliminarPrimerElemento(elementosDerecha));
			byte* bufferElementosDerecha= NodoInterno.completarBuffer(bytesElementosDerecha);
			int bloqueDerecho= archivo.agregarBloque(BloqueUtils::concatena(bytesNivelHijos, bufferElementosDerecha));
			byte* bloqueIzqArray= BloqueUtils::intToByteArray(bloqueIzquierdo);
			byte* bloqueDerArray = BloqueUtils::intToByteArray(bloqueDerecho);
			bufferRaiz= BloqueUtils::concatena(bufferRaiz, bloqueIzqArray,tamanioBufferRaiz,&tamanioBufferRaiz);
			tamanioBufferRaiz = tamanioBufferRaiz + 4;
			bufferRaiz= BloqueUtils::concatena(bufferRaiz, StringUtils::stringToArray(elementoRaiz.getClave()),tamanioBufferRaiz,&strlen(elementoRaiz.getClave().c_str()));
			tamanioBufferRaiz = tamanioBufferRaiz + strlen(elementoRaiz.getClave().c_str());
			bufferRaiz= BloqueUtils::concatena(bufferRaiz, new byte[TAMANO_ELEMENTO-4-strlen(elementoRaiz.getClave().c_str())],tamanioBufferRaiz,TAMANO_ELEMENTO-4-strlen(elementoRaiz.getClave().c_str()));
			tamanioBufferRaiz = tamanioBufferRaiz + TAMANO_ELEMENTO-4-strlen(elementoRaiz.getClave().c_str());
			bufferRaiz= BloqueUtils::concatena(bufferRaiz, bloqueDerArray, tamanioBufferRaiz, 4);
			tamanioBufferRaiz=tamanioBufferRaiz+4;
		}
		bufferRaiz= BloqueUtils::concatena(bufferRaiz, new byte[archivo.getTamanioBloque()-tamanioBufferRaiz],tamanioBufferRaiz,archivo.getTamanioBloque()-tamanioBufferRaiz);
		tamanioBufferRaiz=tamanioBufferRaiz + (archivo.getTamanioBloque()-tamanioBufferRaiz);
		return new NodoInterno(bufferRaiz,BLOQUE_RAIZ,nivel+1,tamanioBufferRaiz);
	}



	Nodo ArbolBSharp::balancearConVecino(Nodo nodoModificado, Nodo nodoPadre, int bloqueVecino,int tipo,int cantidad){
		byte* bufferVecino= archivo.leerBloque(new byte[archivo.getTamanioBloque()],archivo.getTamanioBloque(), bloqueVecino);
		int nivel= bufferVecino[0];
		int tamanioBufferModificado=0;
		Nodo nodoVecino;
		RegistroIndice* registro= new RegistroIndice[cantidad];
		if (nivel==0){
			nodoVecino= new NodoHoja(bufferVecino,bloqueVecino,archivo.getTamanioBloque());
			RegistroIndice* registros= ((NodoHoja)nodoModificado).obtenerRegistros();
			if (tipo == 0){
				StringUtils::vecTovec(registros, 0, registro, 0, cantidad);
			}else{
				StringUtils::vecTovec(registros, ((NodoHoja)nodoModificado).getCantidadRegistros()-cantidad, registro, 0, cantidad);
			}
		}else{
			nodoVecino= new NodoInterno(bufferVecino,bloqueVecino,nivel,archivo.getTamanioBloque());
		}
		if (!estaLleno(nodoVecino,cantidad,registro,cantidad)){
			byte* bufferModificado;
			if(tipo == 0){
				bufferModificado= distibuirIzquierda(nodoModificado, nodoVecino, nodoPadre,cantidad,&tamanioBufferModificado);
			}else{
				bufferModificado= distibuirDerecha(nodoModificado, nodoVecino, nodoPadre,cantidad,&tamanioBufferModificado);
			}
			return new NodoInterno(bufferModificado,nodoPadre.getBloque(),nodoPadre.getNivel(),tamanioBufferModificado);
		}else{
			byte* bufferModificado;
			if (tipo == 0){
				bufferModificado = split(nodoVecino,nodoModificado,nodoPadre,&tamanioBufferModificado);
			}else{
				bufferModificado = split(nodoModificado,nodoVecino,nodoPadre,&tamanioBufferModificado);
			}
			return new NodoInterno(bufferModificado,nodoPadre.getBloque(),nodoPadre.getNivel(),tamanioBufferModificado);
		}
	}

	byte* ArbolBSharp::distibuirIzquierda(Nodo nodoModificado, Nodo nodoVecino, Nodo nodoPadre,int cantidad, int* tamanioBufferRetorno){
		int nivel= nodoModificado.getNivel();
		byte* bytesNivel= new byte[1];
		bytesNivel[0]= (byte) nivel;
		int cantRegistrosNodoVecino=((NodoHoja)nodoVecino).getCantidadRegistros();
		int cantRegistrosNodoModificado=((NodoHoja)nodoModificado).getCantidadRegistros();
		int tamanioBufferNodoPadre=0;
		int tamanioBufferNodoVecino=0;
		int tamanioBufferNodoModificado=0;
		int cantBytesRegistroModificado=0;
		int cantElementosPadre = ((NodoInterno)nodoPadre).getCantidadElementos();
		if(nivel == 0){
			RegistroIndice* registrosModificado= ((NodoHoja)nodoModificado).obtenerRegistros();
			RegistroIndice* registrosVecino= ((NodoHoja)nodoVecino).obtenerRegistros();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();
			for (int i = 0; i < cantidad; i++) {
				registrosVecino= NodoHoja.agregarRegistroAlFinal(registrosVecino, registrosModificado[0],&cantRegistrosNodoVecino);
				registrosModificado= NodoHoja.eliminarPrimerRegistro(registrosModificado,&cantRegistrosNodoModificado);
				int indice= NodoInterno.obtenerElementoaIzquierda(elementosPadre,new Elemento(0,0,registrosVecino[cantRegistrosNodoVecino-1].getTermino()));
				elementosPadre[indice]= new Elemento(nodoVecino.getBloque(),nodoModificado.getBloque(),registrosModificado[0].getTermino());
			}
			byte* bytesRegistroModificado= NodoHoja.obtenerByteArrayRegistros(registrosModificado,cantRegistrosNodoModificado,&cantBytesRegistroModificado);
			int proxHojaModificado= BloqueUtils::byteArrayToInt(nodoModificado.getBuffer(), nodoModificado.getTamanioBuffer()-4);
			bytesRegistroModificado= NodoHoja.completarBuffer(bytesRegistroModificado, proxHojaModificado,&cantRegistrosNodoModificado);
			byte* bufferRegistroModificado= BloqueUtils::concatena(bytesNivel, bytesRegistroModificado,1,&cantRegistroNodoModificado);

			archivo.modificarBloque(bufferRegistroModificado,cantRegistroNodoModificado,nodoModificado.getBloque());
			byte* bytesRegistroVecino= NodoHoja.obtenerByteArrayRegistros(registrosVecino,cantRegistrosNodoVecino,&tamanioBufferNodoVecino);
			int proxHojaVecino= BloqueUtils::byteArrayToInt(nodoVecino.getBuffer(), nodoVecino.getTamanioBuffer()-4);
			bytesRegistroVecino= NodoHoja.completarBuffer(bytesRegistroVecino, proxHojaVecino,&tamanioBufferNodoVecino);
			byte* bufferRegistroVecino= BloqueUtils::concatena(bytesNivel, bytesRegistroVecino,1,&tamanioBufferNodoVecino);
			archivo.modificarBloque(bufferRegistroVecino,tamanioBufferNodoVecino,nodoVecino.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferNodoPadre=NodoInterno.obtenerByteArrayElementos(elementosPadre,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado, bufferNodoPadre, 1, &tamanioBufferNodoPadre);
			return bufferModificado;
		}else{
			Elemento* elementosModificado= ((NodoInterno)nodoModificado).obtenerElementos();
			Elemento* elementosVecino= ((NodoInterno)nodoVecino).obtenerElementos();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();

			for (int i = 0; i < cantidad; i++) {
				Elemento elementoModificado= elementosModificado[0];
				Elemento elementoVecino= elementosVecino[cantRegistrosNodoVecino-1];
				int indice= NodoInterno.obtenerElementoaIzquierda(elementosPadre,elementoModificado,cantElementosPadre);
				string clavePadre= elementoModificado.getClave();
				elementoModificado.setClave(elementosPadre[indice].getClave());
				elementoModificado.setHijoDer(elementoModificado.getHijoIzq());
				elementoModificado.setHijoIzq(elementoVecino.getHijoDer());
				elementosVecino= NodoInterno.agregarElementoAlFinal(elementosVecino, elementoModificado);
				cantElementosVecino=((NodoInterno)nodoVecino).getCantidadElementos();
				elementosModificado= NodoInterno.eliminarPrimerElemento(elementosModificado);
     			elementosPadre[indice].setClave(clavePadre);
			}
			byte* bytesNodoModificado= NodoInterno.obtenerByteArrayElementos(elementosModificado,cantRegistrosNodoModificado,&tamanioBufferNodoModificado);
			byte* bufferNodoModificado= BloqueUtils::concatena(bytesNivel, bytesNodoModificado, 1, &tamanioBufferNodoModificado);
			archivo.modificarBloque(NodoInterno.completarBuffer(bufferNodoModificado),nodoModificado.getBloque());
			byte* bytesNodoVecino= NodoInterno.obtenerByteArrayElementos(elementosVecino,cantRegistrosNodoVecino,&tamanioBufferNodoVecino);
			byte* bufferNodoVecino= BloqueUtils::concatena(bytesNivel, bytesNodoVecino, 1, &tamanioBufferNodoVecino);
			bufferNodoVecino= NodoInterno.completarBuffer(bufferNodoVecino, &tamanioBufferNodoVecino);
			archivo.modificarBloque(bufferNodoVecino, nodoVecino.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferNodoPadre = NodoInterno.obtenerByteArrayElementos(elementosPadre,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado, bufferNodoPadre, *tamanioBufferNodoModificado, &tamanioBufferNodoPadre);
			tamanioBufferRetorno=&tamanioBufferNodoPadre;
			return bufferModificado;
		}
	}

	byte* ArbolBSharp::distibuirDerecha(Nodo nodoModificado, Nodo nodoVecino, Nodo nodoPadre,int cantidad, int* tamanioBufferRetorno){
		int nivel= nodoModificado.getNivel();
		byte* bytesNivel= new byte[1];
		bytesNivel[0]= (byte) nivel;
		int cantRegistrosNodoVecino=((NodoHoja)nodoVecino).getCantidadRegistros();
		int cantRegistrosNodoModificado=((NodoHoja)nodoModificado).getCantidadRegistros();
		int tamanioBufferNodoPadre=0;
		int tamanioBufferNodoVecino=0;
		int tamanioBufferNodoModificado=0;
		int cantElementosPadre = ((NodoInterno)nodoPadre).getCantidadElementos();
		if(nivel == 0){
			RegistroIndice* registrosModificado= ((NodoHoja)nodoModificado).obtenerRegistros();
			RegistroIndice* registrosVecino= ((NodoHoja)nodoVecino).obtenerRegistros();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();
			for (int i = 0; i < cantidad; i++) {
				registrosVecino= NodoHoja.agregarRegistroAlComienzo(registrosVecino, registrosModificado[cantRegistrosNodoModificado-1],&cantRegistrosNodoVecino);
				registrosModificado= NodoHoja.eliminarUltimoRegistro(registrosModificado,&cantRegistrosNodoModificado);
				int indice= NodoInterno.obtenerElementoaDerecha(elementosPadre,new Elemento(0,0,registrosVecino[0].getTermino()));
				elementosPadre[indice]= new Elemento(nodoModificado.getBloque(),nodoVecino.getBloque(),registrosVecino[0].getTermino());
			}
			byte* bytesRegistroModificado= NodoHoja.obtenerByteArrayRegistros(registrosModificado,cantBytesRegistroModificado,&tamanioBufferNodoModificado);
			int proxHojaModificado= BloqueUtils::byteArrayToInt(nodoModificado.getBuffer(), nodoModificado.getTamanioBuffer()-4);
			bytesRegistroModificado= NodoHoja.completarBuffer(bytesRegistroModificado, proxHojaModificado,&tamanioBufferNodoModificado);
			byte* bufferRegistroModificado= BloqueUtils::concatena(bytesNivel, bytesRegistroModificado,1,&tamanioBufferNodoModificado);
			archivo.modificarBloque(bufferRegistroModificado,tamanioBufferNodoModificado,nodoModificado.getBloque());
			byte* bytesRegistroVecino= NodoHoja.obtenerByteArrayRegistros(registrosVecino,cantRegistrosNodoVecino,&tamanioBufferNodoVecino);
			int proxHojaVecino= BloqueUtils::byteArrayToInt(nodoVecino.getBuffer(), nodoVecino.getTamanioBuffer()-4);
			bytesRegistroVecino= NodoHoja.completarBuffer(bytesRegistroVecino, proxHojaVecino, &tamanioBufferNodoVecino);
			byte* bufferRegistroVecino= BloqueUtils::concatena(bytesNivel, bytesRegistroVecino,1,&tamanioBufferNodoVecino);
			archivo.modificarBloque(bufferRegistroVecino,tamanioBufferNodoVecino,nodoVecino.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferNodoPadre=NodoInterno.obtenerByteArrayElementos(elementosPadre,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado, bufferNodoPadre,tamanioBufferNodoModificado,&tamanioBufferNodoPadre);
			tamanioBufferRetorno=&tamanioBufferNodoPadre;
			return bufferModificado;
		}else{
			Elemento* elementosModificado= ((NodoInterno)nodoModificado).obtenerElementos();
			Elemento* elementosVecino= ((NodoInterno)nodoVecino).obtenerElementos();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();
			for (int i = 0; i < cantidad; i++) {
				Elemento elementoModificado= elementosModificado[cantRegistrosNodoModificado-1];
				Elemento elementoVecino= elementosVecino[0];
				int indice= NodoInterno.obtenerElementoaDerecha(elementosPadre,elementoModificado,cantElementosPadre);
				string clavePadre= elementoModificado.getClave();
				elementoModificado.setClave(elementosPadre[indice].getClave());
				elementoModificado.setHijoIzq(elementoModificado.getHijoDer());
				elementoModificado.setHijoDer(elementoVecino.getHijoIzq());
				elementosVecino= NodoInterno.agregarElementoAlComienzo(elementosVecino, elementoModificado, &cantRegistrosNodoVecino);
				elementosModificado= NodoInterno.eliminarUltimoElemento(elementosModificado,&cantRegistrosNodoModificado);
     			elementosPadre[indice].setClave(clavePadre);
			}
			byte* bytesNodoModificado= NodoInterno.obtenerByteArrayElementos(elementosModificado,cantRegistrosNodoModificado,&tamanioBufferNodoModificado);
			byte* bufferNodoModificado= BloqueUtils::concatena(bytesNivel, bytesNodoModificado,1,&tamanioBufferNodoModificado);
			bufferNodoModificado=NodoInterno.completarBuffer(bufferNodoModificado,&tamanioBufferNodoModificado);
			archivo.modificarBloque(bufferNodoModificado,nodoModificado.getBloque());
			byte* bytesNodoVecino= NodoInterno.obtenerByteArrayElementos(elementosVecino,cantRegistrosNodoVecino,&tamanioBufferNodoVecino);
			byte* bufferNodoVecino= BloqueUtils::concatena(bytesNivel, bytesNodoVecino,1,&tamanioBufferNodoVecino);
			bufferNodoVecino=NodoInterno.completarBuffer(bufferNodoVecino,&tamanioBufferNodoVecino);
			archivo.modificarBloque(bufferNodoVecino, nodoVecino.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferNodoPadre=NodoInterno.obtenerByteArrayElementos(elementosPadre,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado, bufferNodoPadre, tamanioBufferNodoModificado, &tamanioBufferNodoPadre);
			tamanioBufferRetorno=&tamanioBufferNodoPadre;
			return bufferModificado;
		}
	}


	byte* ArbolBSharp::split(Nodo nodoIzquierdo, Nodo nodoDerecho,Nodo nodoPadre,int* tamanioBufferRetorno){
		int nivel= nodoIzquierdo.getNivel();
		byte* bytesNivel= new byte[1];
		bytesNivel[0]= (byte) nivel;
		int cantRegistrosNodoIzquierdo=((NodoHoja)nodoIzquierdo).getCantidadRegistros();
		int cantRegistrosNodoDerecho=((NodoHoja)nodoDerecho).getCantidadRegistros();
		int tamanioBufferNodoIzquierdo=0;
		int tamanioBufferNodoDerecho=0;
		int tamanioBufferNodoMedio=0;
		int tamanioBufferNodoPadre=0;
		int cantElementosPadre = ((NodoInterno)nodoPadre).getCantidadElementos();
		int cantElementosMedio=0;
		if(nivel == 0){
			RegistroIndice* registrosIzquierdo= ((NodoHoja)nodoIzquierdo).obtenerRegistros();
			RegistroIndice* registrosDerecho= ((NodoHoja)nodoDerecho).obtenerRegistros();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();
			int indice= NodoInterno.obtenerElementoaDerecha(elementosPadre,new Elemento(0,0,registrosIzquierdo[0].getTermino()),cantElementosPadre);
			RegistroIndice* registrosEntero= NodoHoja.unir(registrosIzquierdo,cantRegistrosNodoIzquierdo,registrosDerecho,cantRegistrosNodoDerecho);
			list<RegistroIndice*> listaRegistros= NodoHoja.dividirRegistrosIndice(registrosEntero, 3, cantRegistrosNodoIzquierdo+cantRegistrosNodoDerecho);
			iterator iteradorRegistrosIndice = listaRegistro.begin();
			registrosIzquierdo=*iteradorRegistrosIndice; //elemento 0
			iteradorRegistrosIndice++;
			RegistroIndice* registrosMedio= *iteradorRegistrosIndice; //elemento 1
			iteradorRegistrosIndice++;
			registrosDerecho= *iteradorRegistrosIndice; //elemento 2
			Elemento* elementosPadreNuevo= NodoInterno.agregarElemento(elementosPadre,indice,new Elemento(archivo.getCantidadBloques(),nodoDerecho.getBloque(),registrosDerecho[0].getTermino()),&cantElementosPadre);
			elementosPadreNuevo[indice].setHijoDer(archivo.getCantidadBloques());
			elementosPadreNuevo[indice].setClave(registrosMedio[0].getTermino());
			byte* bytesRegistrosIzquierdo= NodoHoja.obtenerByteArrayRegistros(registrosIzquierdo,cantRegistrosNodoIzquierdo,&tamanioBufferNodoIzquierdo);
			bytesRegistrosIzquierdo= NodoHoja.completarBuffer(bytesRegistrosIzquierdo, tamanioBufferNodoIzquierdo,archivo.getCantidadBloques());
			byte* bufferRegistrosIzquierdo= BloqueUtils::concatena(bytesNivel, bytesRegistrosIzquierdo,1,&tamanioBufferNodoIzquierdo);
			archivo.modificarBloque(bufferRegistrosIzquierdo, tamanioBufferNodoIzquierdo,nodoIzquierdo.getBloque());
			byte* bytesRegistrosMedio= NodoHoja.obtenerByteArrayRegistros(registrosMedio,&tamanioBufferNodoMedio);
			bytesRegistrosMedio= NodoHoja.completarBuffer(bytesRegistrosMedio, tamanioBufferNodoMedio,nodoDerecho.getBloque());
			byte* bufferRegistrosMedio= BloqueUtils::concatena(bytesNivel, bytesRegistrosMedio,1,&tamanioBufferNodoMedio);
			archivo.agregarBloque(bufferRegistrosMedio);
			byte* bytesRegistrosDerecho= NodoHoja.obtenerByteArrayRegistros(registrosDerecho,&tamanioBufferNodoDerecho);
			int proxHojaDerecho= BloqueUtils::byteArrayToInt(nodoDerecho.getBuffer(),nodoDerecho.getTamanioBuffer()-4);
			bytesRegistrosDerecho= NodoHoja.completarBuffer(bytesRegistrosDerecho, tamanioBufferNodoDerecho,proxHojaDerecho);
			byte* bufferRegistrosDerecho= BloqueUtils::concatena(bytesNivel, bytesRegistrosDerecho,1,&tamanioBufferNodoDerecho);
			archivo.modificarBloque(bufferRegistrosDerecho, tamanioBufferNodoDerecho, nodoDerecho.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferNodoPadreNuevo=NodoInterno.obtenerByteArrayElementos(elementosPadreNuevo,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado, bufferNodoPadreNuevo, tamanioBufferNodoMedio, &tamanioBufferNodoPadre);
			tamanioBufferRetorno=&tamanioBufferNodoPadre;
			return bufferModificado;
		}else{
			Elemento* elementosIzquierdo= ((NodoInterno)nodoIzquierdo).obtenerElementos();
			Elemento* elementosDerecho= ((NodoInterno)nodoDerecho).obtenerElementos();
			Elemento* elementosPadre= ((NodoInterno)nodoPadre).obtenerElementos();
			int indice= NodoInterno.obtenerElementoaDerecha(elementosPadre,new Elemento(0,0,elementosIzquierdo[0].getClave()),cantElementosPadre);
			Elemento* elementosEntero= NodoInterno.unir(elementosIzquierdo,cantRegistrosNodoIzquierdo,elementosDerecho,cantRegistrosNodoDerecho,elementosPadre[indice]);
			list<Elemento*> listaElementos= NodoInterno.dividirElementos(elementosEntero, 3, cantRegistrosNodoIzquierdo+cantRegistroNodoDerecho+1);
			iterator iteradorElementos = listaElementos.begin();
			elementosIzquierdo= *iteradorElementos; // obtiene el elemento 0
			iteradorElementos++;
			Elemento* elementosMedio= *iteradorElementos; // obtiene el elemento 1
			iteradorElementos++;
			elementosDerecho= *iteradorElementos; // obtiene el elemento 2
			Elemento* elementosPadreNuevo= NodoInterno.agregarElemento(elementosPadre,indice,new Elemento(archivo.getCantidadBloques(),nodoDerecho.getBloque(),elementosMedio[elementosMedio.length-1].getClave()),&cantElementosPadre);
			elementosPadreNuevo[indice].setHijoDer(archivo.getCantidadBloques());
			elementosPadreNuevo[indice].setClave(elementosIzquierdo[cantRegistrosNodoIzquierdo-1].getClave());
			elementosIzquierdo=NodoInterno.eliminarUltimoElemento(elementosIzquierdo,&cantRegistrosNodoIzquierdo);
			byte* bytesElementosIzquierdo=NodoInterno.obtenerByteArrayElementos(elementosIzquierdo,cantRegistrosNodoIzquierdo,&tamanioBufferNodoIzquierdo);
			bytesElementosIzquierdo= NodoInterno.completarBuffer(bytesElementosIzquierdo,&tamanioBufferNodoIzquierdo);
			byte* bufferElementosIzquierdo= BloqueUtils::concatena(bytesNivel, bytesElementosIzquierdo,1,&tamanioBufferNodoIzquierdo);
			archivo.modificarBloque(bufferElementosIzquierdo, tamanioBufferNodoIzquierdo, nodoIzquierdo.getBloque());
			cantElementosMedio = (cantRegistrosNodoIzquierdo+cantRegistroNodoDerecho+1)/3;
			elementosMedio=NodoInterno.eliminarUltimoElemento(elementosMedio,&cantElementosMedio);
			byte* bytesElementosMedio= NodoInterno.obtenerByteArrayElementos(elementosMedio,cantElementosMedio,&tamanioBufferNodoMedio);
			bytesElementosMedio= NodoInterno.completarBuffer(bytesElementosMedio,&tamanioBufferNodoMedio);
			byte* bufferElementosMedio= BloqueUtils::concatena(bytesNivel, bytesElementosMedio,1,&tamanioBufferNodoMedio);
			archivo.agregarBloque(bufferElementosMedio,tamanioBufferNodoMedio);
			byte* bytesElementosDerecho= NodoInterno.obtenerByteArrayElementos(elementosDerecho,&tamanioBufferNodoDerecho);
			bytesElementosDerecho= NodoInterno.completarBuffer(bytesElementosDerecho,&tamanioBufferNodoDerecho);
			byte* bufferElementosDerecho= BloqueUtils::concatena(bytesNivel, bytesElementosDerecho,1,&tamanioBufferNodoDerecho);
			archivo.modificarBloque(bufferElementosDerecho, tamanioBufferNodoDerecho,nodoDerecho.getBloque());
			byte* bufferModificado= new byte[1];
			bufferModificado[0]= (byte)nodoPadre.getNivel();
			byte* bufferPadreNuevo=NodoInterno.obtenerByteArrayElementos(elementosPadreNuevo,cantElementosPadre,&tamanioBufferNodoPadre);
			bufferModificado= BloqueUtils::concatena(bufferModificado,bufferPadreNuevo,1,&tamanioBufferNodoPadre);
			tamanioBufferRetorno=&tamanioBufferNodoPadre;
			return bufferModificado;
		}
	}

	bool ArbolBSharp::estaLleno(Nodo nodoVecino, int cantidad,RegistroIndice registro[],int cantRegistros) {
		int nivel= nodoVecino.getNivel();
		if (nivel == 0){
			byte* bytes= ((NodoHoja)nodoVecino).getBuffer();
			int tamanioBytes=4;
			int i;
			for (i = 0; i < cantRegistros; i++) {
				Nodo nodoAux= new NodoHoja(bytes,nodoVecino.getBloque(),nodoVecino.getTamanioBuffer());
				bytes= ((NodoHoja)nodoAux).agregarRegistro(registro[i]);
				bytes= BloqueUtils::concatena(bytes, BloqueUtils::intToByteArray(0),nodoVecino.getTamanioBuffer(),&tamanioBytes);
			}
			return tamanioBytes > archivo.getTamanioBloque();
		}else{
			int cant= nodoVecino.getBuffer()[1];
			return (cant + cantidad > CLAVES_MAX);
		}
	}

	int ArbolBSharp::buscarVecinoDerecho(Nodo nodoPadre, Nodo nodoLeido) {
		byte* bufferNodoPadre= nodoPadre.getBuffer();
		int cantidadElementos= bufferNodoPadre[1];
		for (int i = 0; i < cantidadElementos; i++) {
			int desde= (i*TAMANO_ELEMENTO) + 2;
			int bloqueAux= BloqueUtils::byteArrayToInt(bufferNodoPadre, desde);
			if (bloqueAux == nodoLeido.getBloque()){
				return BloqueUtils::byteArrayToInt(bufferNodoPadre, desde + TAMANO_ELEMENTO);
			}
		}
		return 0;
	}

	int ArbolBSharp::buscarVecinoIzquierdo(Nodo nodoPadre, Nodo nodoLeido) {
		byte* bufferNodoPadre= nodoPadre.getBuffer();
		int cantidadElementos= bufferNodoPadre[1];
		for (int i = 1; i <= cantidadElementos; i++) {
			int desde= (i*TAMANO_ELEMENTO) + 2;
			int bloqueAux= BloqueUtils::byteArrayToInt(bufferNodoPadre, desde);
			if (bloqueAux == nodoLeido.getBloque()){
				return BloqueUtils::byteArrayToInt(bufferNodoPadre, desde - TAMANO_ELEMENTO);
			}
		}
		return 0;

	}


	Nodo ArbolBSharp::obtenerHojaDelTermino(string termino, int bloque){

		byte* buffer= archivo.leerBloque(new byte[archivo.getTamanioBloque()],archivo.getTamanioBloque(), bloque);

		int nivel= buffer[0];

		if (nivel == 0){
			return new NodoHoja(buffer,bloque,archivo.getTamanioBloque());
		}else{
			bloque= NodoInterno.obtenerBloque(buffer,termino);
			Nodo hoja= obtenerHojaDelTermino(termino,bloque);
			return hoja;
		}
	}



	void ArbolBSharp::crear(){
		byte* bloque= new byte[archivo.getTamanioBloque()-4];
		bloque[0]= 0; //nivel
		bloque[1]= 0; //cantidad elementos
		byte* proxHoja= BloqueUtils::intToByteArray(0);
		archivo.agregarBloque(BloqueUtils::concatena(bloque, proxHoja,archivo.getTamanioBloque()-4,4));
	}

	void ArbolBSharp::mostrarArbol(){

		int i;

		for (i = BLOQUE_RAIZ; i < archivo.getCantidadBloques(); i++) {

			byte* buffer= archivo.leerBloque(new byte[archivo.getTamanioBloque()], i);
			int nivel= buffer[0];
			if (nivel == 0){
				mostrar(new NodoHoja(buffer,i,archivo.getTamanioBloque()));
			}else{
				mostrar(new NodoInterno(buffer,i,nivel,archivo.getTamanioBloque()));
			}

		}

	}

	void ArbolBSharp::mostrar(Nodo nodo) {
		int nivel= nodo.getNivel();
		cout<<"bloque: "<<nodo.getBloque()<<endl;
		if (nivel == 0){
			int proxHoja= BloqueUtils::.byteArrayToInt(nodo.getBuffer(), archivo.getTamanioBloque()-4);
			RegistroIndice* registros= ((NodoHoja)nodo).obtenerRegistros();
			cout<<"nivel: "<<nivel<<endl;
			cout<<"registros: "<<endl;
			for (int i = 0; i < ((NodoHoja)nodo).getCantidadRegistros(); i++) {
				cout<<registros[i].getTermino()<< " | ";
			}
			cout<<endl;
			cout<<"\n Proxima Hoja: "<<proxHoja<<endl;
		}else{
			Elemento* elementos= ((NodoInterno)nodo).obtenerElementos();
			cout<<"nivel: "<<nivel<<endl;
			cout<<"claves: "<<endl;
			for (int i = 0; i < elementos.length; i++) {
				Elemento elemento= elementos[i];
				cout<<"HijoIzq: "<<elemento.getHijoIzq()<<" Clave: "<<elemento.getClave()<<endl;
				cout<<" HijoDer: "<<elemento.getHijoDer()<< " | ";
			}
			cout<<endl;
		}

	}
