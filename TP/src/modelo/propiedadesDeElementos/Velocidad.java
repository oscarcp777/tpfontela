package modelo.propiedadesDeElementos;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.utilitarios.Constants;

public class Velocidad {
	private int velocidad;
	private int pasosConVelocidad;
	
	public Velocidad(){
		velocidad = 1;
		pasosConVelocidad=velocidad-1;
	}
	
	public void aumentarVelocidad(){
		velocidad++;
		pasosConVelocidad = velocidad-1;
	}
	
	public int getVelocidad(){
		return this.velocidad;
	}
	
	public void setVelocidad(int velocidad){
		this.velocidad=velocidad;
	}
	
	//Es un contador para que asigne n veces la posicion del poogling de acuerdo a la velocidad que tenga este
	public boolean avanzarEnVelocidad(){
		if(pasosConVelocidad==0){
			pasosConVelocidad=velocidad-1;
			return false;
		}else
			pasosConVelocidad--;
			return true;
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("Velocidad");
		xmlElemento.setAttribute("velocidad", ""+velocidad);
				
		return xmlElemento;
	}
}
