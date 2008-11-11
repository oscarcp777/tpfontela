package modelo.propiedadesDeElementos;

import java.util.Comparator;




import modelo.elementosDelMapa.Aire;
import modelo.elementosDelMapa.Poogling;
import modelo.elementosDelMapa.Terreno;
import modelo.movimientoPooglins.Direccion;
import modelo.utilitarios.Constants;


public class Posicion implements Comparable,Comparator{

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

	@Override
	public int compare(Object arg0, Object arg1) {
		Posicion pos1=(Posicion)arg0;
		Posicion pos2=(Posicion)arg1;
		
		if((pos1.getPosicionX()==pos2.getPosicionX())&&(pos1.getPosicionY()==pos2.getPosicionY()))
		return 0;
		else 
			return 2;
	}
}
