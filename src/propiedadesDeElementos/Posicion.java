package propiedadesDeElementos;

import java.util.Comparator;

import utilitarios.Constants;

import elementosDelMapa.Aire;
import elementosDelMapa.Poogling;
import elementosDelMapa.Terreno;


import movimientoPooglins.Direccion;


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
	//de la posición actual del posicionable
	public Posicion obtenerPosicionSiguienteDerecha(){
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionX(posicion.getPosicionX()+1);
	    return posicion;
	}

	//devuelve la posicion siguiente abajo , respecto
	//de la posición actual del posicionable
	public Posicion obtenerPosicionSiguienteAbajo() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionY(posicion.getPosicionY()+1);
	    return posicion;
	}
	

	//devuelve la posicion siguiente arriba, respecto
	//de la posición actual del posicionable
	public Posicion obtenerPosicionSiguienteArriba() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionY(posicion.getPosicionY()-1);
	    return posicion;
	}
	

	//devuelve la posicion siguiente a izquierda, respecto
	//de la posición actual del posicionable
	public Posicion obtenerPosicionSiguienteIzquierda() {
		Posicion posicion = new Posicion(this);
	    posicion.setPosicionX(posicion.getPosicionX()-1);
	    return posicion;
	}
	
	
	/*
	public boolean posicionValidaDelTerreno(Estatico estatico,Direccion direccionPooglin){
		//La posicion del pooglin es la referencia this actual
		Posicion siguientePosicion = new Posicion(posicionX,posicionY);
		direccionPooglin.siguientePosicion(siguientePosicion);	 //me devuelve la siguiente posicion del poogling
		   														 //de acuerdo a la direccion de movimiento que tenia
	 	Terreno terreno = (Terreno) estatico;
	 	if(compare(terreno.obtenerPosicion(),siguientePosicion)==0) //El terreno esta al lado
	 	return true;
	 	else{
	 		siguientePosicion.decrementarY();					
	 		if(compare(siguientePosicion,terreno.obtenerPosicion())==0)		
	 		return true;
		}
		return false;
	}
	*/
	
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
