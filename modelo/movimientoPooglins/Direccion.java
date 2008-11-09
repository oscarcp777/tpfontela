package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public abstract class Direccion {
	
	public abstract Posicion siguientePosicionEnDireccion(Posicion posicion); 
								  				
	public abstract Direccion cambiarDireccion();

    
}
