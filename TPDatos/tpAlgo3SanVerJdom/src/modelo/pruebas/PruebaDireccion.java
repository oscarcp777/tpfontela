/**
 * 
 */
package modelo.pruebas;

import modelo.movimientos.Direccion;
import junit.framework.TestCase;

public class PruebaDireccion extends TestCase {

private Direccion miDireccionAbajo;	
private Direccion miDireccionDerecha;

	/**
	 * @param name
	 */
	public PruebaDireccion(String name) {
		super(name);
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#setUp()
	 */
	protected void setUp() throws Exception {
		super.setUp();
		miDireccionAbajo=new Direccion();
		miDireccionDerecha=new Direccion();
		miDireccionAbajo.setAbajo();
		miDireccionDerecha.setDerecha();					
	
	}
		
	public void testSetAbajo(){	
		
	Direccion miDireccion = new Direccion(-1,0);
		miDireccion.setAbajo();
		assertEquals(0,miDireccion.getDireccionX());
		assertEquals(1,miDireccion.getDireccionY());			
	}
	
	public void testSetDerecha(){
		Direccion miDireccion = new Direccion(-1,0);
		miDireccion.setDerecha();
		assertEquals(1,miDireccion.getDireccionX());
		assertEquals(0,miDireccion.getDireccionY());			
	}

	
	/*
	 * 
	 * */
	public void testInvertir(){	
		Direccion miDireccionAbajo = new Direccion(0,1);
		
		miDireccionAbajo.invertir();
		assertEquals(0,miDireccionAbajo.getDireccionX());
		assertEquals(-1,miDireccionAbajo.getDireccionY());
		
		Direccion miDireccionDerecha = new Direccion(1,0);
		miDireccionDerecha.invertir();
		assertEquals(-1,miDireccionDerecha.getDireccionX());
		assertEquals(0,miDireccionDerecha.getDireccionY());		
	}
	
	public void testSubirDireccion(){
		
		Direccion miDireccionAbajo = new Direccion(1,1);
		miDireccionAbajo.subirDireccion();
		assertEquals(1,miDireccionAbajo.getDireccionX());
		assertEquals(0,miDireccionAbajo.getDireccionY());

		miDireccionDerecha.subirDireccion();
		assertEquals(1,miDireccionDerecha.getDireccionX());
		assertEquals(-1,miDireccionDerecha.getDireccionY());		
		
		miDireccionDerecha.subirDireccion();
		assertEquals(1,miDireccionDerecha.getDireccionX());
		assertEquals(-1,miDireccionDerecha.getDireccionY());
	}
	
	public void testBajarDireccion(){
		Direccion miDireccionArriba = new Direccion(1,-1);
		
		miDireccionArriba.bajarDireccion();
		assertEquals(1,miDireccionArriba.getDireccionX());
		assertEquals(0,miDireccionArriba.getDireccionY());

		miDireccionArriba.bajarDireccion();
		assertEquals(1,miDireccionArriba.getDireccionX());
		assertEquals(1,miDireccionArriba.getDireccionY());		
		
		miDireccionArriba.bajarDireccion();
		assertEquals(1,miDireccionArriba.getDireccionX());
		assertEquals(1,miDireccionArriba.getDireccionY());	
	}
	
	public void testSetHorizontal(){
		Direccion miDireccionAbajo = new Direccion(1,1);
		miDireccionAbajo.setHorizontal();
		assertEquals(0,miDireccionAbajo.getDireccionY());
		assertEquals(1,miDireccionAbajo.getDireccionX());

		miDireccionAbajo = new Direccion(1,-1);
		miDireccionAbajo.setHorizontal();
		assertEquals(0,miDireccionAbajo.getDireccionY());
		assertEquals(1,miDireccionAbajo.getDireccionX());		
	}
	
	

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#tearDown()
	 */
	protected void tearDown() throws Exception {
		super.tearDown();
		miDireccionAbajo=null;
		miDireccionDerecha=null;
		
	}
	

}
