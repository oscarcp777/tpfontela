package modelo.elementosDelMapa;

import java.awt.Image;
import java.awt.Toolkit;
import java.util.Iterator;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.nivelDeJuego.ColPooglins;
import modelo.propiedadesDeElementos.Colisionable;
import modelo.propiedadesDeElementos.Posicion;
import modelo.propiedadesDeElementos.Posicionable;

public class Nave extends Posicionable{

	public ColPooglins pooglings;
		
	public Nave(Posicion posicion){
		pooglings = new ColPooglins();
		this.asignarPosicion(posicion);
		image = Toolkit.getDefaultToolkit().getImage("imagenes/nave.png");
	}

	public ColPooglins obtenerPooglings() {
		return pooglings;
	}

	public void cargarPooglings(ColPooglins pooglings) {
		this.pooglings = pooglings;
	}

	
	//se agrega el pooglin a la coleccion de pooglins de la nave.
	public void colisionarPoogling(Poogling poogling) {
		this.pooglings.agregarPosicionable(poogling);
	}

	
	public Image getImage() {
		// TODO Auto-generated method stub
		return image;
	}
	
	public Element toXml(Document doc,boolean naveIngreso){
		
		String tipoNave;
		
		if(naveIngreso)
			tipoNave = "NaveIngreso";
		else
			tipoNave = "NaveEscape";
				
		Element xmlElemento = doc.createElement(tipoNave);
		
		if(naveIngreso)
		    xmlElemento.setAttribute("cantidadPooglinsInicial", Integer.toString(pooglings.tamanio())); //le paso la cantidad que tiene la nave
		else
			xmlElemento.setAttribute("cantidadPooglinsFinal", Integer.toString(pooglings.tamanio())); //le paso la cantidad que tiene la nave	
		
		xmlElemento.setAttribute("posicionX",Integer.toString(obtenerPosicion().getPosicionX()));
		xmlElemento.setAttribute("posicionY",Integer.toString(obtenerPosicion().getPosicionY()));
		
		for(Iterator it = pooglings.iterator();it.hasNext();){
			Poogling poogling = (Poogling)it.next();
			if((poogling.isLlegoAnave()&&!naveIngreso) || (!poogling.isLlegoAnave()&&naveIngreso))
			xmlElemento.appendChild(poogling.toXml(doc)); //lo agrego a la nave de salida
		}
			
				
		return xmlElemento;
	}
		
}
