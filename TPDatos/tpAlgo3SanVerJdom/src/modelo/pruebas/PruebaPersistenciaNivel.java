package modelo.pruebas;

import java.util.LinkedList;

import modelo.control.CantidadDeOficios;
import modelo.control.ControlDeJuego;
import modelo.control.Nivel;
import modelo.entornoDeJuego.EstadoParcela;
import modelo.entornoDeJuego.Mapa;
import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.persistencia.Persistidor;
import modelo.pooglins.Posicion;
import junit.framework.TestCase;

public class PruebaPersistenciaNivel extends TestCase {
	
	private int[][] terrenoDePrueba =
	   //0 1 2 3 4 5 6 7 8 9 10
	   {{9,9,9,9,9,9,9,9,9,9,9},//0
		{9,4,4,4,4,4,4,4,0,14,9},//1
		{9,4,4,4,4,4,4,4,3,3,9},//2
		{9,4,4,4,4,4,4,4,3,3,9},//3
		{9,0,0,0,0,0,0,0,3,3,9},//4
		{9,9,9,9,9,9,9,9,9,9,9}};//5
	
	private int altoTerreno = terrenoDePrueba.length;
	private int anchoTerreno = terrenoDePrueba[0].length;
	
	private String archivo="XMLPersistencia/PersistenciaNivel.xml";
	private Nivel estadonivelArch;
	
	public void setUp(){
		
		LinkedList <CantidadDeOficios> lista = new LinkedList<CantidadDeOficios>();
		CantidadDeOficios oficio1 = new CantidadDeOficios(5,3);
		CantidadDeOficios oficio2 = new CantidadDeOficios(1,2);
		lista.add(oficio1);
		lista.add(oficio2);
		
		estadonivelArch = new Nivel();
		estadonivelArch.setTerreno(this.terrenoDePrueba);
		estadonivelArch.setAltoTerreno(this.altoTerreno);
		estadonivelArch.setAnchoTerreno(this.anchoTerreno);
		estadonivelArch.setCantidadDePooglins(10);
		estadonivelArch.setTiempo(1000);
		estadonivelArch.setCantidadDeOficiosPorNivel(lista);
		
	}
	
	public void testPersistencia(){
		Nivel estadonivelRec= new Nivel();
		try{
			Persistidor.guardar(archivo,estadonivelArch);
			Persistidor.recuperar(archivo,estadonivelRec);
		}
		catch(Exception e){ 
			e.printStackTrace();
		}
		assertEquals(estadonivelArch.getAltoTerreno(),estadonivelRec.getAltoTerreno());
		assertEquals(estadonivelArch.getCantidadDePooglins(),estadonivelRec.getCantidadDePooglins());
		assertEquals(estadonivelArch.getCantidadDeOficiosPorNivel().getLast().getCantidad(),estadonivelRec.getCantidadDeOficiosPorNivel().getLast().getCantidad());
		assertEquals(estadonivelArch.getTerreno().length,estadonivelRec.getTerreno().length);
		assertEquals(estadonivelArch.getTerreno()[5][5],estadonivelRec.getTerreno()[5][5]);
		
	}
	
	public void tearDown(){
		archivo=null;
		estadonivelArch=null;
		
	}

	

}
