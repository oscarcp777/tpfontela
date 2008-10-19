package TipoPosicion;

import Otros.Poogling;
import TipoTerrenos.Terreno;

public class Posicion implements Comparable{

	private int posicionX;
	private int posicionY;
		
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
	
	public void incrementarX() {
		posicionX++;
	}
	
	public void incrementarY() {
		posicionY++;
	}
	
	public void decrementarY() {
		posicionY--;
	}
	
	public void decrementarX() {
		posicionX--;
	}
	
	public boolean posicionValidaLateral(Estatico estatico , Poogling poogling){
	
		if (estatico instanceof Terreno){
			
			Terreno terreno = (Terreno) estatico;
		    Posicion posicion = new Posicion(poogling.obtenerPosicion().getPosicionX(),poogling.obtenerPosicion().getPosicionY());
		  
		    poogling.getDireccion().siguientePosicion(posicion);
		    
		    posicionX=posicion.getPosicionX();
		    posicionY=posicion.getPosicionY();
		    
		    if(compareTo(terreno.obtenerPosicion())==0)
		    	return true;
		    
		}
		return false;
	}
	
	public boolean posicionValidaBase(Estatico estatico , Poogling poogling){
		if (estatico instanceof Terreno){

			Terreno terreno = (Terreno) estatico;
			Posicion posicion = new Posicion(poogling.obtenerPosicion().getPosicionX(),poogling.obtenerPosicion().getPosicionY());
		    poogling.getDireccion().siguientePosicion(posicion);
		    posicion.decrementarY();
			if(posicion.equals(terreno.obtenerPosicion())){
				return true;
			}
			
		}
		return false;
	}

	@Override
	public int compareTo(Object o) {
		Posicion otraPosicion = (Posicion)o;
		if((posicionX==otraPosicion.getPosicionX())&&(posicionY==otraPosicion.getPosicionY()))
			return 0;
		else
			return 1;
	}
}
