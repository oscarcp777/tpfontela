package modelo.propiedadesDeElementos;

import java.awt.Image;
import java.util.Observable;


public abstract class Posicionable extends Observable{
	private Posicion posicion;
	protected Image image;
	
	public Posicion obtenerPosicion(){
		return posicion;
	}
	
	public void asignarPosicion(Posicion posicion){
		this.posicion = posicion;
	}
	
	public abstract Image getImage();

	/*
	public void actualizarObservadores(){
		setChanged(); //marco al objeto pues ha sufrido cambios
		notifyObservers(); //les aviso a los observadores de tal cambio producido en el objeto observable
	}*/

}
