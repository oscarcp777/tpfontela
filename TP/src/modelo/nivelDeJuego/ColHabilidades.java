package modelo.nivelDeJuego;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import modelo.FabricaHabilidades.FabricaHabilidades;
import modelo.habilidadesPooglins.Habilidad;


public class ColHabilidades {

	private List habilidades;
	
	public ColHabilidades(){
		this.habilidades = new ArrayList();
	}
	
	
	public ColHabilidades(List habilidades){
		this.habilidades = habilidades;
	}
	
	public void agregarHabilidad(Habilidad habilidad){
		habilidades.add(habilidad);
	}
	
	public Habilidad obtenerHabilidad(int posicion){
		return (Habilidad)habilidades.get(posicion);
	}
	
	public Iterator iterator(){
		return habilidades.iterator();
	}
	
	public boolean isVacia(){
		return habilidades.isEmpty();
	}
	
	public boolean borrarHabilidad(Habilidad habilidad){
		return habilidades.remove(habilidad);
	}
	
}
