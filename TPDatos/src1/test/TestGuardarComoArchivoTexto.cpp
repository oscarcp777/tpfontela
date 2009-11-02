/*
 * TestGuardarComoArchivoTexto.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestGuardarComoArchivoTexto.h"

TestGuardarComoArchivoTexto::TestGuardarComoArchivoTexto() {
	// TODO Auto-generated constructor stub

}

TestGuardarComoArchivoTexto::~TestGuardarComoArchivoTexto() {
	// TODO Auto-generated destructor stub
}
void TestGuardarComoArchivoTexto::ejecutarTest(){
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
					this->getRuta(),"archivoTexto","Padron",INDEXADO_BSHARP,alumno);


	Alumno* alumno1 = new Alumno(31993745,"Santy Donikian",85689);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534);
	Alumno* alumno4 = new Alumno(93850169,"Perez",80000);
	Alumno* alumno5 = new Alumno(93853439,"Daniel Sivori",86524);
	Alumno* alumno6 = new Alumno(93850130,"Perez",84029);
	Alumno* alumno7 = new Alumno(31850139,"Garcia",86531);
	Alumno* alumno8 = new Alumno(44850139,"Oscar Rigeri",86934);
	Alumno* alumno9 = new Alumno(10850139,"Garcia",86745);
	Alumno* alumno10 = new Alumno(23850139,"Diego Maradroga",87890);
	Alumno* alumno11 = new Alumno(23850139,"Maja",87890);



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
	recurso->baja(alumno1);
	recurso->alta(alumno11);

	cout<<endl << "Archivo guardado" << endl;
	recurso->cerrar();
	delete alumno;
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

}
