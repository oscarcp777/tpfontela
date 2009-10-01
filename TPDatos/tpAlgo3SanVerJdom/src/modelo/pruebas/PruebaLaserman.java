/**
 * 
 */
package modelo.pruebas;

import java.util.LinkedList;

import modelo.movimientos.Direccion;
import modelo.pooglins.*;
import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.*;


import junit.framework.TestCase;

public class PruebaLaserman extends TestCase {

	private int[][] terrenoDePrueba = 
	   //0 1 2 3 4 5 6 7 8 9 0 1
	   {{9,9,9,9,9,9,9,9,9,9,9,9},//0
		{9,4,4,4,4,0,0,0,0,0,4,9},//1
		{9,4,4,4,4,3,3,3,3,3,4,9},//2
		{9,0,3,3,0,3,3,3,3,9,0,9},//3
		{9,9,9,9,9,9,9,9,9,9,9,9}};//4
		
		private ControlDeJuego controlJuego;
		private Mapa mapaOtro;
		private Oficio oficio;
		Posicion posicion;

		// TIRA NullPointerException!
		protected void setUp() throws Exception {
			super.setUp();
			controlJuego = new ControlDeJuego();
			CantidadDeOficios oficio = new CantidadDeOficios(3,0);
			LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
			cantidadDeOficios.add(oficio);
			Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
			atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
			mapaOtro = new Mapa(atributos);
			
					
		}
		/*
		 * AGREGAR
		 */
		public void testDemolerHastaEncontrarPiso() {
			posicion = new Posicion(1,3);
			oficio = new Laserman(new Direccion(1,0),new HabilidadNula());
			for (int i = 0; i < 4; i++) {
				oficio.mover(mapaOtro.getTerreno(), posicion);	
			}
			assertEquals(new Posicion(3,3), posicion);
			assertEquals(true, oficio.estaFinalizado());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(2,3)).esPiso());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(3,3)).esPiso());
		}
		
		public void testDemolerHastaEncontrarPiedra() {
			posicion = new Posicion(4,3);
			oficio = new Laserman(new Direccion(1,0),new HabilidadNula());
			for (int i = 0; i < 5; i++) {
				oficio.mover(mapaOtro.getTerreno(), posicion);	
			}
			assertEquals(new Posicion(8,3), posicion);
			assertEquals(true, oficio.estaFinalizado());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(4,3)).esPiso());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(5,3)).esPiso());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,3)).esPiso());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(7,3)).esPiso());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(8,3)).esPiso());
			assertEquals(false, mapaOtro.getTerreno().getElementoTerreno(new Posicion(9,3)).esRompible());
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
