package movimientoPooglins;

import propiedadesDeElementos.Posicion;


public class Movimiento {
	private Posicion posicion; //posicion donde esta parado el pooglin
	private Direccion direccion;
			
	//constructor por defecto
	public Movimiento(){
		
	}
	
	public Movimiento(Posicion posicionInicial){
		posicion = posicionInicial; //le asigna la posicion inicial
	}
	
	//se delega el movimiento a la dirección, la cual sabe en que direccion moverse
	public Posicion siguientePosicion(){
		return (posicion=direccion.siguientePosicionEnDireccion(posicion));
		
	}
	
	public Posicion verSiguientePosicion(){
		Posicion posicion = new Posicion(this.posicion);
		return direccion.siguientePosicionEnDireccion(posicion);
	}
	
	public int cantidadDePasosEnDireccion(){
		return direccion.cantidadDePasosEnDireccion();
	}
	
	public boolean invalido(){
		return direccion.quietoEnDireccion();
	}
	
	public void valido(boolean movimientoValido){
		direccion.moverEnDireccion(movimientoValido);
	}
	
	public void cambiarDireccion(){
		direccion=direccion.cambiarDireccion();
	}
		
	public void cambiarDireccion(Direccion direccion){
		this.direccion = direccion; 
	}
	
}
