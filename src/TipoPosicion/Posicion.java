package TipoPosicion;

import java.util.Comparator;

import Otros.Direccion;
import Otros.Poogling;
import TipoTerrenos.Aire;
import TipoTerrenos.Terreno;

public class Posicion implements Comparable,Comparator{

	private int posicionX;
	private int posicionY;
	
	//Constructor por defecto
	public Posicion(){
		
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
	
	public Posicion incrementarX() {
		posicionX++;
		return this;
	}
	
	public Posicion incrementarY() {
		posicionY++;
		return this;
	}
	
	public Posicion decrementarY() {
		posicionY--;
		return this;
	}
	
	public Posicion decrementarX() {
		posicionX--;
		return this;
	}
	
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
	
	public void setPosicionX(int posX){
		posicionX=posX;
	}
	
	public void setPosicionY(int posY){
		posicionY=posY;
	}
	
	public void posicionMelliza(Posicion posicion){
		posicion.setPosicionX(this.posicionX);
		posicion.setPosicionY(this.posicionY);
	}

	@Override
	public int compareTo(Object o) {
		Posicion otraPosicion = (Posicion)o;
		if((posicionX==otraPosicion.getPosicionX())&&(posicionY==otraPosicion.getPosicionY()))
			return 0;
		else
			return 2;
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
