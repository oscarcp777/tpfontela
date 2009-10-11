/*
 * Almacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */

#ifndef ALMACENAMIENTO_H_
#define ALMACENAMIENTO_H_



#include "../Composite/Compuesto.h"
#include "../Composite/Componente.h"
#include "../Object/Object.h"
#include <fstream>
class Almacenamiento:public Object{
protected:
	std::fstream  archivo;  // referencia al archivo
private:
	Compuesto* compuesto;
	std::string nombreArchivo;
	std::string ruta;

public:
	Almacenamiento(Compuesto* comp);
	virtual ~Almacenamiento();
    Compuesto *getCompuesto();
    std::string toString();
    void setCompuesto(Compuesto *compuesto);
    void agregarComponente(Componente* componente);
    std::string getNombreArchivo();
    std::string getRuta();
    std::string getPath();
    void setNombreArchivo(std::string nombreArchivo);
    void setRuta(std::string ruta);
    virtual void guardar(std::string contenido,std::string tipoArchivo);

};

#endif /* ALMACENAMIENTO_H_ */
