

#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
using namespace std;

int main24() {
	/**
	 * obtengo la instancia de la fabrica para que inicilize una sola vez el mapa de objetos
	 */
	FabricaDeRecursosDeAlmacenamiento* fabricaDeRecursos=FabricaDeRecursosDeAlmacenamiento::obtenerInstancia();

	/**
	 * le paso los parametros de los objetos con los los que quiero que me construya el recurso de almacenamiento
	 * que son constantes que las defini en el Define.h (me parecio que quedaba mejor que un enum)
	 */

	RecursoDeAlmacenamiento* recurso=
			fabricaDeRecursos->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_TEXTO);

	Alumno* alumno1 = new Alumno(31993745,"Santiago Donikian",85689,8,8,8);
	Alumno* alumno2 = new Alumno(31440400,"Richard Dubini",85440,6,6,7);
	Alumno* alumno3 = new Alumno(93850139,"Oscar Caceres",86534,8,7,4);

	recurso->cargarComponente(alumno1);
	recurso->cargarComponente(alumno2);
	recurso->cargarComponente(alumno3);

	recurso->escribirArchivo("/home/richy/","archivoTexto");
	cout << "Archivo guardado" << endl;


	recurso->leerArchivo("/home/richy/","archivoTexto");
	Alumno* alumno = new Alumno();
	recurso->busquedaSecuencial(alumno, "86534");

	std::cout<<std::endl;
	std::cout<<"nombre: "<<alumno->getNombre()<<std::endl;
	std::cout<<"padron: "<<alumno->getPadron()<<std::endl;
	/**
	 * el metodo toString lo implementan todos los que hereden de object entonces
	 * llamando el toString llama a todos los tostring de los objetos que componen el tostring asi veo si cargo bien
	 * la fabrica
	 */


	delete recurso;
	delete fabricaDeRecursos;
	return 0;
}