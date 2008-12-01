package modelo.habilidadesPooglins;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class EstadoHabilidad extends Thread{

	private boolean estado;
	
	public EstadoHabilidad(){
		estado = false;
	}
	
	public void activarHabilidad(){
		estado = true;
	}
	
	public void desactivarHabilidad(){
		estado = false;
	}
		
	public boolean isActivadaHabilidad(){
		return estado;
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("EstadoHabilidad");
		xmlElemento.setAttribute("activada", ""+estado);
		
		return xmlElemento;
	}
		
}
