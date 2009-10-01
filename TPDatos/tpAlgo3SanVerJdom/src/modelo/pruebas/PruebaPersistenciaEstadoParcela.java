package modelo.pruebas;

import junit.framework.TestCase;
import modelo.persistencia.Persistidor;
import modelo.entornoDeJuego.EstadoParcela;
import modelo.entornoDeJuego.MaterialDeTerreno;
import modelo.pooglins.Posicion;


public class PruebaPersistenciaEstadoParcela extends TestCase{
	
	/*No importa la extension, puede ser .dat .per .psn etc*/
	private String archivo="XMLPersistencia/PersistenciaEstadoParcela.xml";
	/*la persona a persistir*/
	private EstadoParcela estadoparcelaArch;
	
	public void setUp(){
		Posicion pos = new Posicion (8,8);
		MaterialDeTerreno mat = new MaterialDeTerreno(true,false,true,false,0);
		estadoparcelaArch = new EstadoParcela(pos,mat);		
	}
	
	public void testPersistencia(){
		/*Creo una vacia*/
		EstadoParcela estadoparcelaRec= new EstadoParcela(null,null);
		try{
			/*Guardo la persona a persistir persArch del SetUP*/
			Persistidor.guardar(archivo,estadoparcelaArch);
			/*La asigno a la persona vacia de la 1º linea del testPersistencia*/
			Persistidor.recuperar(archivo,estadoparcelaRec);
		}
		catch(Exception e){ 
			e.printStackTrace();
			/*Puede tirar una excepcion si no lo pudo guardar o hidratar*/
		}
		/*Suponiendo que pudo persistir e hidratar comparo valores*/
		assertEquals(estadoparcelaArch.getPosX(),estadoparcelaRec.getPosX());
		assertEquals(estadoparcelaArch.getPosY(),estadoparcelaRec.getPosY());
		assertEquals(estadoparcelaArch.getTipoMaterial(),estadoparcelaRec.getTipoMaterial());
		
	}
	
	public void tearDown(){
		archivo=null;
		estadoparcelaArch=null;
		
	}


}
