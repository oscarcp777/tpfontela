package modelo.pruebas;

import java.util.LinkedList;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.Mapa;
import modelo.movimientos.Direccion;
import modelo.pooglins.CaminanteCayendo;
import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaCaminanteCayendo extends TestCase {
	
	private int[][] terrenoDePrueba = 
		   
		   //0 1 2 3 4
		   {{9,9,9,9,9},//0
			{9,4,4,4,9},//1
			{9,4,4,4,9},//2
			{9,4,4,4,9},//3
			{9,4,4,4,9},//4
			{9,4,4,4,9},//5
			{9,4,4,4,9},//6
			{9,4,4,4,9},//7
			{9,4,4,4,9},//8
			{9,0,0,0,9},//9
			{9,9,9,9,9}};//10
			
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
			 * En este Test Probamos que el Oficio CaminanteCayendo se mueva en forma correcta hacia abajo.
			 */
			public void testRealizarUnMovimiento() {
				/*Seteo al oficio en la posicion (1,4) de la matriz situada arriba.
				 *Con direccion hacia la derecha.  
				 * */
				posicion = new Posicion(1,4);
				oficio = new CaminanteCayendo(new Direccion(1,0),new HabilidadNula());
				assertNotNull(mapaOtro.getTerreno());
				oficio.mover(mapaOtro.getTerreno(), posicion);
				assertEquals(new Posicion(1,5), posicion);
			}
			/*
			 * En este Test Probamos que el Oficio Taladrador realice todos los movimientos.
			 * Nota: Al realizar todos los movimientos queda en estado finalizado.
			 * 
			 */
			public void testRealizarTodosLosMovimientos() {
				posicion = new Posicion(3,8);
				oficio = new CaminanteCayendo(new Direccion(1,0),new HabilidadNula());
				boolean matEsPiso = false;
				while(!matEsPiso){
					matEsPiso = mapaOtro.getTerreno().getMaterialActual(posicion).esPiso();
					oficio.mover(mapaOtro.getTerreno(), posicion);
					
				}
				assertEquals(new Posicion(3,9), posicion);
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
