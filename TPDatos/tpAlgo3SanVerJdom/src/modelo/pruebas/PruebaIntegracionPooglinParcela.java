package modelo.pruebas;

import java.util.LinkedList;

import junit.framework.TestCase;
import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.EstadoDeNivelDescargable;
import modelo.control.Nivel;
import modelo.persistencia.Persistidor;
import modelo.entornoDeJuego.Mapa;
import modelo.movimientos.Direccion;
import modelo.pooglins.Caminante;
import modelo.pooglins.HabilidadNula;
import modelo.pooglins.Oficio;
import modelo.pooglins.ParacaidistaEspacial;
import modelo.pooglins.Posicion;

public class PruebaIntegracionPooglinParcela extends TestCase{
	
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
	
	/*No importa la extension, puede ser .dat .per .psn etc*/
	private String archivo="XMLPersistencia/PersistenciaIntegracion.xml";
	/*la persona a persistir*/
	
	
	
	
	
	public void setUp(){
		controlJuego = new ControlDeJuego();
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		mapaOtro = new Mapa(atributos);
	}
	
	private void mover(){
		for (int i = 0; i < 7; i++) {
			mapaOtro.correrRondaMovimientosPooglin();
			
		}
		
	}
	
	
	
	public void testPersistencia(){
		
		Oficio oficioCaminanteSinParacaidas = new Caminante(new Direccion(1,0),new HabilidadNula());
		Oficio oficioCaminanteConParacaidas = new Caminante(new Direccion(1,0),new ParacaidistaEspacial());
		
		
		mapaOtro.agregarPooglin(new Posicion(1, 1));
		mapaOtro.setearOficioAPooglin(1, 0);
		mapaOtro.agregarPooglin(new Posicion(4, 1));
		mapaOtro.setearOficioAPooglin(2, 0);
				
				
		this.mover();
		/*Creo una vacia*/		
		CantidadDeOficios oficio = new CantidadDeOficios(3,0);
		LinkedList<CantidadDeOficios> cantidadDeOficios = new LinkedList(); 
		cantidadDeOficios.add(oficio);
		
		Nivel atributos = controlJuego.inicializar(terrenoDePrueba);
		atributos.setCantidadDeOficiosPorNivel(cantidadDeOficios);
		Mapa mapaRec= new Mapa(atributos);
		
		
		try{
			/*Guardo la persona a persistir persArch del SetUP*/
			Persistidor.guardar(archivo,mapaOtro);
			/*La asigno a la persona vacia de la 1º linea del testPersistencia*/
			Persistidor.recuperar(archivo,mapaRec);
		}
		catch(Exception e){ 
			e.printStackTrace();
			/*Puede tirar una excepcion si no lo pudo guardar o hidratar*/
		}
		/*Suponiendo que pudo persistir e hidratar comparo valores*/
		System.out.println("Oficio pooglin a guardar: " + mapaOtro.getEstadoPooglins().get(1).getOficio());
		System.out.println("Oficio pooglin recuperado: " + mapaRec.getEstadoPooglins().get(1).getOficio());
		System.out.println("Tipo material a guardar: " + mapaOtro.getEstadoTerreno().get(6).getTipoMaterial());
		System.out.println("Tipo material recuperado: " + mapaOtro.getEstadoTerreno().get(6).getTipoMaterial());
		assertEquals(mapaOtro.getEstadoPooglins().get(1).getOficio(),mapaRec.getEstadoPooglins().get(1).getOficio());
		assertEquals(mapaOtro.getEstadoTerreno().get(6).getTipoMaterial(),mapaRec.getEstadoTerreno().get(6).getTipoMaterial());
	}
	
	public void tearDown(){
		archivo=null;
		mapaOtro=null;
		
	}
	

}
