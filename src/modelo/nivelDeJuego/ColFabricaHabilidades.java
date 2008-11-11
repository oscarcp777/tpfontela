package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.FabricaHabilidades.FabricaHabilidades;


public class ColFabricaHabilidades {

	private List fabricaHabilidades;
	
	public ColFabricaHabilidades(){
		fabricaHabilidades = new ArrayList();
	}
	
	public void agregarFabrica(FabricaHabilidades fabrica){
		fabricaHabilidades.add(fabrica);
	}
	
	public FabricaHabilidades obtenerFabrica(int posicion){
		return (FabricaHabilidades)fabricaHabilidades.get(posicion);
	}
	
	public Iterator iterator(){
		return fabricaHabilidades.iterator();
	}
	
	public boolean isVacia(){
		return fabricaHabilidades.isEmpty();
	}
	
	public boolean borrarFabrica(FabricaHabilidades fabrica){
		return fabricaHabilidades.remove(fabrica);
	}
	
}
