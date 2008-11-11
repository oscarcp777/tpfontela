package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;


public class Movimiento {
	private Posicion posicion; //posicion donde esta parado el pooglin
	private Direccion direccion;
	private PasosEnDireccion pasosEnDireccion;
			
	//constructor por defecto
	public Movimiento(){
		
	}
	
	public Movimiento(Posicion posicionInicial){
		posicion = posicionInicial; //le asigna la posicion inicial
		pasosEnDireccion = new PasosEnDireccion();
	}
	
	//se delega el movimiento a la direccion, la cual sabe en que direccion moverse
	public Posicion siguientePosicion(){
		if(noCambiaSuPosicion())
			return posicion;
		else{
			if(pasosEnDireccion.contar()) //si se puede contar los pasos en direccion
			pasosEnDireccion.darPasosEnDireccion(1);
			return (posicion=direccion.siguientePosicionEnDireccion(posicion));
		}
		
		
	}
	
	public Posicion verSiguientePosicion(){
		Posicion posicion = new Posicion();
		boolean valorConteo;
		
		if(pasosEnDireccion.contar()){
		pasosEnDireccion.contarPasosEnDireccion(false);
		valorConteo=true;
		}else
			valorConteo=false;
		
		posicion=direccion.siguientePosicionEnDireccion(this.posicion);
		pasosEnDireccion.contarPasosEnDireccion(valorConteo);
		return posicion;
	}
	
	public int cantidadDePasosEnDireccion(){
		return pasosEnDireccion.cantidadDePasosEnDireccion();
	}
	
	public boolean noCambiaSuPosicion(){
		return pasosEnDireccion.getQuietoEnDireccion();
	}
	
	public void movimientoInvalido(boolean movimientoInvalido){
		pasosEnDireccion.setQuietoEnDireccion(movimientoInvalido);
	}
	
	public void cambiarDireccion(){
		if(!direccion.equals(direccion.cambiarDireccion())){
		pasosEnDireccion.inicializarCantidadDePasos();	
		direccion=direccion.cambiarDireccion();
		}
	}
		
	public void cambiarDireccion(Direccion direccion){
		this.direccion = direccion; 
	}
	
	public Posicion darPasosEnDireccion(PasosEnDireccion pasosEnDireccion){
		int cantidadPasos = 0;
		while(cantidadPasos<pasosEnDireccion.cantidadDePasosEnDireccion()){
			posicion = verSiguientePosicion(); //actualizo la posicion
			cantidadPasos++;
		}
		return posicion;
	}
	
	public void contarPasos(boolean contar){
		pasosEnDireccion.contarPasosEnDireccion(contar);
	}
	
	public boolean isConDireccion(){
		return (direccion!=null);
	}
	
}
