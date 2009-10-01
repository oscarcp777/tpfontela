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
import modelo.pooglins.Pooglins;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaIntegradorPooglinTeleportador extends TestCase {
	private int[][] terrenoDePrueba = 
		  // 0 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 3 4 5 6 7 8 9 1 1 2 
		   {{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9},
			{9,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,9},
			{9,4,4,4,4,4,4,4,4,4,4,4,4,4,10,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,9},
			{9,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,9},
		    {9,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,4,0,0,0,0,9},
			{9,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,4,0,0,0,0,0,0,0,0,3,0,14,9},
			{9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,3,3,3,5,5,5,5,3,3,3,4,9},
			{9,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,5,9},
			{9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}};
			private Pooglins pooglin;
			private ControlDeJuego controlJuego;
			private Mapa mapaOtro;

			/**
			 * Prueba en la que se ve como se mueven los pooglin
			 * En esta prueba verificamos el funsionamiento tanto del Caminante
			 * como el del CaminanteCayente
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
				mapaOtro.agregarPooglin(new Posicion(5,5));
				mapaOtro.setearOficioAPooglin(1,Constantes.TELEPORTER);
				mapaOtro.agregarPooglin(new Posicion(3,5));
				mapaOtro.setearOficioAPooglin(2,Constantes.TELEPORTER);
				mapaOtro.agregarPooglin(new Posicion(12,5));
				mapaOtro.setearOficioAPooglin(3, Constantes.TELEPORTER);
			}

			/*
			 * Ejecuta el metodo mover del pooglin.
			 * Luego el pooglin llamara al mover de su oficio. 
			 * En este casa el oficio es un caminante.
			 */
			public void testMover() {
				while (mapaOtro.hayPooglins()) {
					mapaOtro.correrRondaMovimientosPooglin();
				}
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