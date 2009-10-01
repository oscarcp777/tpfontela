package modelo.entornoDeJuego;

import modelo.pooglins.HabilidadesDisponibles;

public interface ControladorEstadoPooglin {
	
	public void setearOficioAPooglin(int id, int idOficio);
	
	public void setearHabilidadAPooglin(int id, int idHabilidad);
	
	public HabilidadesDisponibles obtenerHabilidades();
	
	public int getMaximaCantidadDePooglins();
	
	public int getCantidadGanadores();
	
	public boolean gane();
	
	

}
