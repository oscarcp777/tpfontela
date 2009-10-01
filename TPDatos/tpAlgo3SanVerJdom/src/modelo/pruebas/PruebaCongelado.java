/**
 * 
 */
package modelo.pruebas;

import java.util.LinkedList;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.*;
import modelo.excepciones.MuerteDePooglinException;
import modelo.pooglins.Congelado;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;


public class PruebaCongelado extends TestCase {
	private int[][] terrenoDePrueba = 
		   //0 1 2 
		   {{9,9,9},//0
			{9,0,9},//1
		    {9,9,9}};//2
			
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
			 * En este Test Probamos que el Oficio Caminante camine en forma correcta hacia la derecha.
			 */
			public void testCongelar() {
				/*Seteo al oficio en la posicion (2,3) de la matriz situada arriba.
				 *Con direccion hacia la derecha.  
				 * */
				boolean murioPooglin = false;
				posicion = new Posicion(1,1);
				oficio = new Congelado();
				try {
					oficio.mover(mapaOtro.getTerreno(), posicion);
				} catch (MuerteDePooglinException e) {
					murioPooglin = true;
				}
				
				
				assertEquals(new Posicion(1,1), posicion);
				assertEquals(true, murioPooglin);
				assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(1,1)).esPooglinsCongelado());
				
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