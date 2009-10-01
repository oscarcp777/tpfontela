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
import modelo.pooglins.Constructor;
import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaConstructor extends TestCase {
	
	private int[][] terrenoDePrueba = 
	   //0 1 2 3 4 5 6 7 8 9 
	   {{9,9,9,9,9,9,9,9,9,9},//0
		{9,4,4,3,4,4,4,4,4,9},//1
		{9,4,3,4,4,4,4,3,4,9},//2
		{9,3,0,0,0,0,0,0,3,9},//3
		{9,9,9,9,9,9,9,9,9,9}};//4
		
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
		 * AGREGAR
		 */
		public void testMoverSobrePuenteConstruido() {
			posicion = new Posicion(2,3);
			oficio = new Constructor(new Direccion(1,0),new HabilidadNula());
			oficio.mover(mapaOtro.getTerreno(), posicion);
			assertEquals(new Posicion(3,2), posicion);
		}
		
		public void testConstruirPuente() {
			posicion = new Posicion(2,3);
			oficio = new Constructor(new Direccion(1,0),new HabilidadNula());
			oficio.mover(mapaOtro.getTerreno(), posicion);
			assertEquals(true,mapaOtro.getTerreno().getElementoTerreno(new Posicion(3,2)).getTipoDeMaterial() == Constantes.TUNEL_DERECHA);
		}
		
		public void testDejarDeConstruirLuegoDeCantidadMaximaPosiciones() {
			posicion = new Posicion(2,3);
			oficio = new Constructor(new Direccion(1,0),new HabilidadNula());
			for (int i = 0; i < Constantes.CANTIDAD_MOV_CONSTRUCTOR + 1; i++) {
				oficio.mover(mapaOtro.getTerreno(), posicion);		
			}
			assertEquals(true, oficio.estaFinalizado());
		}
		public void testDejarDeConstruirPorObstruccionDePared() {
			posicion = new Posicion(6,3);
			oficio = new Constructor(new Direccion(1,0),new HabilidadNula());
			for (int i = 0; i < Constantes.CANTIDAD_MOV_CONSTRUCTOR + 1; i++) {
				oficio.mover(mapaOtro.getTerreno(), posicion);		
			}
			assertEquals(true, oficio.estaFinalizado());
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(7,2)).esPared());
			assertEquals(new Posicion(6,3), posicion);
			//assertEquals(true, mapaOtro.getTerreno().getElementoTerreno( new Posicion(6,3)).getTipoDeMaterial() == Constantes.TUNEL_DERECHA);
		}
		
		public void testPuenteConstruidoCompleto() {
			posicion = new Posicion(2,3);
			oficio = new Constructor(new Direccion(1,0),new HabilidadNula());
			for (int i = 0; i < Constantes.CANTIDAD_MOV_CONSTRUCTOR + 1; i++) {
				oficio.mover(mapaOtro.getTerreno(), posicion);		
			}
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(2,3)).getTipoDeMaterial() == Constantes.TUNEL_DERECHA);
			assertEquals(true, mapaOtro.getTerreno().getElementoTerreno(new Posicion(3,2)).getTipoDeMaterial() == Constantes.TUNEL_DERECHA);
			
			
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
