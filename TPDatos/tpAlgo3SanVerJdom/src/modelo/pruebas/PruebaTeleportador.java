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
import modelo.pooglins.Teleportador;
import junit.framework.TestCase;

public class PruebaTeleportador extends TestCase {
	private int[][] terrenoDePrueba = 
		   //0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 
		   {{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},//0
			{9,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,9},//1
		    {9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,0,0,9},//2
			{9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,4,9},//3
			{9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,9},//4
			{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};//5
			
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
			public void testTeletranportarse() {
				posicion = new Posicion(1,2);
				oficio = new Teleportador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < Constantes.CANTIDAD_MOV_TELEPORTER_CAMINANDO + 2; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);	
				}
				assertEquals(new Posicion(26,2), posicion);
				assertEquals(true, oficio.estaFinalizado());
				
			}
			
			public void testNoTeletransportarsePorPared() {
				posicion = new Posicion(3,2);
				oficio = new Teleportador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < Constantes.CANTIDAD_MOV_TELEPORTER_CAMINANDO + 2; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);	
				}
				assertEquals(new Posicion(8,2), posicion);
				assertEquals(true, oficio.estaFinalizado());
			}
			
			public void testNoTeletransportarsePorFueraDePantalla() {
				posicion = new Posicion(16,2);
				oficio = new Teleportador(new Direccion(1,0),new HabilidadNula());
				for (int i = 0; i < Constantes.CANTIDAD_MOV_TELEPORTER_CAMINANDO + 2; i++) {
					oficio.mover(mapaOtro.getTerreno(), posicion);	
				}
				assertEquals(new Posicion(21,2), posicion);
				assertEquals(true, oficio.estaFinalizado());
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