package modelo.nivelDeJuego;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class Dimension {
	
	private int ancho;
	private int alto;
	
	public Dimension(int ancho, int alto){
		this.ancho = ancho;
		this.alto = alto;
	}
	
	public int getAncho(){
		return ancho;
	}
	
	public int getAlto(){
		return alto;
	}
	
	public Element toXml(Document doc){
		
		Element xmlElemento = doc.createElement("Dimension");
		
		xmlElemento.setAttribute("ancho", ""+ancho);
		xmlElemento.setAttribute("largo", ""+alto);
	
		return xmlElemento;
	}
}
