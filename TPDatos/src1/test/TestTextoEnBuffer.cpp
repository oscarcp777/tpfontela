/*
 * TestTextoEnBuffer.cpp
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#include "TestTextoEnBuffer.h"

TestTextoEnBuffer::TestTextoEnBuffer() {
	// TODO Auto-generated constructor stub

}

TestTextoEnBuffer::~TestTextoEnBuffer() {
	// TODO Auto-generated destructor stub
}
void TestTextoEnBuffer::ejecutarTest(){
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */
	Alumno* alumno = new Alumno();
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
	Alumno* alumno11 = new Alumno(2385011,"TOPO MAN",87230);

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->crearRecursoDeAlmacenamientoEnBuffer(ESTRATEGIA_ALMACENAMIENTO_TEXTO,40,"Padron",alumno);

	std::list<Componente*> listaAlumnos;
	list<Componente*>::iterator iter;


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

	cout<<endl << "guardado en Buffer" << endl;

	recurso->buscar(listaAlumnos,alumno,"Padron=87230");
	iter = listaAlumnos.begin();

	std::cout<<"Cantidad alumnos Encontrados: "<<listaAlumnos.size()<<std::endl;
	while(iter != listaAlumnos.end()){
		alumno = (Alumno*) *iter;
		std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
		std::cout<<"padron: "<<alumno->getPadron()<<std::endl;
		std::cout<<"dni: "<<alumno->getDni()<<std::endl;
		iter++;
	}
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
