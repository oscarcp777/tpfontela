package modelo.pruebas;

import java.util.LinkedList;

import junit.framework.TestCase;
import modelo.constantes.Constantes;
import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.*;
import modelo.movimientos.Direccion;
import modelo.pooglins.Caminante;
import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.ParacaidistaEspacial;
import modelo.pooglins.Posicion;


public class PruebaIntegracionPooglinCaminanteCayendo extends TestCase {
	
		private int[][] terrenoDePrueba =
		   //0 1 2 3 4 5 6 7 8 9
		   {{9,9,9,9,9,9,9,9,9,9},//0
			{9,0,0,0,0,4,4,4,4,9},//1
			{9,3,3,3,3,4,4,4,4,9},//2
			{9,3,3,3,3,4,4,4,4,9},//3
			{9,3,3,3,3,4,4,4,4,9},//4
			{9,3,3,3,3,4,4,4,4,9},//5
			{9,3,3,3,3,0,0,0,14,9},//6
			{9,9,9,9,9,9,9,9,9,9}};//7
		
		
		private ControlDeJuego controlJuego;
		private Mapa mapaOtro;
		/*
		*
		* Este test prueba la interaccion entre un caminante y un pooglin cayendo con y sin paracaidas
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
		
		public void testCaer() {
			
			Oficio oficioCaminanteSinParacaidas = new Caminante(new Direccion(1,0),new HabilidadNula());
			Oficio oficioCaminanteConParacaidas = new Caminante(new Direccion(1,0),new ParacaidistaEspacial());
			
			
			mapaOtro.agregarPooglin(new Posicion(1, 1));
			mapaOtro.setearOficioAPooglin(1, Constantes.CAMINANTE);
			mapaOtro.setearHabilidadAPooglin(1,Constantes.HABILIDAD_NULA);
			mapaOtro.agregarPooglin(new Posicion(1, 1));
			mapaOtro.setearHabilidadAPooglin(1,Constantes.PARACAIDISTA_ESPACIAL);
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
