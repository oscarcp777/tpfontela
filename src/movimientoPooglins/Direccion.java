package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public abstract class Direccion {
	
	private PasosEnDireccion pasosEnDireccion = new PasosEnDireccion();
	
	public abstract Posicion siguientePosicionEnDireccion(Posicion posicion); 
								  				
	public abstract Direccion cambiarDireccion();

	public void darUnPasoEnDireccion() {
		this.pasosEnDireccion.darPasosEnDireccion(1);
	}

	public int cantidadDePasosEnDireccion() {
		return pasosEnDireccion.cantidadDePasosEnDireccion();
	}
	
	public void resetearPasosEnDireccion(){
		this.pasosEnDireccion.inicializarCantidadDePasos();
	}
	
}
