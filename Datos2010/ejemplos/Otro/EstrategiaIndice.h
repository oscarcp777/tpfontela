
#ifndef ESTRATEGIAINDICE_H
#define ESTRATEGIAINDICE_H

#include <string>
#include "Clave.h"
#include "ComparadorClave.h"

/**
  * class EstrategiaIndice
  *
  */

/******************************* Abstract Class ****************************
EstrategiaIndice does not have any pure virtual methods, but its author
  defined it as an abstract class, so you should not use it directly.
  Inherit from it instead and create only objects from the derived classes
*****************************************************************************/
class EstrategiaIndice{
public:
	virtual void crear(std::string nombreArch,unsigned int tamanioBloque,Clave* clave,ComparadorClave* comp)=0;
	virtual bool abrir(std::string nombreArch,ComparadorClave* comp)=0;
	virtual bool BuscarReferencia(const Clave* clave,Referencia* referencia)=0;
	virtual bool insertar(Referencia ref,Clave* clave)=0;
        virtual bool eliminar(const Clave* clave)=0;
	virtual bool modificar(const Clave* clave,Referencia refNueva)=0;
	virtual void mostrarEstado() = 0;
	virtual int tamanioBloque() = 0;
	virtual void cerrar() = 0;
};
#endif // ESTRATEGIAINDICE_H
