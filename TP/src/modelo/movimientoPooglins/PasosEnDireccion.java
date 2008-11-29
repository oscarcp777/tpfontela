package modelo.movimientoPooglins;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class PasosEnDireccion {

	private int cantidadDePasos;
	private boolean quietoEnDireccion;
	private boolean contar;
	
	public PasosEnDireccion(){
		this.cantidadDePasos = 0;
		quietoEnDireccion = false;
		contar = true;
	}
		
	public void darPasosEnDireccion(int cantidadDePasos){
		if (contar())
		this.cantidadDePasos+=cantidadDePasos;
	}
	
	public void setQuietoEnDireccion(boolean quietoEnDireccion){
		this.quietoEnDireccion = quietoEnDireccion;
	}
	
	public boolean getQuietoEnDireccion(){
		return quietoEnDireccion;
	}
	
	public int cantidadDePasosEnDireccion(){
		return cantidadDePasos;
	}
	
	public void inicializarCantidadDePasos(){
		cantidadDePasos = 0;
	}
	
	public void contarPasosEnDireccion(boolean contar){
		this.contar=contar;
	}
	
	public void setContar(boolean contar){
		this.contar = contar;
	}
	
	public boolean contar(){
		return contar;
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("PasosEnDireccion");
		xmlElemento.setAttribute("cantidadDePasos", ""+cantidadDePasos);	
		xmlElemento.setAttribute("quietoEnDireccion", ""+quietoEnDireccion);
		xmlElemento.setAttribute("contar", ""+contar);
							
		return xmlElemento;
	}
	
}
