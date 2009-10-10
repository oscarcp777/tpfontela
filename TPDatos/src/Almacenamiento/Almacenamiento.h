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
class Almacenamiento:public Object{
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

    void setNombreArchivo(std::string nombreArchivo);
    void setRuta(std::string ruta);

};

#endif /* ALMACENAMIENTO_H_ */
