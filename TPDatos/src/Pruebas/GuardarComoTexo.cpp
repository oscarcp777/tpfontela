/*
 * GuardarComoTexo.cpp
 *
 *  Created on: 06/10/2009
 *      Author: Programadores
 */

#include "../Modelo/Alumno.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
#include "../utils/Define.h"

int main(int argc, char *argv[])
{
	Alumno* alumno = new Alumno(31993745,"Santiago",85689);
	FabricaDeRecursosDeAlmacenamiento* fabrica;
	fabrica->obtenerInstancia();
	RecursoDeAlmacenamiento* rDeAlm = fabrica->RecursoDeAlmacenamientoEnArchivo(ESTRATEGIA_ALMACENAMIENTO_TEXTO,ARCHIVO,alumno);

}


