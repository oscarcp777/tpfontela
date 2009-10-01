/**
 * 
 */
package modelo.pruebas;

import modelo.movimientos.Direccion;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaPosicion extends TestCase {	
		private Posicion posicion;
		
	        // TIRA NullPointerException!
			protected void setUp() throws Exception {
				super.setUp();
				posicion = new Posicion(3,3);										
			}
			/*
			 * En este Test Probamos que el objeto Direccion realice el metodo
			 * mover correctamente.
			 */
			public void testMoverHaciaDerecha() {
				/*Le pido a la posicion que me mueva hacia la derecha.  
				 * */
				posicion.moverEnDireccion(new Direccion(1,0));
				assertEquals(new Posicion(4,3), posicion);
			}
			/*
			 * En este Test Probamos que el objeto Direccion realice el metodo
			 * mover correctamente.
			 */
			public void testMoverEnDiagonal() {
				/*Le pido a la posicion que me mueva hacia la Izquierda.  
				 * */
				posicion.moverEnDireccion(new Direccion(1,1));
				assertEquals(new Posicion(4,4), posicion);
			}
			/*
4			 * En este Test Probamos que el objeto Direccion realice el metodo
			 * mover correctamente.
			 */
			public void testMoverIPosiciones() {
				/*Le pido a la posicion que me mueva hacia la derecha i casilleros.  
				 * */
				int i = 5;
				posicion.moverEnDireccion(new Direccion(1,0), i);
				assertEquals(new Posicion(8,3), posicion);
			}
			
			/*
			 * En este Test Probamos que el objeto Direccion se copie correctamente.
			 */
			public void testCopiarPosiciones() {
				Posicion posicionCopia = posicion.copiar();
				assertEquals(posicionCopia, posicion);
			}
	
			/*
			 * (non-Javadoc)
			 * 
			 * @see junit.framework.TestCase#tearDown()
			 */
			protected void tearDown() throws Exception {
				super.tearDown();

			}
}
