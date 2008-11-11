package modelo.habilidadesPooglins;


import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.mapaDeJuego.Mapa;
import modelo.propiedadesDeElementos.Posicion;

public abstract class Habilidad {
	
	protected EstadoHabilidad estadoHabilidad; //lo usaran las clases descendientes
		
	//se le pasa el mapa, el pooglin y el terreno contiguo al pooglin
	public abstract void aplicarApooglin(Mapa mapa, Poogling poogling, Terreno terreno);
	
	public abstract void aplicarAterreno(Mapa mapa,Terreno terreno,Poogling poogling);
	
	public boolean isActivada(){
		return estadoHabilidad.isActivadaHabilidad();
	}
	
	public void activarHabilidad(){
		estadoHabilidad.activarHabilidad();
	}
	
	public void desactivarHabilidad(){
		estadoHabilidad.desactivarHabilidad();
	}
	
	public abstract String getNombre();
	
}
