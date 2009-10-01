package modelo.control;

import java.util.LinkedList;

public interface EstadoDeNivelDescargable {
	
	public int[][] getTerreno();
	
	public int getCantidadDePooglins();
	
	public int getTiempo(); 
	
	public LinkedList<CantidadDeOficios> getCantidadDeOficiosPorNivel();
	
	public int getAnchoTerreno();
	
	public int getAltoTerreno();

	public int getPorcentajeGanadores();
	

}
