/*
 * Test.cpp
 *
 *  Created on: 28/03/2010
 *      Author: nelson
 */

#include "TestIOFile.h"
#include "TestFreeBlockController.h"
#include "TestBTree.h"
#include "TestLogger.h"
#include "TestHash.h"
#include "../src.datos.utils/Define.h"

int main(){

	TestIOFile* testIOFile = new TestIOFile();
	TestFreeBlockController* testFreeBlockController = new TestFreeBlockController();
	TestBTree* testBTree = new TestBTree();
	TestLogger* testLogger = new TestLogger();
	TestHash* testHash = new TestHash();

//	testIOFile->runBinaryFileTest2();
//	testIOFile->runTextFileTest();
//	testFreeBlockController->runGeneralTest();
//	testFreeBlockController->runAddTest();
//	testFreeBlockController->runPrintTest(cout);
//	testFreeBlockController->runGetTest();

/*
 * Les comento que me genere un archivo de datos, basado en el
 * medodo runTestInsertWithRamdom que como su nombre lo indica esta hecho mediante
 * ramdon.
 * El archivo es input.
 */
	testBTree->runTestInsert("files/newTest.dat", 128);
//	testBTree->runTestInsertWithRandom("files/newDate.dat", 128);
//	testBTree->runTestSecuenceSet("files/testbt.dat",128);
/*
 * Probe creando un archivo inputdelete donde se encuentran los datos a eliminar
 * y al parecer anda bien, lo que pasa es que cuesta seguir el camino de la
 * eliminacion ya que el volumen de datos es muy grande.
 * Probe tambien en eliminar todas las claves, no se pincho pero en la salida
 * la cantidad de bloques libres no me dio lo que esperaba ... tenia que darme un numero
 * inmenso sin embargo de dio un numero bajo tipo 60.
 */
	testBTree->runTestRemove("files/newTest.dat",128);
//	testLogger->runTestLogger();

//*************TESTs HASH*******************
//	testHash->runCreateAndInsertTest();
//	testHash->runRemoveTest();
//	testHash->runSearchTest();
//	testHash->runUpdateTest();
//	testHash->runPrintTest();
//	testHash->runExampleCatedraTest();
//*************FIN TESTs HASH*******************

	delete testLogger;
	delete testIOFile;
	delete testFreeBlockController;
	delete testBTree;
	delete testHash;


	return 0;
}
