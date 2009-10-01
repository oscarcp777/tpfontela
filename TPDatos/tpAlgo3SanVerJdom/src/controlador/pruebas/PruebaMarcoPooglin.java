package controlador.pruebas;

import modelo.pooglins.Posicion;
import controlador.MarcoPosicion;
import junit.framework.TestCase;

public class PruebaMarcoPooglin extends TestCase {

	protected void setUp() throws Exception {
		
	}
	
	public void testEstaDentro(){
		MarcoPosicion marco = new MarcoPosicion(new Posicion(1,61));
		assertEquals(true, marco.estaDentro(new Posicion(4,40)));
		assertEquals(false, marco.estaDentro(new Posicion(1,67)));
		assertEquals(true, marco.estaDentro(new Posicion(1,61)));
	}
}
