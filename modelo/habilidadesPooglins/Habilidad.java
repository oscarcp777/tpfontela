package habilidadesPooglins;


import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;
public abstract class Habilidad {
	
	private boolean activada;
	
	public abstract void destruirTerreno(Terreno terreno);
	
	public abstract void aplicar(Poogling poogling);
	
}
