package habilidadesPooglins;


import java.util.Hashtable;
import java.util.Iterator;
import java.util.List;

import nivelDeJuego.ColFabricaHabilidades;

import FabricaHabilidades.FabricaHabilidades;

public class ContenedorHabilidades {

	private Hashtable hashTable=new Hashtable();
	private static ContenedorHabilidades instance = new ContenedorHabilidades();
	
	private ContenedorHabilidades(){
		
	}
	
	public static ContenedorHabilidades getInstance(){
		return instance;
	}
	
	//Arma un mapa con las habilidades disponibles a instanciar en el nivel de juego
	public void mapearHabilidades(ColFabricaHabilidades fabricaHabilidades){
		
		for(Iterator it = fabricaHabilidades.iterator();it.hasNext();){
			FabricaHabilidades fabrica = (FabricaHabilidades)it.next();
			hashTable.put(fabrica.obtenerNombre(), fabrica);
		}
	}
	
	public Habilidad obtenerHabilidadDeFabrica(String claveNombre){
		FabricaHabilidades fabrica = (FabricaHabilidades)hashTable.get(claveNombre);
		return fabrica.crear();
	}
	
}
