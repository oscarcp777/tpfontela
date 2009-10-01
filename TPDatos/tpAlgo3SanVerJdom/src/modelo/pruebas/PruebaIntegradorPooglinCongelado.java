/**
 * 
 */
package modelo.pruebas;

import java.util.LinkedList;

import modelo.constantes.Constantes;
import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.*;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaIntegradorPooglinCongelado extends TestCase {
	private int[][] terrenoDePrueba =
	   //0 1 2 3 4 5 6 7 8 9
	   {{9,9,9,9,9,9,9,9,9,9},//0
		{9,3,3,3,3,3,3,3,3,9},//1
		{9,3,3,3,3,3,3,3,3,9},//2
		{9,14,0,0,0,0,0,0,0,9},//3
		{9,3,3,3,3,3,3,3,3,9},//4
		{9,9,9,9,9,9,9,9,9,9}};//5
	
	
	private ControlDeJuego controlJuego;
	private Mapa mapaOtro;
	
	/*
	*
	* Este test prueba la interaccion entre un caminante y un pooglin congelado
	*
	*/
	
	protected void setUp() throws Exception {
		super.setUp();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		controlJuego = new ControlDeJuego();
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		mapaOtro = new Mapa(atributos);

	}

	
	private void mover(){
		while (mapaOtro.hayPooglins()) {
			mapaOtro.correrRondaMovimientosPooglin();
		}
		
	}
	
	public void testCongelar() {
		
		
		mapaOtro.agregarPooglin(new Posicion(2, 3));
		mapaOtro.agregarPooglin(new Posicion(7, 3));
		mapaOtro.setearOficioAPooglin(1, Constantes.CAMINANTE);
		mapaOtro.setearOficioAPooglin(2, Constantes.CONGELADO);
		
		
		this.mover();
		
		
		assertEquals(1, mapaOtro.getCantidadGanadores());
		
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