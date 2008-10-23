package Otros;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import fabricas.FabricaTerreno;

import TipoTerrenos.Terreno;

public class ColTerreno {
	
	private List colTerrenos;
	
	public ColTerreno(){
		colTerrenos=new ArrayList();
	}
	
	public Terreno obtenerTerreno(int pos){
		return (Terreno)colTerrenos.get(pos);
	}
	
	public void agregarTerreno(Terreno terreno){
		colTerrenos.add(terreno);
	}
	
	public boolean eliminarFabricaTerreno(Terreno terreno){
		return colTerrenos.remove(terreno);
	}
	
	public Iterator iterator(){
		return colTerrenos.iterator();
	}
	
}

