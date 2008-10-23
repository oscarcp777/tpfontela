package fabricas;

import TipoPosicion.Posicion;

public final class ModuloAlOrigen {

	public static double calcularModulo(Posicion posicion){
		return Math.hypot(posicion.getPosicionX(),posicion.getPosicionY());
	}
	
}
