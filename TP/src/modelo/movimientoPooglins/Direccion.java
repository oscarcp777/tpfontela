package modelo.movimientoPooglins;

import modelo.propiedadesDeElementos.Posicion;
import modelo.utilitarios.Constants;

public abstract class Direccion {
	
	public abstract Posicion siguientePosicionEnDireccion(Posicion posicion); 
								  				
	public abstract Direccion cambiarDireccion();
	
	public boolean veniaEnEsaDireccion(Posicion posPoogling,Posicion posTerreno){
		return posTerreno.compareTo(this.siguientePosicionEnDireccion(posPoogling))==Constants.ValorComparador.IGUAL; //me dice si venia en esa direccion el pooglin
	}																										//esto me sirve para tunelElectromagnetico para que el
    																										//poogling no se quede dando vueltas sobre el.
}
