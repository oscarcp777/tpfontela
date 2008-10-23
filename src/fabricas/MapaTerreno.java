package fabricas;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

import Otros.DimensionTerreno;
import TipoPosicion.Posicion;
import TipoTerrenos.Terreno;
import Utilidades.Constants;

public class MapaTerreno implements Comparator{

	private Map mapTerreno;
	private Map clavesRepetidas;
	private DimensionTerreno dimensionTerreno;
	private int valorComparatorKeys;
		
	public MapaTerreno(DimensionTerreno dimensionTerreno){
		this.mapTerreno = new TreeMap(this);
		this.dimensionTerreno=dimensionTerreno;
		this.clavesRepetidas = new TreeMap();
		
	}
	
	public void agregarTerreno(Terreno terreno){
	/*	if((dimensionTerreno.compareTo(terreno.obtenerPosicion())==Constants.ValorComparador.IGUAL)||
		  (dimensionTerreno.compareTo(terreno.obtenerPosicion())==Constants.ValorComparador.MAYOR)) */
		this.mapTerreno.put(terreno.obtenerPosicion(), terreno);
		agregarTerrenoConClaveRepetida(terreno);
	}
	
	protected void agregarTerrenoConClaveRepetida(Terreno terreno){ //visibilidad restringida
		if(this.valorComparatorKeys==Constants.ValorComparador.IGUAL)
		this.clavesRepetidas.put(terreno.obtenerPosicion(),terreno);
	}
	
	public Terreno obtenerTerreno(Posicion posicion){
		if(clavesRepetidas.get(posicion)!=null)
			return (Terreno)this.clavesRepetidas.get(posicion);
		return (Terreno)this.mapTerreno.get(posicion);
	}

	
	public int compare(Object o1, Object o2) {
		Posicion posicionO1 = (Posicion)o1;
		Posicion posicionO2 = (Posicion)o2;
		if(ModuloAlOrigen.calcularModulo(posicionO2)==ModuloAlOrigen.calcularModulo(posicionO1))
			return (this.valorComparatorKeys=Constants.ValorComparador.IGUAL); //seria una clave repetida, lo agrego a la coleccion 
													//de claves repetidas dado que no se agrega en al arbol
			else if(ModuloAlOrigen.calcularModulo(posicionO2)<ModuloAlOrigen.calcularModulo(posicionO1))
				return (this.valorComparatorKeys=Constants.ValorComparador.MENOR);
				else 
					return (this.valorComparatorKeys=Constants.ValorComparador.MAYOR);
	}
		
}
