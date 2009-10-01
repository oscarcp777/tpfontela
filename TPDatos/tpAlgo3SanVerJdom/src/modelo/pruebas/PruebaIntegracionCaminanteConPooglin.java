/**
 * 
 */
package modelo.pruebas;


import java.util.LinkedList;

import modelo.pooglins.*;
import modelo.constantes.Constantes;
import modelo.control.CantidadDeOficios;
import modelo.control.Nivel;
import modelo.control.ControlDeJuego;
import modelo.entornoDeJuego.*;

import junit.framework.TestCase;

public class PruebaIntegracionCaminanteConPooglin extends TestCase {
	/**
	 * En este Test proamos que el Oficio Caminante se comporte en forma correcta
	 * dentero del Objeto Pooglins
	 */
	
	private int[][] terrenoDePrueba = 
	   //0 1 2 3 4 5 6 7 8 9
	   {{9,9,9,9,9,9,9,9,9,9},//0
		{9,3,3,3,3,3,3,3,3,9},//1
		{9,3,3,3,0,3,3,3,3,9},//2
		{9,3,0,1,3,6,6,0,3,9},//3
		{9,3,3,3,3,3,3,3,3,9},//4
		{9,9,9,9,9,9,9,9,9,9}};//5
	private Pooglins pooglin;
	private ControlDeJuego controlJuego;
	private Mapa mapaOtro;
	private Oficio oficio;
	Posicion posicion;

	// TIRA NullPointerException!
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
	/*
	 * En este Test Probamos que el Pooglins con oficio Caminante camine en forma correcta hacia la derecha.
	 */
	public void testMoverHaciaAdelante() {
		/*Seteo al oficio en la posicion (2,3) de la matriz situada arriba.
		 *Con direccion hacia la derecha.  
		 * */
		posicion = new Posicion(2,3);
		pooglin = new Pooglins(1, posicion, mapaOtro.getTerreno());
		//oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
		pooglin.setOficio(Constantes.CAMINANTE);
		assertNotNull(mapaOtro.getTerreno());
		pooglin.mover();
		assertEquals(new Posicion(3,3), posicion);
	}
	/*
	 * En este Test Probamos que el Pooglins con oficio Caminante revote al llegar a una pared.
	 * Lo importante es que no llegue a la posicion de la pared.
	 */
	public void testRevotar() {
		posicion = new Posicion(7,3);
		pooglin = new Pooglins(1, posicion, mapaOtro.getTerreno());
/*		oficio = new Caminante(new Direccion(1,0),new HabilidadNula());*/
		pooglin.setOficio(Constantes.CAMINANTE);
		pooglin.mover();
		assertEquals(new Posicion(7,3), posicion);
	}
	
	/*
	 * En este Test Probamos que el Pooglins con oficio Caminante suba una pendiente.
	 */
	public void testSubir() {
		posicion = new Posicion(3,3);
		pooglin = new Pooglins(1, posicion, mapaOtro.getTerreno());
		//oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
		pooglin.setOficio(Constantes.CAMINANTE);
		pooglin.mover();
		assertEquals(new Posicion(4,2), posicion);
	}
	
	/*
	 * En este Test Probamos que el Oficio Caminante duplique su velocidad al caminar en el Hielo.
	 */
	public void testCaminarEnHielo() {
		posicion = new Posicion(5,3);
		pooglin = new Pooglins(1, posicion, mapaOtro.getTerreno());
		//oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
		pooglin.setOficio(Constantes.CAMINANTE);
		pooglin.mover();
		assertEquals(new Posicion(7,3), posicion);
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
