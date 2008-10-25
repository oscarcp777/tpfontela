package movimientoPooglins;

import propiedadesDeElementos.Posicion;


public class Movimiento {
	private Posicion posicion; //posicion donde esta parado el pooglin
	private Direccion direccion;
		
	//constructor por defecto
	public Movimiento(){
	
	}
	
	public Movimiento(Posicion posicionInicial,Direccion direccionInicial){
		posicion = posicionInicial; //le asigna la posicion inicial
		this.direccion = direccionInicial; //le asigna la direccion inicial 
	}
	
	//se delega el movimiento a la dirección, la cual sabe en que direccion moverse
	public void mover(){
		posicion=direccion.siguientePosicionEnDireccion(posicion);
	}
	
	//cambia el tipo de movimiento de acuerdo a la direccion
	//Si se estaba moviendo hacia la derecha, se moverá hacia la izquierda
	//Si se estaba moviendo hacia la izquierda, se moverá hacia la derecha
	//Si se estaba moviendo hacia abajo, se moverá hacia la izquierda por default
	public void cambiarMovimiento(){
		direccion=direccion.cambiarDireccion();
	}
	
	//obtiene la posicion siguiente a la posicion actual 
	public Posicion getPosicionSiguiente(){
		return direccion.siguientePosicionEnDireccion(posicion);
	}

	public Posicion getPosicion() {
		return posicion;
	}
	
}
