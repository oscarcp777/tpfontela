package modelo.propiedadesDeElementos;

import org.w3c.dom.Document;
import org.w3c.dom.Element;

import modelo.utilitarios.Constants;


public class Posicion implements Comparable{

	private int posicionX;
	private int posicionY;
	
	//Constructor por defecto
	public Posicion(){
		
	}
	
	public Posicion(Posicion posicion){
		  this.posicionX=posicion.getPosicionX();
		  this.posicionY=posicion.getPosicionY();
	}
	
	public Posicion(int posicionX, int posicionY){
	  this.posicionX=posicionX;
	  this.posicionY=posicionY;
	}
	
	public int getPosicionX() {
		return posicionX;
	}

	public int getPosicionY() {
		return posicionY;
	}
	
	//devuelve la posicion siguiente a derecha, respecto
	//de la posicion actual del posicionable
	public Posicion obtenerPosicionSiguienteDerecha(){
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionX(posicion.getPosicionX()+1);
	    return posicion;
	}

	//devuelve la posicion siguiente abajo , respecto
	//de la posicion actual del posicionable
	public Posicion obtenerPosicionSiguienteAbajo() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionY(posicion.getPosicionY()+1);
	    return posicion;
	}
	

	//devuelve la posicion siguiente arriba, respecto
	//de la posicion actual del posicionable
	public Posicion obtenerPosicionSiguienteArriba() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionY(posicion.getPosicionY()-1);
	    return posicion;
	}
	

	//devuelve la posicion siguiente a izquierda, respecto
	//de la posicion actual del posicionable
	public Posicion obtenerPosicionSiguienteIzquierda() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionX(posicion.getPosicionX()-1);
	    return posicion;
	}

	public void setPosicionX(int posX){
		posicionX=posX;
	}
	
	public void setPosicionY(int posY){
		posicionY=posY;
	}
	
	
	@Override
	public int compareTo(Object o) {
		
		Posicion otraPosicion = (Posicion)o;
		
		if((this.getPosicionY()>otraPosicion.getPosicionY()) || ((this.getPosicionY()==otraPosicion.getPosicionY())
			&& this.getPosicionX()>otraPosicion.getPosicionX()))
				
			return Constants.ValorComparador.MAYOR;
		
		else if((this.getPosicionY()==otraPosicion.getPosicionY())&&(this.getPosicionX()==otraPosicion.getPosicionX())){
			 
			return Constants.ValorComparador.IGUAL;
		}else
			
			return Constants.ValorComparador.MENOR;
	}
	
	public int diferenciaEnX(Posicion posicion){
		int posXparam=posicion.getPosicionX();
		
		return (posXparam>posicionX)?posXparam-posicionX:posicionX-posXparam;
	}
	
	public int diferenciaEnY(Posicion posicion){
		int posYparam=posicion.getPosicionY();
		
		return (posYparam>posicionY)?posYparam-posicionY:posicionY-posYparam;
	}
	
	public Element toXml(Document doc){
		Element xmlElemento = doc.createElement("Posicion");
		xmlElemento.setAttribute("posicionX", ""+posicionX);
		xmlElemento.setAttribute("posicionY", ""+posicionY);
					
		return xmlElemento;
	}
}
