package modelo.control;

import java.util.LinkedList;

public interface EstadoDeNivelCargable {

	public void setTerreno(int[][] terreno);
	
	public void setCantidadDePooglins(int cantidadDePooglins);
	
	public void setTiempo(int tiempo);
	
	public void setCantidadDeOficiosPorNivel(LinkedList<CantidadDeOficios> cantidadDeOficiosPorNivel);
	
	public void setAnchoTerreno(int anchoTerreno);
	
	public void setAltoTerreno(int altoTerreno);
	
}
