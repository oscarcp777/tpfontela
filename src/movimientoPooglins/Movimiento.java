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
	
	//se delega el movimiento a la direcci�n, la cual sabe en que direccion moverse
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
	
	public void cambiarDireccion(){
		direccion=direccion.cambiarDireccion();
	}
		
	public void cambiarDireccion(Direccion direccion){
		this.direccion = direccion; 
	}
	
}
