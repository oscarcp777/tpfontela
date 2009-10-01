/**
 * 
 */
package modelo.pruebas;

import java.util.LinkedList;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.EquipoPooglins;
import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaEquipoPooglins extends TestCase {
	private int[][] terrenoDePrueba = 
	   //0 1 2 3 4 5 6 7 8 9 0 1
	   {{9,9,9,9,9,9,9,9,9,9,9,9},//0
		{9,4,4,4,4,4,4,4,4,4,4,9},//1
		{9,4,4,4,4,4,4,4,4,4,4,9},//2
		{9,0,0,0,0,0,3,3,3,9,0,9},//3
		{9,9,9,9,9,9,9,9,9,9,9,9}};//4
		
		private ControlDeJuego controlJuego;
		private Mapa mapaOtro;
		private Oficio oficio;
		Posicion posicion;
	
	
	/**
	 * @param name
	 */
	public PruebaEquipoPooglins(String name) {
		super(name);		
	}

	/* (non-Javadoc)
	 * @see junit.framework.TestCase#setUp()
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

	public void testHayPooglins(){
		EquipoPooglins equipo = new EquipoPooglins();
		assertEquals(false, equipo.hayPooglins());
		equipo.agregarPooglin(new Posicion(1,1), mapaOtro.getTerreno());
		assertEquals(true, equipo.hayPooglins());
	}
	
	public void testAgregarPooglin(){
		EquipoPooglins equipo = new EquipoPooglins();
		assertEquals(0, equipo.getCantidadPooglins());
		equipo.agregarPooglin(new Posicion(1,1), mapaOtro.getTerreno());
		assertEquals(1, equipo.getCantidadPooglins());
		equipo.agregarPooglin(new Posicion(1,1), mapaOtro.getTerreno());
		assertEquals(2, equipo.getCantidadPooglins());
	}
	
	public void testObtenerPooglin(int id){
		EquipoPooglins equipo = new EquipoPooglins();
		equipo.agregarPooglin(new Posicion(1,1), mapaOtro.getTerreno());
		assertNotNull(equipo.obtenerPooglin(1));
		equipo.agregarPooglin(new Posicion(1,2), mapaOtro.getTerreno());
		assertNotNull(equipo.obtenerPooglin(2));
		assertEquals(new Posicion(1,1), equipo.obtenerPooglin(2).getPosicion());
	}
	
	public void testEliminarPooglin(int id){
		EquipoPooglins equipo = new EquipoPooglins();
		equipo.agregarPooglin(new Posicion(1,1), mapaOtro.getTerreno());
		equipo.agregarPooglin(new Posicion(1,2), mapaOtro.getTerreno());
		equipo.eliminarPooglin(1);
		assertNull(equipo.obtenerPooglin(1));
		assertEquals(2,equipo.obtenerPooglin(2).getId() );
	}
	/*
	 * Puede Fallar este test si el movimiento de caminante HORIZONTAl falla.
	 */
	public void testCorrerRondaMovimientosPooglin() {
		EquipoPooglins equipo = new EquipoPooglins();
		equipo.agregarPooglin(new Posicion(1,3), mapaOtro.getTerreno());
		equipo.agregarPooglin(new Posicion(2,3), mapaOtro.getTerreno());
		equipo.correrRondaMovimientosPooglin();
		assertEquals(new Posicion(2,3), equipo.obtenerPooglin(1).getPosicion());
		assertEquals(new Posicion(3,3), equipo.obtenerPooglin(2).getPosicion());
	}


	

}
