package modelo.pruebas;

import junit.framework.TestCase;

import modelo.entornoDeJuego.EstadoPooglin;
import modelo.movimientos.Direccion;
import modelo.persistencia.Persistidor;
import modelo.pooglins.Posicion;


public class PruebaPersistenciaEstadoPooglin extends TestCase{
	
	/*No importa la extension, puede ser .dat .per .psn etc*/
	private String archivo="XMLPersistencia/PersistenciaEstadoPooglin.xml";
	/*la persona a persistir*/
	private EstadoPooglin estadopooglinArch;
	
	public void setUp(){
		Posicion pos = new Posicion (3,4);
		estadopooglinArch = new EstadoPooglin(5,pos,3,4, new Direccion(0,0));		
	}
	
	public void testPersistencia(){
		/*Creo una vacia*/
		EstadoPooglin estadopooglinRec= new EstadoPooglin();
		try{
			/*Guardo la persona a persistir persArch del SetUP*/
			Persistidor.guardar(archivo,estadopooglinArch);
			/*La asigno a la persona vacia de la 1º linea del testPersistencia*/
			Persistidor.recuperar(archivo,estadopooglinRec);
		}
		catch(Exception e){ 
			e.printStackTrace();
			/*Puede tirar una excepcion si no lo pudo guardar o hidratar*/
		}
		/*Suponiendo que pudo persistir e hidratar comparo valores*/
		assertEquals(estadopooglinArch.getId(),estadopooglinRec.getId());
		assertEquals(estadopooglinArch.getPosicionX(),estadopooglinRec.getPosicionX());
		assertEquals(estadopooglinArch.getPosicionY(),estadopooglinRec.getPosicionY());
		assertEquals(estadopooglinArch.getOficio(),estadopooglinRec.getOficio());
		assertEquals(estadopooglinArch.getHabilidad(),estadopooglinRec.getHabilidad());
	}
	
	public void tearDown(){
		archivo=null;
		estadopooglinArch=null;
		
	}


}
