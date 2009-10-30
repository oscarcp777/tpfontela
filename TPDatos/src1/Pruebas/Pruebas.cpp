/*
 * main.cpp
 *
 *  Created on: 29/10/2009
 *      Author: richy
 */
#include "Pruebas.h"
using namespace std;

Pruebas::Pruebas() {
}

void Pruebas::imprimirOrdenPruebas(){
	cout<<"1: Busqueda Secuencial Bloques Archivo"<<endl;
	cout<<"2: Busqueda Secuencial Bloques Buffer"<<endl;
	cout<<"3: Busqueda Secuencial Registros Archivo"<<endl;
	cout<<"4: Busqueda Secuencial Registros Buffer"<<endl;
	cout<<"5: Busqueda Secuencial Texto Archivo"<<endl;
	cout<<"6: Busqueda Secuencial Texto Buffer"<<endl;
	cout<<"7: Guardar Como Registro Archivo"<<endl;
	cout<<"8: Guardar Como Texo Archivo"<<endl;
	cout<<"9: Guardar En Bloques Archivo"<<endl;
}


int Pruebas::testBusquedaSecuencialBloquesArchivo(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		Alumno* alumno = new Alumno();

		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoBloques");

		std::list<Componente*> listaAlumnos;
		list<Componente*>::iterator iter;

		recurso->buscar(listaAlumnos,alumno,"Nombre=Garcia");
		iter = listaAlumnos.begin();

		std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
		while(iter != listaAlumnos.end()){
			alumno = (Alumno*) *iter;
			std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
			std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
			std::cout<<"padron: "<<alumno->getDni()<<std::endl;
			std::cout<<std::endl;
			iter++;
		}

		delete recurso;
		delete fabricaDeRecursos;
		return 0;
}
int Pruebas::testBusquedaSecuencialBloquesBuffer(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();
		Alumno* alumno = new Alumno();
		Alumno* alumno1 = new Alumno(31993745,"Santy",85689,8,8,8);
		Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
		Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,120,"padron",alumno);


		recurso->alta(alumno1);
		recurso->alta(alumno2);
		recurso->alta(alumno3);

		cout << endl;
		cout << "Buffer guardado" << endl;

		std::list<Componente*> listaAlumnos;
		list<Componente*>::iterator iter;

		recurso->buscar(listaAlumnos,alumno,"Padron=85440");
		iter = listaAlumnos.begin();

		std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
		while(iter != listaAlumnos.end()){
			alumno = (Alumno*) *iter;
			std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
			std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
			std::cout<<"padron: "<<alumno->getDni()<<std::endl;
			iter++;
		}

		delete recurso;
		delete fabricaDeRecursos;
		return 0;


}
int Pruebas::testBusquedaSecuencialRegistrosArchivo(){
	/**
		 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
		 */
		FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */
		Alumno* alumno = new Alumno();

		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoRegistros");


		std::list<Componente*> listaAlumnos;
		list<Componente*>::iterator iter;

		recurso->buscar(listaAlumnos,alumno,"Nombre=Perez");
						iter = listaAlumnos.begin();

		std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
		while(iter != listaAlumnos.end()){
			alumno = (Alumno*) *iter;
			std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
			std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
			std::cout<<"padron: "<<alumno->getDni()<<std::endl;
			std::cout<<std::endl;
			iter++;
		}

		delete recurso;
		delete fabricaDeRecursos;
		return 0;

}
int Pruebas::testBusquedaSecuencialRegistrosBuffer(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();
	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_REGISTROS,40,"padron",alumno);



	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);

	cout << endl;
	cout << "Buffer guardado" << endl;

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"Padron=85440");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
		std::cout<<"padron: "<<alumno->getDni()<<std::endl;
		iter++;
	}

	delete recurso;
	delete fabricaDeRecursos;
	return 0;

}
int Pruebas::testBusquedaSecuencialTextoArchivo(){
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->abrirRecursoDeAlmacenamientoEnArchivo("../TP0Datos/files/","archivoTexto");

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;

	recurso->buscar(listaAlumnos,alumno,"Nombre=Perez");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
		std::cout<<"padron: "<<alumno->getDni()<<std::endl;
		std::cout<<std::endl;
		iter++;
	}

	delete recurso;
	delete fabricaDeRecursos;
	return 0;
}
int Pruebas::testBusquedaSecuencialTextoBuffer(){
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();
	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_TEXTO,40,"padron",alumno);

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;


	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);

	//recurso->alta("../files/","archivoTexto");
	cout<<endl << "guardado en Buffer" << endl;

	recurso->buscar(listaAlumnos,alumno,"Padron=85440");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"dni: "<<alumno->getPadron()<<std::endl;
		std::cout<<"padron: "<<alumno->getDni()<<std::endl;
		iter++;
	}


	delete recurso;
	delete fabricaDeRecursos;
	return 0;
}
int Pruebas::testGuardarComoRegistroArchivo(){
	/**
		 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
		 */
		FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */

		Alumno* alumno = new Alumno();
		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_REGISTROS,40,
						"../TP0Datos/files/","archivoRegistros","padron",INDEXADO_BSHARP,alumno);

		Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
		Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
		Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
		Alumno* alumno4 = new Alumno(93850169,"Perez",80000,8,7,4);
		Alumno* alumno5 = new Alumno(93853439,"Daniel Sivori",86524,8,7,4);
		Alumno* alumno6 = new Alumno(93850130,"Perez",84029,8,7,4);
		Alumno* alumno7 = new Alumno(31850139,"Garcia",86531,8,7,4);
		Alumno* alumno8 = new Alumno(44850139,"Oscar Rigeri",86934,8,7,4);
		Alumno* alumno9 = new Alumno(10850139,"Garcia",86745,8,7,4);
		Alumno* alumno10 = new Alumno(23850139,"Diego Maradroga",87890,8,7,4);


		recurso->alta(alumno1);
		recurso->alta(alumno2);
		recurso->alta(alumno3);
		recurso->alta(alumno4);
		recurso->alta(alumno5);
		recurso->alta(alumno6);
		recurso->alta(alumno7);
		recurso->alta(alumno8);
		recurso->alta(alumno9);
		recurso->alta(alumno10);

		cout << endl;
		cout << "Archivo guardado" << endl;

		delete recurso;
		delete fabricaDeRecursos;
		return 0;
}
int Pruebas::testGuardarComoTexoArchivo(){
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_TEXTO,50,
					"../TP0Datos/files/","archivoTexto","padron",INDEXADO_BSHARP,alumno);


	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
	Alumno* alumno4 = new Alumno(93850169,"Perez",80000,8,7,4);
	Alumno* alumno5 = new Alumno(93853439,"Daniel Sivori",86524,8,7,4);
	Alumno* alumno6 = new Alumno(93850130,"Perez",84029,8,7,4);
	Alumno* alumno7 = new Alumno(31850139,"Garcia",86531,8,7,4);
	Alumno* alumno8 = new Alumno(44850139,"Oscar Rigeri",86934,8,7,4);
	Alumno* alumno9 = new Alumno(10850139,"Garcia",86745,8,7,4);
	Alumno* alumno10 = new Alumno(23850139,"Diego Maradroga",87890,8,7,4);


	recurso->alta(alumno1);
	recurso->alta(alumno2);
	recurso->alta(alumno3);
	recurso->alta(alumno4);
	recurso->alta(alumno5);
	recurso->alta(alumno6);
	recurso->alta(alumno7);
	recurso->alta(alumno8);
	recurso->alta(alumno9);
	recurso->alta(alumno10);


	cout<<endl << "Archivo guardado" << endl;

	delete recurso;
	delete fabricaDeRecursos;
	return 0;

}
int Pruebas::testGuardarEnBloquesArchivo(){
	/**
		 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
		 */
		FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

		/**
		 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
		 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
		 */
		Alumno* alumno = new Alumno();
		RecursoDeAlmacenamiento* recurso=
				fabricaDeRecursos->crearRecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_BLOQUES,120,
										"../TP0Datos/files/","archivoBloques","padron",INDEXADO_BSHARP,alumno);

		Alumno* alumno1 = new Alumno(31993745,"Santy",85689,8,8,8);
		Alumno* alumno2 = new Alumno(31440400,"Dubini",85440,6,6,7);
		Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);
		Alumno* alumno4 = new Alumno(93850169,"Rodrigo Perez",80000,8,7,4);
		Alumno* alumno5 = new Alumno(93853439,"Daniel Sivori",86524,8,7,4);
		Alumno* alumno6 = new Alumno(93850139,"Perez",84029,8,7,4);
		Alumno* alumno7 = new Alumno(31850139,"Garcia",86531,8,7,4);
		Alumno* alumno8 = new Alumno(44850139,"Oscar Rigeri",86934,8,7,4);
		Alumno* alumno9 = new Alumno(10850139,"Garcia",86745,8,7,4);
		Alumno* alumno10 = new Alumno(2385013,"Don",87890,8,7,4);


		recurso->alta(alumno1);
		recurso->alta(alumno2);
		recurso->alta(alumno3);
		recurso->alta(alumno4);
		recurso->alta(alumno5);
		recurso->alta(alumno6);
		recurso->alta(alumno7);
		recurso->alta(alumno8);
		recurso->alta(alumno9);
		recurso->alta(alumno10);
		cout<<std::endl<< "Archivo guardado" << endl;

		/**
		 * el metodo toString lo implementan todos los que hereden de object entonces
		 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
		 * la fabrica
		 */

		delete alumno1;
		delete alumno2;
		delete alumno3;
		delete alumno4;
		delete alumno5;
		delete alumno6;
		delete alumno7;
		delete alumno8;
		delete alumno9;
		delete alumno10;
		delete recurso;
		delete fabricaDeRecursos;
		return 0;
}
void Pruebas::seleccionarTest(int numPrueba){

	switch(numPrueba){

	case 1:
			this->testBusquedaSecuencialBloquesArchivo();
			break;

	case 2:
			this->testBusquedaSecuencialBloquesBuffer();
			break;

	case 3:
			this->testBusquedaSecuencialRegistrosArchivo();
			break;

	case 4:
			this->testBusquedaSecuencialRegistrosBuffer();
			break;

	case 5:
			this->testBusquedaSecuencialTextoArchivo();
			break;

	case 6:
			this->testBusquedaSecuencialTextoBuffer();
			break;

	case 7:
			this->testGuardarComoRegistroArchivo();
			break;

	case 8:
			this->testGuardarComoTexoArchivo();
			break;
	case 9:
			this->testGuardarEnBloquesArchivo();
			break;

	default :
			cout<<"NUMERO DE PRUEBA INVALIDO"<<endl;


	}


}