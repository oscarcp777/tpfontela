package modelo.xml;

import org.dom4j.Element;

import modelo.mapaDeJuego.Mapa;

public class EstadoJuego {
	private Mapa mapa;
	
	public EstadoJuego(Mapa mapa){
		this.mapa = mapa;
	}
	
	public EstadoJuego(Element elementXML){
		
	}
}
