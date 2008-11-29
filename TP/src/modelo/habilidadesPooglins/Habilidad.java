package modelo.habilidadesPooglins;


import org.w3c.dom.Document;
import org.w3c.dom.Element;

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

	public abstract boolean isConstruible();
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("Habilidad");
		xmlElemento.setAttribute("nombreHabilidad",""+this.getClass().getSimpleName()); //uso reflection para obtener el nombre de la habilidad que coincide con el de la clase
		xmlElemento.appendChild(estadoHabilidad.toXml(doc));							//luego a traves de un mapa de habilidades con dicho nombre la puedo obtener.
						
		return xmlElemento;
	}
	
}
