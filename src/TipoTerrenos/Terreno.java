package TipoTerrenos;

import Otros.Poogling;


public abstract class Terreno {

	
	public abstract boolean movimientoPooglingValido(Poogling poogling);
	
	//colisiona el poogling contra el terreno,
	//si es fuego, se quema y le saca vidas
	public abstract void colisionPoogling(Poogling poogling);
	
}
