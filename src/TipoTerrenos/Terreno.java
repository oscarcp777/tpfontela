package TipoTerrenos;

import Otros.Poogling;
import Otros.Vida;
import TipoHabilidades.Habilidad;


public abstract class Terreno {
	
	private Vida vida;
	
	public abstract boolean movimientoPooglingValido(Poogling poogling);
	
	//colisiona el poogling contra el terreno,
	//si es fuego, se quema y le saca vidas
	public abstract void colisionPoogling(Poogling poogling);
	
	public abstract void aplicarHabilidad(Habilidad habilidad);

	public void setVida(Vida vida) {
		this.vida = vida;
	}

	public Vida getVida() {
		return vida;
	}
	
}
