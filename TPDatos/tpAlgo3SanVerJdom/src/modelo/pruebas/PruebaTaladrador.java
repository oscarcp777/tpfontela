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
import modelo.movimientos.Direccion;
import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import modelo.pooglins.Taladrador;
import junit.framework.TestCase;

public class PruebaTaladrador extends TestCase {
	private int[][] terrenoDePrueba = 
		   
		   //0 1 2 3 4 5 6 7 8 9
		   {{9,9,9,9,9,9,9,9,9,9},//0
			{9,4,4,4,4,4,4,4,4,9},//1
			{9,4,0,0,0,0,0,0,0,9},//2
			{9,4,3,3,3,3,3,3,3,9},//3
			{9,0,3,3,3,3,3,3,3,9},//4
			{9,3,3,3,3,3,3,3,3,9},//5
			{9,3,8,3,3,3,3,3,3,9},//6
			{9,3,3,3,3,3,3,3,3,9},//7
			{9,3,3,3,3,3,3,3,3,9},//8
			{9,0,0,0,0,0,0,0,0,9},//9
			{9,9,9,9,9,9,9,9,9,9}};//10
			
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
			 * En este Test Probamos que el Oficio Taladrador se mueva en forma correcta hacia la abajo.
			 */
			public void testRealizarUnMovimiento() {
				/*Seteo al oficio en la posicion (2,2) de la matriz situada arriba.
				 *Con direccion hacia la derecha.  
				 * */
				posicion = new Posicion(2,3);
				oficio = new Taladrador(new Direccion(1,0),new HabilidadNula());
				assertNotNull(mapaOtro.getTerreno());
				oficio.mover(mapaOtro.getTerreno(), posicion);
				assertEquals(new Posicion(2,4), posicion);
			}
			/*
			 * En este Test Probamos que el Oficio Taladrador realice todos los movimientos.
			 * Nota: Al realizar todos los movimientos queda en estado finalizado.
			 * 
			 */
			public void testRealizarTodosLosMovimientos() {
				posicion = new Posicion(3,2);
				oficio = new Taladrador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < (Constantes.CANTIDAD_MOV_TALADRADOR + 1) ; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);
				}
				assertEquals(new Posicion(3,7), posicion);
				assertEquals(true, oficio.estaFinalizado());
			}
			
			/*
			 * En este Test Probamos que el Oficio Taladrador deje de taladrar cuando se encuentre con una piedra.
			 */
			public void testRealizarMovimientosHastaPiedra() {
				posicion = new Posicion(2,2);
				oficio = new Taladrador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < (Constantes.CANTIDAD_MOV_TALADRADOR + 1) ; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);
				}
				assertEquals(new Posicion(2,6), posicion);
				assertEquals(true, oficio.estaFinalizado());
			}
			
			/*
			 * En este Test Probamos que el Oficio Taladrador deje de taladrar cuando agote sus movimientos.
			 */
			public void testRealizarMovimientosHastaAgotarMovimientos() {
				posicion = new Posicion(6,2);
				oficio = new Taladrador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < (Constantes.CANTIDAD_MOV_TALADRADOR + 10) ; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);
				}
				assertEquals(new Posicion(6,7), posicion);
				assertEquals(true, oficio.estaFinalizado());
			}
			
			/*
			 * En este Test Probamos que el Oficio Taladrador deje 
			 * materiales del tipo Vacio al taladrar.
			 */
			public void testDejaVacioAlTaladrar() {
				posicion = new Posicion(6,2);
				oficio = new Taladrador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < (Constantes.CANTIDAD_MOV_TALADRADOR + 10) ; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);
				}
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,2)).esVacio());
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,3)).esVacio());
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,4)).esVacio());
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,5)).esVacio());
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,6)).esVacio());
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(6,7)).esPiso());
				assertEquals(new Posicion(6,7), posicion);
				assertEquals(true, oficio.estaFinalizado());
			}
			
			/*
			 * (non-Javadoc)
			 * 
			 * @see junit.framework.TestCase#tearDown()
			 */
			/*protected void tearDown() throws Exception {
				super.tearDown();

			}*/
}
