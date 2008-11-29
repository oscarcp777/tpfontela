package modelo.propiedadesDeElementos;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

public class Vida {
	int cantidadVidas;
	
	public Vida(int cantidadVidas){
		this.cantidadVidas = cantidadVidas;
	}
	
	public int getCantidadVidas(){
		return cantidadVidas;
	}
	
	public void sacarVidas(int vidas){
		if(vidas>=cantidadVidas)
			cantidadVidas=0;
		else
			cantidadVidas = cantidadVidas-vidas;
	}
	
	public boolean hayVida(){
		return (cantidadVidas>0);
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("Vida");
		xmlElemento.setAttribute("cantidadVidas", ""+cantidadVidas);
				
		return xmlElemento;
	}

}
