package controlador.pruebas;

import junit.framework.TestCase;

import modelo.pooglins.Posicion;
import controlador.PooglinsEnJuego;

public class PruebaPooglinsEnJuego extends TestCase{

	private PooglinsEnJuego pooglins ;
	
	protected void setUp() throws Exception {
	pooglins = new PooglinsEnJuego();
	pooglins.crearPooglinPosicion(1, new Posicion(30,30));
	pooglins.crearPooglinPosicion(2, new Posicion(61,61));
	}
	
	
	public void testModificarPosicionPooglin(){
	pooglins.modificarPosicionPooglin(1, new Posicion(31,31));
	assertEquals(new Posicion(31,31), pooglins.getPooglinPorId(1).getPosicion());
	assertEquals(new Posicion(61,61), pooglins.getPooglinPorId(2).getPosicion());
	pooglins.modificarPosicionPooglin(1, new Posicion(30,30));
	}
	public void testGetPooglinCliqueado(){
		assertEquals(1, pooglins.getPooglinCliqueado(new Posicion(35,28)));
		assertEquals(2, pooglins.getPooglinCliqueado(new Posicion(69,32)));
		assertEquals(0, pooglins.getPooglinCliqueado(new Posicion(0,0)));
	}
}
