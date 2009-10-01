/**
 * 
 */
package modelo.pruebas;

import java.util.LinkedList;

import modelo.constantes.Constantes;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.EstadoDeNivelDescargable;
import modelo.control.Nivel;
import modelo.entornoDeJuego.Mapa;
import modelo.pooglins.Oficio;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaMapa extends TestCase {
		
	private int[][] terrenoDePrueba = 
		   //0 1 2 
		   {{3,0,0},//0
		   	{3,0,0}};//1

	/**
	 * @param name
	 */
	public PruebaMapa(String name) {
		super(name);
		
	}

	
	/**
	 * Implementacion Controlable
	 * */
	public void testSetearOficioAPooglin(int id, Oficio oficio){
		ControlDeJuego controlJuego = new ControlDeJuego();
		EstadoDeNivelDescargable atributos = controlJuego.inicializar(terrenoDePrueba);
		Mapa mapa = new Mapa(atributos);
		
		mapa.agregarPooglin(new Posicion(1,1));
		mapa.setearOficioAPooglin(1,Constantes.CAMINANTE_CAYENTE);
		assertEquals(Constantes.CAMINANTE_CAYENTE, mapa.getEstadoPooglins().get(0).getId());
	}
	
	public void testCorrerRondaMovimientosPooglin( ){
		//Delega comportamiento en EquipoPooglin. Ver test EquipoPooglin testCorrerRondaMovimientosPooglin()
		
	}
	
	public void testHayPooglins(){
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		assertEquals(false, mapa.hayPooglins());
		mapa.agregarPooglin(new Posicion(1,0));
		assertEquals(true, mapa.hayPooglins());
	}
	public void testAgregarPooglin(Posicion posInicial) {
		//Delega comportamiento en EquipoPooglin. Ver test EquipoPooglin testAgregarPooglin()
	}
	/**
	 * Implementacion VisorEstados
	 * */	
	public void testGetEstadoTerreno(){
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		assertEquals(1,mapa.getEstadoTerreno().get(1).getPosX());
		assertEquals(0,mapa.getEstadoTerreno().get(1).getPosY());
		assertEquals(Constantes.PISO,mapa.getEstadoTerreno().get(1).getTipoMaterial());
	}
	
	public void testGetEstadoPooglins(){
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		mapa.agregarPooglin(new Posicion(1,1));
		mapa.setearOficioAPooglin(1, Constantes.TALADRADOR);
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionX());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionY());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getId());
		assertEquals(Constantes.TALADRADOR,mapa.getEstadoPooglins().get(0).getOficio());
		assertEquals(Constantes.HABILIDAD_NULA,mapa.getEstadoPooglins().get(0).getHabilidad());
	}
	
	/**
	 * Implementacion Observador
	 * */
	public void testActualizarEstadoParcela() {
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		assertEquals(Constantes.PARED, mapa.getEstadoTerreno().get(0).getTipoMaterial());
		mapa.correrRondaMovimientosPooglin();
		mapa.getTerreno().crearPiso(new Posicion(0,0));
		assertEquals(Constantes.PISO, mapa.getEstadoTerreno().get(0).getTipoMaterial());
	}
	
	public void testActualizarEstadoPooglin() {
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		mapa.agregarPooglin(new Posicion(1,1));
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionX());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionY());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getId());
		assertEquals(Constantes.CAMINANTE,mapa.getEstadoPooglins().get(0).getOficio());
		assertEquals(Constantes.HABILIDAD_NULA,mapa.getEstadoPooglins().get(0).getHabilidad());
		mapa.setearOficioAPooglin(1, Constantes.TALADRADOR);
		mapa.setearHabilidadAPooglin(1, Constantes.PARACAIDISTA_ESPACIAL);
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionX());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getPosicionY());
		assertEquals(1,mapa.getEstadoPooglins().get(0).getId());
		assertEquals(Constantes.TALADRADOR,mapa.getEstadoPooglins().get(0).getOficio());
		assertEquals(Constantes.PARACAIDISTA_ESPACIAL,mapa.getEstadoPooglins().get(0).getHabilidad());
	}
	
	public void testEventoMuertePooglin() {
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		mapa.agregarPooglin(new Posicion(1,1));
		mapa.eventoMuertePooglin(1);
		assertEquals(false, mapa.hayPooglins());
	}
	
	public void testEventoPooglinGanador() {
		ControlDeJuego controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapa = new Mapa(atributos);
		mapa.agregarPooglin(new Posicion(1,1));
		mapa.eventoPooglinGanador(1);
		assertEquals(false, mapa.hayPooglins());
		assertEquals(1, mapa.getCantidadGanadores());
	}
	


}
