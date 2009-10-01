package controlador.pruebas;

import junit.framework.Test;
import junit.framework.TestSuite;

public class AllTest {
	public static Test suite() {
		
		TestSuite suite = new TestSuite("Test for controlador.pruebas");
		suite.addTestSuite(PruebaMarcoPooglin.class);
		return suite;
		
	}
}
