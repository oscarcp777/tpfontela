package Otros;

import TipoPosicion.Posicion;

public interface Direccion {
	
	public void siguientePosicion(Posicion posicion); //me actualiza la referencia
	
	public boolean verPosicionAbajo(Posicion posicion); //me actualiza la referencia
													  				
	public Direccion cambiarDireccion(); //me actualiza la referencia
	        
		
}
