package modelo.pruebas;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTests {

	public static Test suite() {
		TestSuite suite = new TestSuite("Test for modelo.pruebas");
		//$JUnit-BEGIN$
		suite.addTestSuite(PruebaLaserman.class);
		suite.addTestSuite(PruebaIntegradorPooglinTeleportador.class);
		suite.addTestSuite(PruebaTaladrador.class);
		suite.addTestSuite(PruebaIntegradorPooglinConstructor.class);
		suite.addTestSuite(PruebaEquipoPooglins.class);
		suite.addTestSuite(PruebaintegradorPooglinLaserman.class);
		suite.addTestSuite(PruebaConstructor.class);
		suite.addTestSuite(PruebaIntegradorPooglinCongelado.class);
		suite.addTestSuite(PruebaPosicion.class);
		suite.addTestSuite(PruebaCaminante.class);
		suite.addTestSuite(PruebaIntegracionCaminanteConPooglin.class);
		suite.addTestSuite(PruebaCongelado.class);
		suite.addTestSuite(PruebaTeleportador.class);
		suite.addTestSuite(PruebaDireccion.class);
		//$JUnit-END$
		return suite;
	}

}
