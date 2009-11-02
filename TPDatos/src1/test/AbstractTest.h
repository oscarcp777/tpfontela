/*
 * AbstractTest.h
 *
 *  Created on: 01/11/2009
 *      Author: oscar
 */

#ifndef ABSTRACTTEST_H_
#define ABSTRACTTEST_H_
#include <iostream>
#include "../Object/Object.h"
#include "../utils/Define.h"
#include "../Modelo/Alumno.h"
#include "../Composite/Componente.h"
#include "../Factory/FabricaDeRecursosDeAlmacenamiento.h"
#include "../Almacenamiento/RecursoDeAlmacenamiento.h"
#include <vector>
#include "../utils/StringUtils.h"
using namespace std;
class AbstractTest {
protected:
  string ruta;
public:
	AbstractTest();
	virtual ~AbstractTest();
	virtual void ejecutarTest()=0;
	string getRuta();
	void setRuta(string ruta);
};

#endif /* ABSTRACTTEST_H_ */
