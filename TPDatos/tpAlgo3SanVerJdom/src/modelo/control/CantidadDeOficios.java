package modelo.control;

import org.jdom.Element;

import modelo.persistencia.SerializableJDOM;

public class CantidadDeOficios implements SerializableJDOM {
	
	
	private int cantidad;
	private int idOficio;
	
	
	public CantidadDeOficios(int cantidad, int idOficio) {
		this.cantidad = cantidad;
		this.idOficio = idOficio;
	}
	
	public int getCantidad() {
		return cantidad;
	}
	public int getIdOficio() {
		return idOficio;
	}
	
	public Element serializarJDOM() {
		Element raiz = new Element("Nivel");
		raiz.setAttribute("Cantidad", (new Integer(this.cantidad).toString()));
		raiz.setAttribute("IdOficio", new Integer(this.idOficio).toString());
		return raiz;
	}
	

	public void hidratarJDOM(Element desde) {
		this.cantidad = Integer.parseInt(desde.getAttributeValue("Cantidad"));
		this.idOficio = Integer.parseInt(desde.getAttributeValue("IdOficio"));
		
		
	}

	
}
