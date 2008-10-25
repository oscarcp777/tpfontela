package movimientoPooglins;

import propiedadesDeElementos.Posicion;

public interface Direccion {
	
	public Posicion siguientePosicionEnDireccion(Posicion posicion); 
								  				
	public Direccion cambiarDireccion(); //me actualiza la referencia
	        
		
}
