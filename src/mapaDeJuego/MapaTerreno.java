package mapaDeJuego;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import nivelDeJuego.DimensionTerreno;

import elementosDelMapa.Terreno;


import propiedadesDeElementos.Posicion;


import utilitarios.Constants;


public class MapaTerreno implements Comparator{

	private Map mapTerreno;
			
	public MapaTerreno(){
		this.mapTerreno = new TreeMap(this); //le paso la referencia actual pues esta implementa el comparator
	}										 //para el TreeMap.
	
	
	public void agregarTerreno(Terreno terreno){
		mapTerreno.put(terreno.obtenerPosicion(),terreno);
	}
	
	public Terreno obtenerTerreno(Posicion posicion){
		return (Terreno)this.mapTerreno.get(posicion);
	}

	public int compare(Object o1, Object o2) {
		Posicion posicionO1 = (Posicion)o1;
		return posicionO1.compareTo(o2); //se lo delego a posición que sabe como hacer la comparación			
	}
		
}
