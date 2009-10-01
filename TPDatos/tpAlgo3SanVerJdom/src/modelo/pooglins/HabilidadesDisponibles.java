package modelo.pooglins;

import java.util.HashMap;

public class HabilidadesDisponibles {
	
	private HashMap<Integer, Integer> oficios;

	public HashMap<Integer, Integer> getOficios() {
		return oficios;
	}

	public void setOficios(HashMap<Integer, Integer> oficios) {
		this.oficios = oficios;
	}
	
	public int obtenerDisponiblesPorIdDeNivel(int idOficio){
		return oficios.get(idOficio);
	}

	public void descontarUno(Integer idOficio){
		oficios.put(idOficio, (this.oficios.get(idOficio))-1);
	}
	
	public boolean tieneDisponibles(Integer idOficio) {
		return 	oficios.get(idOficio).intValue()>0;	
	}

}
