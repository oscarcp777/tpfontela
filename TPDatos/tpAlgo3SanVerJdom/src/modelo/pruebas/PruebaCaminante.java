package modelo.pruebas;

import java.util.LinkedList;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.Mapa;
import modelo.movimientos.Direccion;
import modelo.pooglins.Caminante;

import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;


public class PruebaCaminante extends TestCase {
	
	private int[][] terrenoDePrueba = 
	   //0 1 2 3 4 5 6 7 8 9
	   {{9,9,9,9,9,9,9,9,9,9},//0
		{9,3,3,3,3,3,3,3,3,9},//1
		{9,3,3,3,0,3,3,3,3,9},//2
		{9,3,0,1,3,6,6,0,3,9},//3
		{9,3,3,3,3,3,3,3,3,9},//4
		{9,9,9,9,9,9,9,9,9,9}};//5
		
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
		public void testMoverHaciaAdelante() {
			/*Seteo al oficio en la posicion (2,3) de la matriz situada arriba.
			 *Con direccion hacia la derecha.  
			 * */
			posicion = new Posicion(2,3);
			oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
			assertNotNull(mapaOtro.getTerreno());
			oficio.mover(mapaOtro.getTerreno(), posicion);
			assertEquals(new Posicion(3,3), posicion);
		}
		/*
		 * En este Test Probamos que el Oficio Caminante revote al llegar a una pared.
		 * Lo importante es que no llegue a la posicion de la pared.
		 */
		public void testRevotar() {
			posicion = new Posicion(7,3);
			oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
			oficio.mover(mapaOtro.getTerreno(), posicion);
			assertEquals(new Posicion(7,3), posicion);
		}
		
		/*
		 * En este Test Probamos que el Oficio Caminante suba una pendiente.
		 */
		public void testSubir() {
			posicion = new Posicion(3,3);
			oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
			oficio.mover(mapaOtro.getTerreno(), posicion);
			assertEquals(new Posicion(4,2), posicion);
		}
		
		/*
		 * En este Test Probamos que el Oficio Caminante duplique su velocidad al caminar en el Hielo.
		 */
		public void testCaminarEnHielo() {
			posicion = new Posicion(5,3);
			oficio = new Caminante(new Direccion(1,0),new HabilidadNula());
			oficio.mover(mapaOtro.getTerreno(), posicion);
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