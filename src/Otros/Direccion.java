package Otros;

import TipoPosicion.Posicion;

public interface Direccion {
	
	public abstract void siguientePosicion(Posicion posicion);
	
	public abstract Direccion cambiarDireccion(Posicion posicion);
	        
		
}
