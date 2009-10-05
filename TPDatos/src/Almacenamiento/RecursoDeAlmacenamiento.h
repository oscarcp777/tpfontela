/*
 * RecursosAlmacenamiento.h
 *
 *  Created on: 19/09/2009
 *      Author: richy
 */
#include "Almacenamiento.h"
#include "../Estrategy/EstrategiaRecurso.h"
#include "../Estrategy/EstrategiaAlmacenamiento.h"
#include "../Estrategy/EstrategiaIndice.h"
#include "../Composite/Componente.h"

#ifndef RECURSOSALMACENAMIENTO_H_
#define RECURSOSALMACENAMIENTO_H_

class RecursoDeAlmacenamiento :public Object{
public:
	std::string toString();
	RecursoDeAlmacenamiento();
	RecursoDeAlmacenamiento(Componente* componente, EstrategiaRecurso* eRecurso, EstrategiaAlmacenamiento* eAlmacenamiento, Almacenamiento* almacenamiento );
	virtual ~RecursoDeAlmacenamiento();
    Almacenamiento *getAlmacenamiento()
    {
        return almacenamiento;
    }

    EstrategiaAlmacenamiento *getEstrategiaAlmacenamiento()
    {
        return estrategiaAlmacenamiento;
    }

    EstrategiaIndice *getEstrategiaIndice()
    {
        return estrategiaIndice;
    }

    EstrategiaRecurso *getEstrategiaRecurso()
    {
        return estrategiaRecurso;
    }

    void setAlmacenamiento(Almacenamiento *almacenamiento)
    {
        this->almacenamiento = almacenamiento;
    }

    void setEstrategiaAlmacenamiento(EstrategiaAlmacenamiento *estrategiaAlmacenamiento)
    {
        this->estrategiaAlmacenamiento = estrategiaAlmacenamiento;
    }

    void setEstrategiaIndice(EstrategiaIndice *estrategiaIndice)
    {
        this->estrategiaIndice = estrategiaIndice;
    }

    void setEstrategiaRecurso(EstrategiaRecurso *estrategiaRecurso)
    {
        this->estrategiaRecurso = estrategiaRecurso;
    }

private:
	Almacenamiento* almacenamiento;
	EstrategiaAlmacenamiento* estrategiaAlmacenamiento;
	EstrategiaRecurso* estrategiaRecurso;
	EstrategiaIndice* estrategiaIndice;


};

#endif /* RECURSOSALMACENAMIENTO_H_ */
